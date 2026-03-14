/***********************************************************************
 * Lab10.cpp
 * Orbit all satellites: constants, physics helpers, Sim/Demo, callback, main.
 * Runs unit tests then starts the simulation with Earth and satellites.
 ************************************************************************/

#include <cmath>
#include <vector>
#include "uiInteract.h"
#include "uiDraw.h"
#include "position.h"
#include "satellite.h"
#include "sputnik.h"
#include "gps.h"
#include "hubble.h"
#include "crewDragon.h"
#include "starlink.h"
#include "test.h"
#include "ship.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double HOURS_PER_DAY = 24.0;
const double MINUTES_PER_HOUR = 60.0;
const double FRAME_RATE = 30.0;
const double SECONDS_PER_DAY = 86400.0;
const double SIM_SECONDS_PER_FRAME = 10.0;
const double TIME_DILATION = HOURS_PER_DAY * MINUTES_PER_HOUR;

const double EARTH_RADIUS = 6378000.0;
const double GRAVITY_SEA_LEVEL = 9.80665;
const double GEO_DISTANCE = 42164000.0;
const double GEO_VELOCITY = 3100.0;
const double GPS_DISTANCE = 26560000.0;
const double GPS_VELOCITY = 3880.0;
const double KICK_VELOCITY = 2000.0;
const double TIME_PER_FRAME = SIM_SECONDS_PER_FRAME;
const double ROTATION_PER_FRAME = -(2.0 * M_PI * SIM_SECONDS_PER_FRAME / SECONDS_PER_DAY);

Acceleration getGravity(const Position& pos, double earthRadius, double gravitySeaLevel)
{
   double x = pos.getMetersX();
   double y = pos.getMetersY();
   double distance = sqrt(x * x + y * y);
   if (distance <= 0.0) return Acceleration(0.0, 0.0);
   double h = distance - earthRadius;
   double g = gravitySeaLevel * (earthRadius / (earthRadius + h)) * (earthRadius / (earthRadius + h));
   double ux = -x / distance;
   double uy = -y / distance;
   return Acceleration(g * ux, g * uy);
}

void updateVelocity(Velocity& v, const Acceleration& a, double time)
{
   v.add(a.getVelocity(time));
}

void updatePosition(Position& pos, const Velocity& v, const Acceleration& a, double time)
{
   pos.addMetersX(v.getDx() * time + 0.5 * a.getDDx() * time * time);
   pos.addMetersY(v.getDy() * time + 0.5 * a.getDDy() * time * time);
}

const double GPS_ORBIT_X = 23001634.72;
const double GPS_ORBIT_Y = 13280000.0;
const double GPS_ORBIT_VX = 1940.0;
const double GPS_ORBIT_VY = 3360.18;

/*********************************************
 * Sim
 * Holds the list of bodies and star state. move() advances each body; draw() draws star and bodies.
 *********************************************/
class Sim
{
public:
   Sim(Position ptUpperRight) : ptUpperRight(ptUpperRight)
   {
      bodies.push_back(new Earth());
      bodies.push_back(new Sputnik());
      bodies.push_back(new GPS(0.0, GPS_DISTANCE, -GPS_VELOCITY, 0.0));
      bodies.push_back(new GPS(GPS_ORBIT_X, GPS_ORBIT_Y, -GPS_ORBIT_VX, GPS_ORBIT_VY));
      bodies.push_back(new GPS(GPS_ORBIT_X, -GPS_ORBIT_Y, GPS_ORBIT_VX, GPS_ORBIT_VY));
      bodies.push_back(new GPS(0.0, -GPS_DISTANCE, GPS_VELOCITY, 0.0));
      bodies.push_back(new GPS(-GPS_ORBIT_X, -GPS_ORBIT_Y, GPS_ORBIT_VX, -GPS_ORBIT_VY));
      bodies.push_back(new GPS(-GPS_ORBIT_X, GPS_ORBIT_Y, -GPS_ORBIT_VX, -GPS_ORBIT_VY));
      bodies.push_back(new Hubble());
      bodies.push_back(new CrewDragon());
      bodies.push_back(new Starlink());
      
      // Create the ship
      pShip = new Ship();
      bodies.push_back(pShip);
      
      ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
      phaseStar = 0;
   }

   ~Sim()
   {
      for (Simulatable* p : bodies)
         delete p;
   }

   void input(const Interface* pUI);
   void move();
   void draw();

   std::vector<Simulatable*> bodies;
   Position ptStar;
   Position ptUpperRight;
   unsigned char phaseStar;
   
private:
   Ship* pShip{nullptr};
};

void Sim::input(const Interface* pUI)
{
   if (pShip)
      pShip->input(pUI, bodies);
}

void Sim::move()
{
   for (Simulatable* body : bodies)
      body->advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
   phaseStar++;
}

void Sim::draw()
{
   Position pt;
   ogstream gout(pt);
   gout.drawStar(ptStar, phaseStar);
   for (Simulatable* body : bodies)
      body->draw(gout);
}

void callBack(const Interface* pUI, void* p)
{
   Sim* pSim = (Sim*)p;
   pSim->input(pUI);
   pSim->move();
   pSim->draw();
}

double Position::metersFromPixels = 40.0;

#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
   (void)argc;
   (void)argv;
   testRunner();

   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL, "Lab 09 Orbit One Satellite", ptUpperRight);
   Sim sim(ptUpperRight);
   ui.run(callBack, &sim);
   return 0;
}

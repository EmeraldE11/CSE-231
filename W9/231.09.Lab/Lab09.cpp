/***********************************************************************
 * Lab09.cpp
 * Orbit one satellite: constants, physics helpers, Sim/Demo, callback, main.
 * Runs unit tests then starts the simulation with Earth and GPS.
 ************************************************************************/

#include <cmath>
#include <vector>
#include "uiInteract.h"
#include "uiDraw.h"
#include "position.h"
#include "satellite.h"
#include "test.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double HOURS_PER_DAY = 24.0;
const double MINUTES_PER_HOUR = 60.0;
const double TIME_DILATION = HOURS_PER_DAY * MINUTES_PER_HOUR;
const double FRAME_RATE = 30.0;
const double SECONDS_PER_DAY = 86400.0;

const double EARTH_RADIUS = 6378000.0;
const double GRAVITY_SEA_LEVEL = 9.80665;
const double GEO_DISTANCE = 42164000.0;
const double GEO_VELOCITY = 3100.0;
const double TIME_PER_FRAME = TIME_DILATION / FRAME_RATE;
const double ROTATION_PER_FRAME = -(2.0 * M_PI / FRAME_RATE) * (TIME_DILATION / SECONDS_PER_DAY);

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

Earth::Earth()
{
   position.setMeters(0.0, 0.0);
   angle = 0.0;
}

void Earth::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   angle += ROTATION_PER_FRAME;
}

void Earth::draw(ogstream& gout)
{
   gout.drawEarth(position, angle);
}

Satellite::Satellite() : angularVelocity(0.02), radius(10.0), dead(false) {}

Satellite::Satellite(double x, double y, double vx, double vy)
   : angularVelocity(0.02), radius(10.0), dead(false)
{
   position.setMeters(x, y);
   velocity.setDx(vx);
   velocity.setDy(vy);
   direction.setDxDy(vx, vy);
}

void Satellite::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   if (dead) return;
   double distance = sqrt(position.getMetersX() * position.getMetersX() +
                          position.getMetersY() * position.getMetersY());
   if (distance <= earthRadius) return;

   Acceleration aGravity = getGravity(position, earthRadius, gravitySeaLevel);
   updateVelocity(velocity, aGravity, timePerFrame);
   updatePosition(position, velocity, aGravity, timePerFrame);
   direction.rotate(angularVelocity);
}

Hubble::Hubble() : Satellite(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0) {}

void Hubble::draw(ogstream& gout)
{
   gout.drawHubble(position, direction.getRadians());
}

GPS::GPS() : Satellite(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0) {}

void GPS::draw(ogstream& gout)
{
   gout.drawGPS(position, direction.getRadians());
}

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
      bodies.push_back(new GPS());
      ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
      phaseStar = 0;
   }

   ~Sim()
   {
      for (Simulatable* p : bodies)
         delete p;
   }

   void input(const Interface* pUI) { (void)pUI; }
   void move();
   void draw();

   std::vector<Simulatable*> bodies;
   Position ptStar;
   Position ptUpperRight;
   unsigned char phaseStar;
};

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

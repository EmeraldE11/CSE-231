/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include <cmath>        // for M_PI, sqrt
#include <vector>       // for collection of simulatable bodies
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POSITION
#include "test.h"
using namespace std;

// Simulator time: 1 minute = 1 real day -> 24*60 = 1440x faster
const double HOURS_PER_DAY = 24.0;
const double MINUTES_PER_HOUR = 60.0;
const double TIME_DILATION = HOURS_PER_DAY * MINUTES_PER_HOUR;  // 1440

const double FRAME_RATE = 30.0;   // frames per second
const double TIME_PER_FRAME = TIME_DILATION / FRAME_RATE;  // real seconds per frame (48)

const double SECONDS_PER_DAY = 86400.0;   // earth rotation period in real seconds
const double ROTATION_PER_FRAME = -(2.0 * M_PI / FRAME_RATE) * (TIME_DILATION / SECONDS_PER_DAY);

const double EARTH_RADIUS = 6378000.0;    // meters
const double GRAVITY_SEA_LEVEL = 9.80665; // m/s^2

// GEO: 35,786 km above earth, 42,164 km from center; orbital velocity 3.1 km/s
const double GEO_DISTANCE = 42164000.0;   // meters from earth center
const double GEO_VELOCITY = 3100.0;       // m/s (tangential)

/*************************************************************************
 * Simulatable
 * Base for all bodies in the orbital simulation. Matches the problem
 * domain (earth, satellites, etc.) so the inheritance tree aligns
 * with the design concern. New body types are added as subclasses.
 *************************************************************************/
class Simulatable
{
public:
   virtual ~Simulatable() {}
   virtual void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) = 0;
   virtual void draw(ogstream& gout) = 0;
   Position position;
};

/*************************************************************************
 * Earth
 * Fixed at center; advances by rotating. Draws as earth.
 *************************************************************************/
class Earth : public Simulatable
{
public:
   Earth()
   {
      position.setMeters(0.0, 0.0);
      angle = 0.0;
   }
   void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) override
   {
      angle += ROTATION_PER_FRAME;
   }
   void draw(ogstream& gout) override;

   double angle;
};

/*************************************************************************
 * Satellite
 * Orbital body with velocity; advance applies gravity and motion.
 * New satellite types can be added by subclassing and overriding draw.
 *************************************************************************/
class Satellite : public Simulatable
{
public:
   Satellite(double x, double y, double dx, double dy)
   {
      position.setMeters(x, y);
      this->dx = dx;
      this->dy = dy;
      rotation = 0.0;
   }
   void advance(double t, double r, double g0) override
   {
      double x = position.getMetersX();
      double y = position.getMetersY();
      double distance = sqrt(x * x + y * y);
      if (distance <= r)
         return;
      double h = distance - r;
      double gh = g0 * (r / (r + h)) * (r / (r + h));
      double ddx = -gh * (x / distance);
      double ddy = -gh * (y / distance);
      position.setMeters(x + dx * t + 0.5 * ddx * t * t,
                        y + dy * t + 0.5 * ddy * t * t);
      dx += ddx * t;
      dy += ddy * t;
      rotation += 0.02;
   }
   void draw(ogstream& gout) override;

   double dx;
   double dy;
   double rotation;
};

/*************************************************************************
 * Demo
 * Holds a collection of simulatable bodies. Adding a new body type
 * is done by adding a class and inserting it here—no change to
 * advance/draw logic in callBack (Straightforward adaptability).
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) : ptUpperRight(ptUpperRight)
   {
      bodies.push_back(new Earth());
      bodies.push_back(new Satellite(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0));

      ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
      ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
      phaseStar = 0;
   }

   ~Demo()
   {
      for (Simulatable* p : bodies)
         delete p;
   }

   std::vector<Simulatable*> bodies;
   Position ptStar;
   Position ptUpperRight;
   unsigned char phaseStar;
};

void Earth::draw(ogstream& gout)
{
   gout.drawEarth(position, angle);
}

void Satellite::draw(ogstream& gout)
{
   gout.drawGPS(position, rotation);
}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   Demo* pDemo = (Demo*)p;

   for (Simulatable* body : pDemo->bodies)
      body->advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);

   pDemo->phaseStar++;

   Position pt;
   ogstream gout(pt);

   gout.drawStar(pDemo->ptStar, pDemo->phaseStar);
   for (Simulatable* body : pDemo->bodies)
      body->draw(gout);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{

   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}

/***********************************************************************
 * direction.h
 * Stores an angle in radians and provides get/set in radians, degrees,
 * and unit vector components (dx, dy). Supports rotation and cardinal directions.
 ************************************************************************/

#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*********************************************
 * Direction
 * Angle in radians; getDx/getDy return cos/sin of the angle.
 * Constructor interprets its argument as DEGREES where 0 = up,
 * 90 = right, 180 = down, -90 = left.
 *********************************************/
class Direction
{
public:
   Direction() : radians(0.0) {}
   Direction(double degrees) { setDegrees(degrees); }

   void setRadians(double r)
   {
      radians = normalize(r);
   }

   void setDegrees(double d)
   {
      double r = d * (M_PI / 180.0);
      setRadians(r);
   }

   void setDxDy(double dx, double dy);

   void setUp()   { setRadians(M_PI / 2.0); }
   void setDown() { setRadians(M_PI * 1.5); }
   void setLeft() { setRadians(M_PI); }
   void setRight(){ setRadians(0.0); }

   void rotate(double amount) { setRadians(radians + amount); }

   double getRadians() const { return radians; }
   double getDegrees() const { return radians * (180.0 / M_PI); }
   double getDx() const { return std::cos(radians); }
   double getDy() const { return std::sin(radians); }

private:
   static double normalize(double r)
   {
      // Normalize into [-pi, pi)
      while (r <= -M_PI)
         r += 2.0 * M_PI;
      while (r > M_PI)
         r -= 2.0 * M_PI;
      return r;
   }

   double radians;
};

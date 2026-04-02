/***********************************************************************
 * direction.h
 * Stores an angle in radians and provides get/set in radians, degrees,
 * and unit vector components (dx, dy). Supports rotation and cardinal directions.
 ************************************************************************/

#pragma once

#include <cmath>

/*********************************************
 * Direction
 * Angle in radians; getDx/getDy return cos/sin of the angle.
 *********************************************/
class Direction
{
public:
   Direction() : radians(0.0) {}
   Direction(double radians) : radians(radians) {}

   void setRadians(double r) { radians = r; }
   void setDegrees(double d) { radians = d * (3.14159265358979323846 / 180.0); }
   void setDxDy(double dx, double dy);

   void setUp()   { setRadians(3.14159265358979323846 / 2.0); }
   void setDown() { setRadians(3.14159265358979323846 * 1.5); }
   void setLeft() { setRadians(3.14159265358979323846); }
   void setRight(){ setRadians(0.0); }

   void rotate(double amount) { radians += amount; }

   double getRadians() const { return radians; }
   double getDegrees() const { return radians * (180.0 / 3.14159265358979323846); }
   double getDx() const { return cos(radians); }
   double getDy() const { return sin(radians); }

private:
   double radians;
};

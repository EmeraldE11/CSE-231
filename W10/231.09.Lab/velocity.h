/***********************************************************************
 * velocity.h
 * Stores dx, dy components. Provides get/set by component or by speed+direction.
 * addDx/addDy and add(Velocity) modify the vector in place.
 ************************************************************************/

#pragma once

#include <cmath>
#include "direction.h"

/*********************************************
 * Velocity
 * 2D velocity vector (dx, dy) in meters per second.
 *********************************************/
class Velocity
{
public:
   Velocity() : dx(0.0), dy(0.0) {}
   Velocity(double dx, double dy) : dx(dx), dy(dy) {}

   void assign(const Velocity& v) { dx = v.dx; dy = v.dy; }

   double getDx() const { return dx; }
   double getDy() const { return dy; }
   double getSpeed() const { return sqrt(dx * dx + dy * dy); }
   Direction getDirection() const;

   void setDx(double x) { dx = x; }
   void setDy(double y) { dy = y; }
   void setSpeed(double speed);
   void setDirection(const Direction& d);

   void addDx(double x) { dx += x; }
   void addDy(double y) { dy += y; }
   void add(const Velocity& v) { dx += v.dx; dy += v.dy; }

private:
   double dx;
   double dy;
};

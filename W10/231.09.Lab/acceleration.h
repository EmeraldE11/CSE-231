/***********************************************************************
 * acceleration.h
 * Stores ddx, ddy. getVelocity(time) returns a Velocity (ddx*time, ddy*time)
 * for use in v += a*dt.
 ************************************************************************/

#pragma once

#include "velocity.h"

/*********************************************
 * Acceleration
 * 2D acceleration (ddx, ddy) in meters per second squared.
 *********************************************/
class Acceleration
{
public:
   Acceleration() : ddx(0.0), ddy(0.0) {}
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) {}

   void assign(const Acceleration& a) { ddx = a.ddx; ddy = a.ddy; }

   double getDDx() const { return ddx; }
   double getDDy() const { return ddy; }

   Velocity getVelocity(double time) const { return Velocity(ddx * time, ddy * time); }

private:
   double ddx;
   double ddy;
};

/***********************************************************************
 * velocity.cpp
 * getDirection returns a Direction from atan2(dy,dx). setSpeed scales the
 * current direction to the given magnitude. setDirection keeps speed and sets dx,dy from the direction.
 ************************************************************************/

#include "velocity.h"

Direction Velocity::getDirection() const
{
   Direction d;
   d.setDxDy(dx, dy);
   return d;
}

void Velocity::setSpeed(double speed)
{
   double s = getSpeed();
   if (s <= 0.0) return;
   dx = dx * (speed / s);
   dy = dy * (speed / s);
}

void Velocity::setDirection(const Direction& d)
{
   double s = getSpeed();
   dx = d.getDx() * s;
   dy = d.getDy() * s;
}

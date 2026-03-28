/***********************************************************************
 * direction.cpp
 * Implements setDxDy: sets radians from the atan2 of the given vector.
 ************************************************************************/

#include "direction.h"

/*********************************************
 * setDxDy
 * Sets the direction from a unit vector (dx, dy) using atan2
 * and normalizes the resulting angle.
 *********************************************/
void Direction::setDxDy(double dx, double dy)
{
   double r = atan2(dy, dx);
   setRadians(r);
}

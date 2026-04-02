/***********************************************************************
 * direction.cpp
 * Implements setDxDy: sets radians from the atan2 of the given vector.
 ************************************************************************/

#include "direction.h"

/*********************************************
 * setDxDy
 * Sets the direction from a unit vector (dx, dy) using atan2.
 *********************************************/
void Direction::setDxDy(double dx, double dy)
{
   radians = atan2(dy, dx);
}

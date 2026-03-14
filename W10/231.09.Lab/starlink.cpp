/***********************************************************************
 * starlink.cpp
 * Starlink implementation: LEO per program spec.
 ************************************************************************/

#include "starlink.h"

Starlink::Starlink() : Satellite(0.0, -13020000.0, 5800.0, 0.0)
{
   radius = 6.0;
}

void Starlink::draw(ogstream& gout)
{
   gout.drawStarlink(position, direction.getRadians());
}

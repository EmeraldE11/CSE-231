/***********************************************************************
 * sputnik.cpp
 * Sputnik implementation: initial position and velocity per program spec.
 ************************************************************************/

#include "sputnik.h"

Sputnik::Sputnik() : Satellite(-36515095.13, 21082000.0, 2050.0, 2684.68)
{
   radius = 4.0;
}

void Sputnik::draw(ogstream& gout)
{
   gout.drawSputnik(position, direction.getRadians());
}

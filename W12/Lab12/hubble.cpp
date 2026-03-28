/***********************************************************************
 * hubble.cpp
 * Hubble implementation: GEO orbit per program spec.
 ************************************************************************/

#include "hubble.h"

Hubble::Hubble() : Satellite(0.0, -GEO_DISTANCE, GEO_VELOCITY, 0.0)
{
   radius = 10.0;
}

void Hubble::destroy(std::vector<Simulatable*>& satellites)
{
   spawnDebrisOnCollision(satellites, 3, 2);
}

void Hubble::draw(ogstream& gout)
{
   gout.drawHubble(position, direction.getRadians());
}

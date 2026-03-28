/***********************************************************************
 * starlink.cpp
 * Starlink implementation: LEO per program spec.
 ************************************************************************/

#include "starlink.h"
#include "partTypes.h"

Part* Starlink::createPart(const Position& offset, const Velocity& kick)
{
   return new StarlinkPart(*this, offset, kick);
}

Starlink::Starlink() : Satellite(0.0, -13020000.0, 5800.0, 0.0)
{
   radius = 6.0;
}

void Starlink::destroy(std::vector<Simulatable*>& satellites)
{
   spawnDebrisOnCollision(satellites, 2, 1);
}

void Starlink::draw(ogstream& gout)
{
   gout.drawStarlink(position, direction.getRadians());
}

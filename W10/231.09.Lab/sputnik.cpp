/***********************************************************************
 * sputnik.cpp
 * Sputnik implementation: initial position and velocity per program spec.
 ************************************************************************/

#include "sputnik.h"
#include "partTypes.h"

Part* Sputnik::createPart(const Position& offset, const Velocity& kick)
{
   return new SputnikPart(*this, offset, kick);
}

Sputnik::Sputnik() : Satellite(-36515095.13, 21082000.0, 2050.0, 2684.68)
{
   radius = 4.0;
}

void Sputnik::destroy(std::vector<Simulatable*>& satellites)
{
   spawnDebrisOnCollision(satellites, 2, 1);
}

void Sputnik::draw(ogstream& gout)
{
   gout.drawSputnik(position, direction.getRadians());
}

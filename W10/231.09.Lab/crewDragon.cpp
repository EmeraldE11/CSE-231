/***********************************************************************
 * crewDragon.cpp
 * Crew Dragon implementation: LEO per program spec.
 ************************************************************************/

#include "crewDragon.h"
#include "partTypes.h"

Part* CrewDragon::createPart(const Position& offset, const Velocity& kick)
{
   return new CrewDragonPart(*this, offset, kick);
}

CrewDragon::CrewDragon() : Satellite(0.0, 8000000.0, -7900.0, 0.0)
{
   radius = 7.0;
}

void CrewDragon::destroy(std::vector<Simulatable*>& satellites)
{
   spawnDebrisOnCollision(satellites, 3, 2);
}

void CrewDragon::draw(ogstream& gout)
{
   gout.drawCrewDragon(position, direction.getRadians());
}

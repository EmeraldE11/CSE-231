/***********************************************************************
 * crewDragon.cpp
 * Crew Dragon implementation: LEO per program spec.
 ************************************************************************/

#include "crewDragon.h"

CrewDragon::CrewDragon() : Satellite(0.0, 8000000.0, -7900.0, 0.0)
{
   radius = 7.0;
}

void CrewDragon::draw(ogstream& gout)
{
   gout.drawCrewDragon(position, direction.getRadians());
}

/***********************************************************************
 * crewDragon.h
 * Crew Dragon: low Earth orbit, radius 7 pixels.
 ************************************************************************/

#pragma once

#include "satellite.h"

class CrewDragon : public Satellite
{
public:
   CrewDragon();
   void draw(ogstream& gout) override;
   void destroy(std::vector<Simulatable*>& satellites) override;
};

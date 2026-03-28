/***********************************************************************
 * part.h
 * Debris piece broken from a satellite on collision. Does not expire;
 * can be broken into fragments.
 ************************************************************************/

#pragma once

#include "satellite.h"

class Part : public Satellite
{
public:
   Part(const Satellite& parent, const Position& offset, const Velocity& kick);
   void draw(ogstream& gout) override;
   void destroy(std::vector<Simulatable*>& satellites) override;
};

/***********************************************************************
 * part.h
 ************************************************************************/

#pragma once

#include "satellite.h"

class Part : public Satellite
{
public:
   Part(const Satellite& parent, const Direction& kickDirection);
   void draw(ogstream& gout) override;
   void destroy(std::vector<Simulatable*>& satellites) override;
};

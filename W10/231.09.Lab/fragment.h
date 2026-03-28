/***********************************************************************
 * fragment.h
 ************************************************************************/

#pragma once

#include "satellite.h"

class Fragment : public Satellite
{
public:
   Fragment(const Satellite& parent, const Direction& kickDirection);
   void draw(ogstream& gout) override;
   void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) override;
   void destroy(std::vector<Simulatable*>& satellites) override;
};

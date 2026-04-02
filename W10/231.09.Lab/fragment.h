/***********************************************************************
 * fragment.h
 * Uniform debris particle; same behavior regardless of origin.
 ************************************************************************/

#pragma once

#include "satellite.h"

class Fragment : public Satellite
{
public:
   Fragment(const Satellite& parent, const Position& offset, const Velocity& kick);
   void draw(ogstream& gout) override;
};

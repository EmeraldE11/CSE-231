/***********************************************************************
 * hubble.h
 * Hubble Space Telescope: GEO at (0, -42164000), velocity (3100, 0), radius 10.
 ************************************************************************/

#pragma once

#include "satellite.h"

class Hubble : public Satellite
{
public:
   Hubble();
   void draw(ogstream& gout) override;
};

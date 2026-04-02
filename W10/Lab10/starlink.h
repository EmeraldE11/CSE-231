/***********************************************************************
 * starlink.h
 * Starlink satellite: low Earth orbit, radius 6 pixels.
 ************************************************************************/

#pragma once

#include "satellite.h"

class Starlink : public Satellite
{
public:
   Starlink();
   void draw(ogstream& gout) override;
};

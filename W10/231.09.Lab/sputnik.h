/***********************************************************************
 * sputnik.h
 * Sputnik satellite: elliptical retrograde orbit, radius 4 pixels.
 ************************************************************************/

#pragma once

#include "satellite.h"

class Sputnik : public Satellite
{
public:
   Sputnik();
   void draw(ogstream& gout) override;
};

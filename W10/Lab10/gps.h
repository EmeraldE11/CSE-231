/***********************************************************************
 * gps.h
 * GPS satellite: navigation orbit, radius 12 pixels. Six orbits supported.
 ************************************************************************/

#pragma once

#include "satellite.h"

class GPS : public Satellite
{
public:
   GPS();
   GPS(double x, double y, double vx, double vy);
   void draw(ogstream& gout) override;
};

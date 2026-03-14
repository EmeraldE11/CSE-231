/***********************************************************************
 * gps.cpp
 * GPS implementation: default first of six orbits; overload for other positions.
 ************************************************************************/

#include "gps.h"

GPS::GPS() : Satellite(0.0, GPS_DISTANCE, -GPS_VELOCITY, 0.0)
{
   radius = 12.0;
}

GPS::GPS(double x, double y, double vx, double vy) : Satellite(x, y, vx, vy)
{
   radius = 12.0;
}

void GPS::draw(ogstream& gout)
{
   gout.drawGPS(position, direction.getRadians());
}

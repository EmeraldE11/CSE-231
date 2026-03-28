/***********************************************************************
 * fragment.cpp
 ************************************************************************/

#include "fragment.h"

Fragment::Fragment(const Satellite& parent, const Direction& kickDirection)
   : Satellite(parent, kickDirection)
{
   radius = 2.0;
   angularVelocity = 0.05;
}

void Fragment::draw(ogstream& gout)
{
   gout.drawFragment(position, direction.getRadians());
}

void Fragment::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   Satellite::advance(timePerFrame, earthRadius, gravitySeaLevel);
   if (age >= SHORT_LIVED_LIFETIME_FRAMES)
      kill();
}

void Fragment::destroy(std::vector<Simulatable*>& satellites)
{
   (void)satellites;
   kill();
}

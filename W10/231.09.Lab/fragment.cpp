/***********************************************************************
 * fragment.cpp
 ************************************************************************/

#include "fragment.h"

Fragment::Fragment(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Satellite(parent.getPosition().getMetersX() + offset.getMetersX(),
              parent.getPosition().getMetersY() + offset.getMetersY(),
              kick.getDx(), kick.getDy())
{
   angularVelocity = 0.08;
   radius = 1.0 * position.getZoom();
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

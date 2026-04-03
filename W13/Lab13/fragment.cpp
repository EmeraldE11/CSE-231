/***********************************************************************
 * fragment.cpp
 ************************************************************************/

#include "fragment.h"

Fragment::Fragment(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Satellite(parent.getPosition().getMetersX() + offset.getMetersX(),
              parent.getPosition().getMetersY() + offset.getMetersY(),
              parent.getVelocity().getDx() + kick.getDx(),
              parent.getVelocity().getDy() + kick.getDy())
{
   angularVelocity = 0.08;
   radius = 1.0;
}

void Fragment::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   Satellite::advance(timePerFrame, earthRadius, gravitySeaLevel);
   if (!dead && age >= FRAGMENT_LIFETIME_FRAMES)
      kill();
}

void Fragment::draw(ogstream& gout)
{
   gout.drawFragment(position, direction.getRadians());
}

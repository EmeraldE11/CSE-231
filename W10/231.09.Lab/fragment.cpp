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

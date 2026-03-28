/***********************************************************************
 * part.cpp
 ************************************************************************/

#include "part.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Part::Part(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Satellite(parent.getPosition().getMetersX() + offset.getMetersX(),
              parent.getPosition().getMetersY() + offset.getMetersY(),
              kick.getDx(), kick.getDy())
{
   angularVelocity = 0.05;
   radius = 2.0 * position.getZoom();
}

void Part::draw(ogstream& gout)
{
   gout.drawProjectile(position);
   gout.drawFragment(position, direction.getRadians());
}

void Part::destroy(std::vector<Simulatable*>& satellites)
{
   Direction d1;
   d1.setRadians(direction.getRadians());
   Direction d2;
   d2.setRadians(direction.getRadians() + M_PI / 2.0);
   Velocity k1(d1.getDx() * KICK_VELOCITY * 0.4, d1.getDy() * KICK_VELOCITY * 0.4);
   Velocity k2(d2.getDx() * KICK_VELOCITY * 0.4, d2.getDy() * KICK_VELOCITY * 0.4);
   spawnFragment(satellites, Position(), k1);
   spawnFragment(satellites, Position(), k2);
   if (dead) return;
   const int n = 2;
   for (int i = 0; i < n; i++)
   {
      double angle = direction.getRadians() + (2.0 * M_PI * i / n);
      Direction kick;
      kick.setRadians(angle);
      satellites.push_back(new Fragment(*this, kick));
   }
   kill();
}

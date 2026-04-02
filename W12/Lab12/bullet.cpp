/***********************************************************************
 * bullet.cpp
 ************************************************************************/

#include "bullet.h"
#include "uiDraw.h"

Bullet::Bullet(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Satellite(parent.getPosition().getMetersX() + offset.getMetersX(),
              parent.getPosition().getMetersY() + offset.getMetersY(),
              kick.getDx(), kick.getDy())
{
   angularVelocity = 0.0;
   radius = BULLET_RADIUS_PIXELS;
}

void Bullet::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   (void)earthRadius;
   (void)gravitySeaLevel;
   if (dead) return;

   // Constant velocity until lifetime expires (no gravity).
   position.addMetersX(velocity.getDx() * timePerFrame);
   position.addMetersY(velocity.getDy() * timePerFrame);
   age++;
   if (age >= BULLET_LIFETIME_FRAMES)
      kill();
}

void Bullet::draw(ogstream& gout)
{
   gout.drawProjectile(position);
}

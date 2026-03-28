/***********************************************************************
 * bullet.cpp
 ************************************************************************/

#include "bullet.h"
#include "ship.h"

namespace
{
const int IGNORE_COLLISION_WITH_FIRER_AGE = 4;
}

Bullet::Bullet(const Ship& ship, const Position& offset, const Velocity& kick)
   : Projectile(ship, offset, kick), firedFrom(&ship)
{
}

bool Bullet::ignoresCollisionWith(const Ship& ship) const
{
   return firedFrom == &ship && age < IGNORE_COLLISION_WITH_FIRER_AGE;
}

void Bullet::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   Projectile::advance(timePerFrame, earthRadius, gravitySeaLevel);
   if (age >= SHORT_LIVED_LIFETIME_FRAMES)
      kill();
}

void Bullet::destroy(std::vector<Simulatable*>& satellites)
{
   (void)satellites;
   kill();
}

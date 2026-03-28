/***********************************************************************
 * bullet.h
 ************************************************************************/

#pragma once

#include "satellite.h"

class Ship;

class Bullet : public Projectile
{
public:
   using Projectile::Projectile;
   Bullet(const Ship& ship, const Position& offset, const Velocity& kick);

   bool ignoresCollisionWith(const Ship& ship) const;

   void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) override;
   void destroy(std::vector<Simulatable*>& satellites) override;

private:
   const Ship* firedFrom{nullptr};
};

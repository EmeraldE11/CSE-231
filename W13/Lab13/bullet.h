/***********************************************************************
 * bullet.h
 * Ship-fired round; same draw as a projectile marker, limited lifetime.
 ************************************************************************/

#pragma once

#include "satellite.h"

class Bullet : public Satellite
{
public:
   /// offset: meters from parent center; kick: world velocity of the round (not relative to parent).
   Bullet(const Satellite& parent, const Position& offset, const Velocity& kick);
   void advance(double timePerFrame, double earthRadius, double gravitySeaLevel) override;
   void draw(ogstream& gout) override;
};

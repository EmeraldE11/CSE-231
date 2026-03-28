/***********************************************************************
 * ship.cpp
 * Ship
 ************************************************************************/

#include "ship.h"
#include "bullet.h"
#include "position.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include <cmath>

extern const double TIME_PER_FRAME;
extern const double BULLET_RELATIVE_SPEED;

const double SHIP_THRUST = 25.0;
const double SHIP_ROTATION_PER_FRAME = M_PI / 30.0;

Ship::Ship()
   : Satellite(GPS_DISTANCE, 0.0, 0.0, GPS_VELOCITY)
{
   radius = 10.0;
   angularVelocity = 0.0;
   dead = false;
   age = 0;
   direction.setRadians(M_PI_2);
}

void Ship::input(const Interface* pUI, std::vector<Simulatable*>& satellites)
{
   thrust = false;

   if (pUI && pUI->isLeft())
      direction.rotate(SHIP_ROTATION_PER_FRAME);
   if (pUI && pUI->isRight())
      direction.rotate(-SHIP_ROTATION_PER_FRAME);

   if (pUI && pUI->isUp())
   {
      double dvx = SHIP_THRUST * TIME_PER_FRAME * direction.getDx();
      double dvy = SHIP_THRUST * TIME_PER_FRAME * direction.getDy();
      velocity.setDx(velocity.getDx() + dvx);
      velocity.setDy(velocity.getDy() + dvy);
      thrust = true;
   }

   if (pUI && pUI->isSpace())
   {
      const double bulletRadiusPx = 1.0;
      double mPerPx = Position::getMetersFromPixels();
      double pastHullMeters = (radius + bulletRadiusPx) * mPerPx;
      double epsilonMeters = std::max(10.0, 1e-9 * pastHullMeters);
      double noseMeters = pastHullMeters + epsilonMeters;
      Position offset;
      offset.setMeters(noseMeters * direction.getDx(), noseMeters * direction.getDy());
      Velocity kick;
      kick.setDx(velocity.getDx() + BULLET_RELATIVE_SPEED * direction.getDx());
      kick.setDy(velocity.getDy() + BULLET_RELATIVE_SPEED * direction.getDy());
      satellites.push_back(new Bullet(*this, offset, kick));
   }
}

void Ship::draw(ogstream& gout)
{
   // uiDraw::rotate maps local +Y (nose) to (sin R, cos R); Direction uses (cos θ, sin θ).
   gout.drawShip(position, M_PI_2 - direction.getRadians(), thrust);
}

void Ship::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   Acceleration a = getGravity(position, earthRadius, gravitySeaLevel);
   updateVelocity(velocity, a, timePerFrame);
   move(timePerFrame);
   age++;
}

void Ship::move(double time)
{
   position.addMetersX(velocity.getDx() * time);
   position.addMetersY(velocity.getDy() * time);
}

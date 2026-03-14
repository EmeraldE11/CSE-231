/***********************************************************************
 * satellite.cpp
 * Earth, Satellite base, and Projectile implementations.
 ************************************************************************/

#include "satellite.h"
#include <cmath>

Earth::Earth()
{
   position.setMeters(0.0, 0.0);
   angle.setRadians(0.0);
}

void Earth::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   (void)timePerFrame;
   (void)earthRadius;
   (void)gravitySeaLevel;
   angle.rotate(ROTATION_PER_FRAME);
}

void Earth::draw(ogstream& gout)
{
   gout.drawEarth(position, angle.getRadians());
}

Satellite::Satellite() : angularVelocity(0.02), radius(10.0), dead(false), age(0) {}

Satellite::Satellite(double x, double y, double vx, double vy)
   : angularVelocity(0.02), radius(10.0), dead(false), age(0)
{
   position.setMeters(x, y);
   velocity.setDx(vx);
   velocity.setDy(vy);
   direction.setDxDy(vx, vy);
}

Satellite::Satellite(const Satellite& parent, const Direction& kickDirection)
   : angularVelocity(0.0), radius(0.0), dead(false), age(0)
{
   position = parent.getPosition();
   velocity.setDx(kickDirection.getDx() * KICK_VELOCITY);
   velocity.setDy(kickDirection.getDy() * KICK_VELOCITY);
   direction = kickDirection;
}

void Satellite::move(double time)
{
   advance(time, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
}

void Satellite::advance(double timePerFrame, double earthRadius, double gravitySeaLevel)
{
   if (dead) return;
   double distance = sqrt(position.getMetersX() * position.getMetersX() +
                          position.getMetersY() * position.getMetersY());
   if (distance <= earthRadius) return;

   double dt = timePerFrame;
   Acceleration a = getGravity(position, earthRadius, gravitySeaLevel);
   velocity.add(a.getVelocity(dt * 0.5));
   position.addMetersX(velocity.getDx() * dt);
   position.addMetersY(velocity.getDy() * dt);
   Acceleration aNew = getGravity(position, earthRadius, gravitySeaLevel);
   velocity.add(aNew.getVelocity(dt * 0.5));
   direction.rotate(angularVelocity);
   age++;
}

Projectile::Projectile(const Satellite& parent, const Position& offset, const Velocity& kick)
   : Satellite(parent.getPosition().getMetersX() + offset.getMetersX(),
              parent.getPosition().getMetersY() + offset.getMetersY(),
              kick.getDx(), kick.getDy())
{
   radius = 1.0 * position.getZoom();
}

void Projectile::draw(ogstream& gout)
{
   gout.drawProjectile(position);
}

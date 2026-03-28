/***********************************************************************
 * satellite.cpp
 * Earth, Satellite base, and Projectile implementations.
 ************************************************************************/

#include "satellite.h"
#include "part.h"
#include "fragment.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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



Part* Satellite::createPart(const Position& offset, const Velocity& kick)
{
   (void)offset;
   (void)kick;
   return nullptr;
}

void Satellite::spawnPart(std::vector<Simulatable*>& out, const Position& offset, const Velocity& kick)
{
   Part* p = createPart(offset, kick);
   if (p)
      out.push_back(p);
}

void Satellite::spawnFragment(std::vector<Simulatable*>& out, const Position& offset, const Velocity& kick)
{
   out.push_back(new Fragment(*this, offset, kick));
}

void Satellite::spawnDebrisOnCollision(std::vector<Simulatable*>& out, int numParts, int numFragments)
{
   spawnPartRing(out, numParts);
   spawnFragmentRing(out, numFragments);
}

void Satellite::spawnPartRing(std::vector<Simulatable*>& out, int numParts)
{
   for (int i = 0; i < numParts; i++)
   {
      double angle = 2.0 * M_PI * i / numParts;
      Direction d;
      d.setRadians(angle);
      Position off;
      off.setMeters(d.getDx() * 400.0, d.getDy() * 400.0);
      Velocity kick(d.getDx() * KICK_VELOCITY * 0.3, d.getDy() * KICK_VELOCITY * 0.3);
      spawnPart(out, off, kick);
   }
}

void Satellite::spawnFragmentRing(std::vector<Simulatable*>& out, int numFragments)
{
   for (int i = 0; i < numFragments; i++)
   {
      double angle = 2.0 * M_PI * i / numFragments + 0.5;
      Direction d;
      d.setRadians(angle);
      Velocity kick(d.getDx() * KICK_VELOCITY * 0.25, d.getDy() * KICK_VELOCITY * 0.25);
      spawnFragment(out, Position(), kick);
   }
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

/***********************************************************************
 * collision.cpp
 ************************************************************************/

#include "collision.h"
#include "satellite.h"
#include "bullet.h"
#include "fragment.h"
#include "part.h"
#include "position.h"
#include "ship.h"
#include <cmath>

static double radiusMeters(double radiusPixels)
{
   return radiusPixels * Position::getMetersFromPixels();
}

static bool ignoreBulletVersusFiringShip(const Satellite& a, const Satellite& b)
{
   const Bullet* bu = dynamic_cast<const Bullet*>(&a);
   const Ship* sh = dynamic_cast<const Ship*>(&b);
   if (bu && sh && bu->ignoresCollisionWith(*sh)) return true;
   bu = dynamic_cast<const Bullet*>(&b);
   sh = dynamic_cast<const Ship*>(&a);
   if (bu && sh && bu->ignoresCollisionWith(*sh)) return true;
   return false;
}

bool collide(const Satellite& a, const Satellite& b)
{
   if (a.isDead() || b.isDead()) return false;
   if (ignoreBulletVersusFiringShip(a, b)) return false;
   double d = computeDistance(a.getPosition(), b.getPosition());
   double sumR = radiusMeters(a.getRadius()) + radiusMeters(b.getRadius());
   return d <= sumR;
}

bool collideEarth(const Satellite& s, double earthRadius)
{
   if (s.isDead()) return false;
   double x = s.getPosition().getMetersX();
   double y = s.getPosition().getMetersY();
   double d = std::sqrt(x * x + y * y);
   return d <= earthRadius + radiusMeters(s.getRadius());
}

void resolveCollision(Satellite* a, Satellite* b, std::vector<Simulatable*>& bodies)
{
   if (!a || !b || a->isDead() || b->isDead()) return;
   if (ignoreBulletVersusFiringShip(*a, *b)) return;

   Bullet* buA = dynamic_cast<Bullet*>(a);
   Bullet* buB = dynamic_cast<Bullet*>(b);
   if (buA && buB)
   {
      a->kill();
      b->kill();
      return;
   }
   if (buA || buB)
   {
      Satellite* bullet = buA ? a : b;
      Satellite* other = buA ? b : a;
      bullet->kill();
      if (dynamic_cast<Fragment*>(other))
         other->kill();
      else
         other->destroy(bodies);
      return;
   }

   Part* pA = dynamic_cast<Part*>(a);
   Part* pB = dynamic_cast<Part*>(b);
   Fragment* fA = dynamic_cast<Fragment*>(a);
   Fragment* fB = dynamic_cast<Fragment*>(b);

   if (pA && fB)
   {
      pA->destroy(bodies);
      fB->kill();
      return;
   }
   if (pB && fA)
   {
      pB->destroy(bodies);
      fA->kill();
      return;
   }

   a->destroy(bodies);
   b->destroy(bodies);
}

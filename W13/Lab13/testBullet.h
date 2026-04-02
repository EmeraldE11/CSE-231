/***********************************************************************
 * testBullet.h
 * Unit tests for Bullet (ship-fired round, limited lifetime).
 ************************************************************************/

#pragma once

#include "bullet.h"
#include "satellite.h"
#include "testSatellite.h"
#include "uiDraw.h"
#include "unitTest.h"
#include <string>

class TestGoutBullet : public ogstream
{
public:
   TestGoutBullet() : ogstream() {}
   ~TestGoutBullet() { str(""); }
   void flush() override {}
   void drawProjectile(const Position&) override { *this << "Projectile"; }
};

class TestBullet : public UnitTest
{
public:
   void run()
   {
      constructor_setsPositionFromParentPlusOffset();
      constructor_setsVelocityFromKick();
      getRadius_usesFixedCollisionRadius();
      advance_expiresAfterLifetimeFrames();
      advance_velocityUnchangedByGravity();
      draw_writesProjectileMarkerToStream();
      destroy_defaultLeavesVectorUnchanged();
      report("Bullet");
   }

private:
   void constructor_setsPositionFromParentPlusOffset()
   {
      const double px = 1000000.0;
      const double py = 2000000.0;
      SatelliteFixture parent(px, py, 0.0, 0.0);
      Position off;
      off.setMeters(50.0, -30.0);
      Velocity kick(0.0, 0.0);
      Bullet b(parent, off, kick);
      assertEquals(b.getPosition().getMetersX(), px + 50.0);
      assertEquals(b.getPosition().getMetersY(), py - 30.0);
   }

   void constructor_setsVelocityFromKick()
   {
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(1500.0, -500.0);
      Bullet b(parent, off, kick);
      assertEquals(b.getVelocity().getDx(), 1500.0);
      assertEquals(b.getVelocity().getDy(), -500.0);
   }

   void getRadius_usesFixedCollisionRadius()
   {
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Bullet b(parent, off, kick);
      assertEquals(b.getRadius(), BULLET_RADIUS_PIXELS);
   }

   void advance_expiresAfterLifetimeFrames()
   {
      SatelliteFixture parent(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Bullet b(parent, off, kick);
      for (int i = 0; i < BULLET_LIFETIME_FRAMES; ++i)
         b.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      assertUnit(b.isDead());
   }

   void advance_velocityUnchangedByGravity()
   {
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(1200.0, -800.0);
      Bullet b(parent, off, kick);
      b.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      assertEquals(b.getVelocity().getDx(), 1200.0);
      assertEquals(b.getVelocity().getDy(), -800.0);
   }

   void draw_writesProjectileMarkerToStream()
   {
      SatelliteFixture parent(500000.0, -500000.0, 0.0, 2000.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 100.0);
      Bullet b(parent, off, kick);
      TestGoutBullet gout;
      b.draw(gout);
      assertUnit(gout.str().find("Projectile") != std::string::npos);
   }

   void destroy_defaultLeavesVectorUnchanged()
   {
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Bullet b(parent, off, kick);
      std::vector<Simulatable*> satellites;
      b.destroy(satellites);
      assertUnit(satellites.empty());
   }
};

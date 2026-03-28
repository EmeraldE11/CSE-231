/***********************************************************************
 * testPart.h
 * Unit tests for Part (via GPSPart). Each test: SETUP / EXERCISE / VERIFY / TEARDOWN;
 * EXERCISE is exactly one statement (the method under test); VERIFY is only asserts.
 ************************************************************************/

#pragma once

#include "part.h"
#include "partTypes.h"
#include "fragment.h"
#include "satellite.h"
#include "testSatellite.h"
#include "uiDraw.h"
#include "unitTest.h"
#include <cmath>
#include <string>

// Same pattern as TestGout in testDraw.h: ogstream::~ogstream calls flush(), which uses
// GLUT; clear the buffer in the derived destructor and override flush() so unit tests
// run without glutInit.
class TestGoutPart : public ogstream
{
public:
   TestGoutPart() : ogstream() {}
   ~TestGoutPart() { str(""); }
   void flush() override {}
   void drawProjectile(const Position&) override { *this << "Projectile"; }
};

class TestPart : public UnitTest
{
public:
   void run()
   {
      GPSPart_constructor_setsPositionFromParentPlusOffset();
      GPSPart_constructor_setsVelocityFromKick();
      GPSPart_getRadius_scalesWithZoom();
      GPSPart_kill_setsDeadFlag();
      GPSPart_draw_writesProjectileToStream();
      GPSPart_destroy_spawnsTwoFragments();
      GPSPart_destroy_doesNotKillPart();
      GPSPart_advance_whenDead_positionUnchanged();
      GPSPart_advance_whenAlive_positionChanges();
      GPSPart_advance_insideEarth_positionUnchanged();
      GPSPart_advance_atRest_negativeVerticalVelocityFromGravity();
      GPSPart_advance_rotatesDirectionByAngularVelocity();
      report("Part");
   }

private:
   static double getNormalizedDirectionDelta(double beforeRad, double afterRad)
   {
      double delta = afterRad - beforeRad;
      while (delta > M_PI)  delta -= 2.0 * M_PI;
      while (delta < -M_PI) delta += 2.0 * M_PI;
      return delta;
   }

   void GPSPart_constructor_setsPositionFromParentPlusOffset()
   {
      // SETUP
      const double px = 1000000.0;
      const double py = 2000000.0;
      const double expectedX = px + 50.0;
      const double expectedY = py - 75.0;
      SatelliteFixture parent(px, py, 0.0, 0.0);
      Position off;
      off.setMeters(50.0, -75.0);
      Velocity kick(0.0, 0.0);
      // EXERCISE
      GPSPart part(parent, off, kick);
      // VERIFY
      assertEquals(part.getPosition().getMetersX(), expectedX);
      assertEquals(part.getPosition().getMetersY(), expectedY);
      // TEARDOWN
      // (none)
   }

   void GPSPart_constructor_setsVelocityFromKick()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(333.0, -444.0);
      // EXERCISE
      GPSPart part(parent, off, kick);
      // VERIFY
      assertEquals(part.getVelocity().getDx(), 333.0);
      assertEquals(part.getVelocity().getDy(), -444.0);
      // TEARDOWN
      // (none)
   }

   void GPSPart_getRadius_scalesWithZoom()
   {
      // SETUP
      Position zoomProbe;
      double savedZoom = zoomProbe.getZoom();
      zoomProbe.setZoom(100.0);
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      // EXERCISE
      GPSPart part(parent, off, kick);
      // VERIFY
      assertEquals(part.getRadius(), 200.0);
      // TEARDOWN
      zoomProbe.setZoom(savedZoom);
   }

   void GPSPart_kill_setsDeadFlag()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 100.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      GPSPart part(parent, off, kick);
      // EXERCISE
      part.kill();
      // VERIFY
      assertUnit(part.isDead());
      // TEARDOWN
      // (none)
   }

   void GPSPart_draw_writesProjectileToStream()
   {
      // SETUP
      SatelliteFixture parent(1000000.0, 2000000.0, 1000.0, 0.0);
      Position off;
      off.setMeters(10.0, 0.0);
      Velocity kick(500.0, 100.0);
      GPSPart part(parent, off, kick);
      TestGoutPart gout;
      // EXERCISE
      part.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("Projectile") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void GPSPart_destroy_spawnsTwoFragments()
   {
      // SETUP
      SatelliteFixture parent(0.0, 0.0, 1000.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      GPSPart part(parent, off, kick);
      std::vector<Simulatable*> satellites;
      // EXERCISE
      part.destroy(satellites);
      // VERIFY
      assertUnit(satellites.size() == 2);
      assertUnit(dynamic_cast<Fragment*>(satellites[0]) != nullptr);
      assertUnit(dynamic_cast<Fragment*>(satellites[1]) != nullptr);
      // TEARDOWN
      for (Simulatable* p : satellites)
         delete p;
   }

   void GPSPart_destroy_doesNotKillPart()
   {
      // SETUP
      SatelliteFixture parent(0.0, 0.0, 1000.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      GPSPart part(parent, off, kick);
      std::vector<Simulatable*> satellites;
      // EXERCISE
      part.destroy(satellites);
      // VERIFY
      assertUnit(!part.isDead());
      // TEARDOWN
      for (Simulatable* p : satellites)
         delete p;
   }

   void GPSPart_advance_whenDead_positionUnchanged()
   {
      // SETUP
      SatelliteFixture parent(0.0, 0.0, 1000.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      GPSPart part(parent, off, kick);
      part.kill();
      double xBefore = part.getPosition().getMetersX();
      double yBefore = part.getPosition().getMetersY();
      // EXERCISE
      part.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEquals(part.getPosition().getMetersX(), xBefore);
      assertEquals(part.getPosition().getMetersY(), yBefore);
      // TEARDOWN
      // (none)
   }

   void GPSPart_advance_whenAlive_positionChanges()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      GPSPart part(parent, off, kick);
      double xBefore = part.getPosition().getMetersX();
      double yBefore = part.getPosition().getMetersY();
      // EXERCISE
      part.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(part.getPosition().getMetersX() != xBefore ||
                 part.getPosition().getMetersY() != yBefore);
      // TEARDOWN
      // (none)
   }

   void GPSPart_advance_insideEarth_positionUnchanged()
   {
      // SETUP
      double x0 = EARTH_RADIUS - 100.0;
      SatelliteFixture parent(x0, 0.0, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      GPSPart part(parent, off, kick);
      // EXERCISE
      part.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEquals(part.getPosition().getMetersX(), x0);
      assertEquals(part.getPosition().getMetersY(), 0.0);
      // TEARDOWN
      // (none)
   }

   void GPSPart_advance_atRest_negativeVerticalVelocityFromGravity()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      GPSPart part(parent, off, kick);
      // EXERCISE
      part.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(part.getVelocity().getDy() < 0.0);
      // TEARDOWN
      // (none)
   }

   void GPSPart_advance_rotatesDirectionByAngularVelocity()
   {
      // SETUP
      const double expectedSpinRad = 0.05;
      SatelliteFixture parent(0.0, GEO_DISTANCE, 1000.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      GPSPart part(parent, off, kick);
      double dirBefore = part.getDirectionRadians();
      // EXERCISE
      part.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEqualsTolerance(getNormalizedDirectionDelta(dirBefore, part.getDirectionRadians()), expectedSpinRad, 0.01);
      // TEARDOWN
      // (none)
   }
};

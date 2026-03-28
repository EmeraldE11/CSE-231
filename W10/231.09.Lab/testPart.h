/***********************************************************************
 * testPart.h
 * Unit tests for Part. SETUP / EXERCISE / VERIFY / TEARDOWN;
 * EXERCISE is a single call to the method under test; VERIFY is asserts only.
 ************************************************************************/

#pragma once

#include "part.h"
#include "fragment.h"
#include "satellite.h"
#include "testSatellite.h"
#include "uiDraw.h"
#include "unitTest.h"
#include <cmath>
#include <string>

class TestPart : public UnitTest
{
public:
   void run()
   {
      constructor_setsPositionFromParentPlusOffset();
      constructor_setsVelocityFromKick();
      getRadius_scalesWithZoom();
      kill_setsDeadFlag();
      draw_writesProjectileToStream();
      destroy_spawnsTwoFragments();
      destroy_doesNotKillPart();
      advance_deadPartPositionUnchanged();
      advance_livePartMoves();
      advance_insideEarth_noMovement();
      advance_gravityChangesVelocityTowardEarth();
      advance_spinRotatesDirectionByAngularVelocity();
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

   void constructor_setsPositionFromParentPlusOffset()
   {
      // SETUP
      const double px = 1000000.0;
      const double py = 2000000.0;
      SatelliteFixture parent(px, py, 0.0, 0.0);
      Position off;
      off.setMeters(50.0, -75.0);
      Velocity kick(0.0, 0.0);
      // EXERCISE
      Part part(parent, off, kick);
      // VERIFY
      assertEquals(part.getPosition().getMetersX(), px + 50.0);
      assertEquals(part.getPosition().getMetersY(), py - 75.0);
      // TEARDOWN
      // (none)
   }

   void constructor_setsVelocityFromKick()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(333.0, -444.0);
      // EXERCISE
      Part part(parent, off, kick);
      // VERIFY
      assertEquals(part.getVelocity().getDx(), 333.0);
      assertEquals(part.getVelocity().getDy(), -444.0);
      // TEARDOWN
      // (none)
   }

   void getRadius_scalesWithZoom()
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
      Part part(parent, off, kick);
      // VERIFY
      assertEquals(part.getRadius(), 200.0);
      // TEARDOWN
      zoomProbe.setZoom(savedZoom);
   }

   void kill_setsDeadFlag()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 100.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Part part(parent, off, kick);
      // EXERCISE
      part.kill();
      // VERIFY
      assertUnit(part.isDead());
      // TEARDOWN
      // (none)
   }

   void draw_writesProjectileToStream()
   {
      // SETUP
      SatelliteFixture parent(1000000.0, 2000000.0, 1000.0, 0.0);
      Position off;
      off.setMeters(10.0, 0.0);
      Velocity kick(500.0, 100.0);
      Part part(parent, off, kick);
      Position pt;
      ogstreamFake gout(pt);
      // EXERCISE
      part.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("Projectile") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void destroy_spawnsTwoFragments()
   {
      // SETUP
      SatelliteFixture parent(0.0, 0.0, 1000.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      Part part(parent, off, kick);
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

   void destroy_doesNotKillPart()
   {
      // SETUP
      SatelliteFixture parent(0.0, 0.0, 1000.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      Part part(parent, off, kick);
      std::vector<Simulatable*> satellites;
      // EXERCISE
      part.destroy(satellites);
      // VERIFY
      assertUnit(!part.isDead());
      // TEARDOWN
      for (Simulatable* p : satellites)
         delete p;
   }

   void advance_deadPartPositionUnchanged()
   {
      // SETUP
      SatelliteFixture parent(0.0, 0.0, 1000.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      Part part(parent, off, kick);
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

   void advance_livePartMoves()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Part part(parent, off, kick);
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

   void advance_insideEarth_noMovement()
   {
      // SETUP
      double x0 = EARTH_RADIUS - 100.0;
      SatelliteFixture parent(x0, 0.0, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Part part(parent, off, kick);
      // EXERCISE
      part.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEquals(part.getPosition().getMetersX(), x0);
      assertEquals(part.getPosition().getMetersY(), 0.0);
      // TEARDOWN
      // (none)
   }

   void advance_gravityChangesVelocityTowardEarth()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Part part(parent, off, kick);
      // EXERCISE
      part.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(part.getVelocity().getDy() < 0.0);
      // TEARDOWN
      // (none)
   }

   void advance_spinRotatesDirectionByAngularVelocity()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 1000.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(100.0, 0.0);
      Part part(parent, off, kick);
      double dirBefore = part.getDirectionRadians();
      // EXERCISE
      part.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEqualsTolerance(getNormalizedDirectionDelta(dirBefore, part.getDirectionRadians()), 0.05, 0.01);
      // TEARDOWN
      // (none)
   }
};

/***********************************************************************
 * testFragment.h
 * Unit tests for Fragment. Each test: SETUP / EXERCISE / VERIFY / TEARDOWN;
 * EXERCISE is exactly one statement (the method under test); VERIFY is only asserts.
 ************************************************************************/

#pragma once

#include "fragment.h"
#include "satellite.h"
#include "testSatellite.h"
#include "uiDraw.h"
#include "unitTest.h"
#include <cmath>
#include <string>

// Same pattern as TestGout in testDraw.h (see testPart.h / TestGoutPart).
class TestGoutFragment : public ogstream
{
public:
   TestGoutFragment() : ogstream() {}
   ~TestGoutFragment() { str(""); }
   void flush() override {}
   void drawFragment(const Position&, double) override { *this << "Fragment"; }
};

class TestFragment : public UnitTest
{
public:
   void run()
   {
      Fragment_constructor_setsPositionFromParentPlusOffset();
      Fragment_constructor_setsVelocityFromKick();
      Fragment_getRadius_scalesWithZoom();
      Fragment_kill_setsDeadFlag();
      Fragment_draw_writesFragmentToStream();
      Fragment_destroy_leavesVectorEmpty();
      Fragment_advance_whenDead_positionUnchanged();
      Fragment_advance_whenAlive_positionChanges();
      Fragment_advance_insideEarth_positionUnchanged();
      Fragment_advance_atRest_negativeVerticalVelocityFromGravity();
      Fragment_advance_rotatesDirectionByAngularVelocity();
      report("Fragment");
   }

private:
   static double getNormalizedDirectionDelta(double beforeRad, double afterRad)
   {
      double delta = afterRad - beforeRad;
      while (delta > M_PI)  delta -= 2.0 * M_PI;
      while (delta < -M_PI) delta += 2.0 * M_PI;
      return delta;
   }

   void Fragment_constructor_setsPositionFromParentPlusOffset()
   {
      // SETUP
      const double px = -500000.0;
      const double py = 750000.0;
      const double expectedX = px + 120.0;
      const double expectedY = py - 200.0;
      SatelliteFixture parent(px, py, 0.0, 0.0);
      Position off;
      off.setMeters(120.0, -200.0);
      Velocity kick(0.0, 0.0);
      // EXERCISE
      Fragment frag(parent, off, kick);
      // VERIFY
      assertEquals(frag.getPosition().getMetersX(), expectedX);
      assertEquals(frag.getPosition().getMetersY(), expectedY);
      // TEARDOWN
      // (none)
   }

   void Fragment_constructor_setsVelocityFromKick()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(-1200.0, 800.0);
      // EXERCISE
      Fragment frag(parent, off, kick);
      // VERIFY
      assertEquals(frag.getVelocity().getDx(), -1200.0);
      assertEquals(frag.getVelocity().getDy(), 800.0);
      // TEARDOWN
      // (none)
   }

   void Fragment_getRadius_scalesWithZoom()
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
      Fragment frag(parent, off, kick);
      // VERIFY
      assertEquals(frag.getRadius(), 100.0);
      // TEARDOWN
      zoomProbe.setZoom(savedZoom);
   }

   void Fragment_kill_setsDeadFlag()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 1000.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Fragment frag(parent, off, kick);
      // EXERCISE
      frag.kill();
      // VERIFY
      assertUnit(frag.isDead());
      // TEARDOWN
      // (none)
   }

   void Fragment_draw_writesFragmentToStream()
   {
      // SETUP
      SatelliteFixture parent(500000.0, -500000.0, 0.0, 2000.0);
      Position off;
      off.setMeters(5.0, 5.0);
      Velocity kick(300.0, -100.0);
      Fragment frag(parent, off, kick);
      TestGoutFragment gout;
      // EXERCISE
      frag.draw(gout);
      // VERIFY
      assertUnit(gout.str().find("Fragment") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void Fragment_destroy_leavesVectorEmpty()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Fragment frag(parent, off, kick);
      std::vector<Simulatable*> satellites;
      // EXERCISE
      frag.destroy(satellites);
      // VERIFY
      assertUnit(satellites.empty());
      // TEARDOWN
      // (none)
   }

   void Fragment_advance_whenDead_positionUnchanged()
   {
      // SETUP
      SatelliteFixture parent(0.0, 0.0, 0.0, 1000.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(50.0, 50.0);
      Fragment frag(parent, off, kick);
      frag.kill();
      double xBefore = frag.getPosition().getMetersX();
      double yBefore = frag.getPosition().getMetersY();
      // EXERCISE
      frag.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEquals(frag.getPosition().getMetersX(), xBefore);
      assertEquals(frag.getPosition().getMetersY(), yBefore);
      // TEARDOWN
      // (none)
   }

   void Fragment_advance_whenAlive_positionChanges()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Fragment frag(parent, off, kick);
      double xBefore = frag.getPosition().getMetersX();
      double yBefore = frag.getPosition().getMetersY();
      // EXERCISE
      frag.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(frag.getPosition().getMetersX() != xBefore ||
                 frag.getPosition().getMetersY() != yBefore);
      // TEARDOWN
      // (none)
   }

   void Fragment_advance_insideEarth_positionUnchanged()
   {
      // SETUP
      double x0 = EARTH_RADIUS - 50.0;
      SatelliteFixture parent(x0, 0.0, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Fragment frag(parent, off, kick);
      // EXERCISE
      frag.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEquals(frag.getPosition().getMetersX(), x0);
      assertEquals(frag.getPosition().getMetersY(), 0.0);
      // TEARDOWN
      // (none)
   }

   void Fragment_advance_atRest_negativeVerticalVelocityFromGravity()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 0.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Fragment frag(parent, off, kick);
      // EXERCISE
      frag.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(frag.getVelocity().getDy() < 0.0);
      // TEARDOWN
      // (none)
   }

   void Fragment_advance_rotatesDirectionByAngularVelocity()
   {
      // SETUP
      const double expectedSpinRad = 0.08;
      SatelliteFixture parent(0.0, GEO_DISTANCE, 500.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(200.0, 0.0);
      Fragment frag(parent, off, kick);
      double dirBefore = frag.getDirectionRadians();
      // EXERCISE
      frag.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEqualsTolerance(getNormalizedDirectionDelta(dirBefore, frag.getDirectionRadians()), expectedSpinRad, 0.01);
      // TEARDOWN
      // (none)
   }
};

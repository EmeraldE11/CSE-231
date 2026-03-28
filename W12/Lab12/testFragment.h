/***********************************************************************
 * testFragment.h
 * Unit tests for Fragment. SETUP / EXERCISE / VERIFY / TEARDOWN;
 * EXERCISE is a single call to the method under test; VERIFY is asserts only.
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
      constructor_setsPositionFromParentPlusOffset();
      constructor_setsVelocityFromKick();
      getRadius_scalesWithZoom();
      kill_setsDeadFlag();
      draw_writesFragmentToStream();
      destroy_defaultLeavesVectorUnchanged();
      advance_deadFragmentPositionUnchanged();
      advance_liveFragmentMoves();
      advance_insideEarth_noMovement();
      advance_gravityChangesVelocityTowardEarth();
      advance_spinRotatesDirectionByAngularVelocity();
      advance_expiresAfterLifetimeFrames();
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

   void constructor_setsPositionFromParentPlusOffset()
   {
      // SETUP
      const double px = -500000.0;
      const double py = 750000.0;
      SatelliteFixture parent(px, py, 0.0, 0.0);
      Position off;
      off.setMeters(120.0, -200.0);
      Velocity kick(0.0, 0.0);
      // EXERCISE
      Fragment frag(parent, off, kick);
      // VERIFY
      assertEquals(frag.getPosition().getMetersX(), px + 120.0);
      assertEquals(frag.getPosition().getMetersY(), py - 200.0);
      // TEARDOWN
      // (none)
   }

   void constructor_setsVelocityFromKick()
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
      Fragment frag(parent, off, kick);
      // VERIFY
      assertEquals(frag.getRadius(), 100.0);
      // TEARDOWN
      zoomProbe.setZoom(savedZoom);
   }

   void kill_setsDeadFlag()
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

   void draw_writesFragmentToStream()
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

   void destroy_defaultLeavesVectorUnchanged()
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

   void advance_deadFragmentPositionUnchanged()
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

   void advance_liveFragmentMoves()
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

   void advance_insideEarth_noMovement()
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

   void advance_gravityChangesVelocityTowardEarth()
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

   void advance_spinRotatesDirectionByAngularVelocity()
   {
      // SETUP
      SatelliteFixture parent(0.0, GEO_DISTANCE, 500.0, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(200.0, 0.0);
      Fragment frag(parent, off, kick);
      double dirBefore = frag.getDirectionRadians();
      // EXERCISE
      frag.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEqualsTolerance(getNormalizedDirectionDelta(dirBefore, frag.getDirectionRadians()), 0.08, 0.01);
      // TEARDOWN
      // (none)
   }

   void advance_expiresAfterLifetimeFrames()
   {
      SatelliteFixture parent(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0);
      Position off;
      off.setMeters(0.0, 0.0);
      Velocity kick(0.0, 0.0);
      Fragment frag(parent, off, kick);
      for (int i = 0; i < FRAGMENT_LIFETIME_FRAMES; ++i)
         frag.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      assertUnit(frag.isDead());
   }
};

/***********************************************************************
 * testSatellite.h
 * Unit tests for Satellite behavior using the Hubble concrete class
 * and a fixture with custom (x, y, vx, vy). Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "bullet.h"
#include "satellite.h"
#include "hubble.h"
#include "unitTest.h"
#include <cmath>

// Concrete Satellite for tests that need custom position/velocity or (parent, direction).
class SatelliteFixture : public Satellite
{
public:
   SatelliteFixture(double x, double y, double vx, double vy) : Satellite(x, y, vx, vy) {}
   SatelliteFixture(const Satellite& parent, const Direction& d) : Satellite(parent, d) {}
   void draw(ogstream&) override {}
};

class TestSatellite : public UnitTest
{
public:
   void run()
   {
      constructor_hubbleInitialState();
      kill_setsDeadFlag();
      advance_deadSatelliteDoesNotMove();
      advance_liveSatelliteMoves();
      advance_insideEarth_noMovement();
      advance_zeroDx_onlyDy_motionVertical();
      advance_zeroDy_onlyDx_motionHorizontal();
      advance_orbitApproximateRadiusConstant();
      advance_acceleratesTowardEarth();
      advance_zeroAngularVelocity_directionUnchanged();
      advance_gravityChangesVelocityTowardEarth();
      advance_spinRotatesDirectionByAngularVelocity();
      advance_inertiaVelocityProducesDisplacement();
      move_stationaryNorth();
      move_stationarySouth();
      move_stationaryEast();
      move_stationaryWest();
      constructor_stationaryNorth();
      constructor_stationarySouth();
      constructor_stationaryEast();
      constructor_stationaryWest();
      constructor_bulletFromParent();
      destroy_noOp();
      input_noOp();
      report("Satellite");
   }

private:
   void runAdvances(Satellite& sat, int frames)
   {
      for (int i = 0; i < frames; i++)
         sat.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
   }

   static double getNormalizedDirectionDelta(double beforeRad, double afterRad)
   {
      double delta = afterRad - beforeRad;
      while (delta > M_PI)  delta -= 2.0 * M_PI;
      while (delta < -M_PI) delta += 2.0 * M_PI;
      return delta;
   }

   void constructor_hubbleInitialState()
   {
      // SETUP
      // (none)
      // EXERCISE
      Hubble h;
      // VERIFY
      assertEquals(h.getPosition().getMetersX(), 0.0);
      assertEquals(h.getPosition().getMetersY(), -GEO_DISTANCE);
      assertEquals(h.getRadius(), 10.0);
      assertUnit(!h.isDead());
      // TEARDOWN
      // (none)
   }

   void kill_setsDeadFlag()
   {
      // SETUP
      Hubble h;
      // EXERCISE
      h.kill();
      // VERIFY
      assertUnit(h.isDead());
      // TEARDOWN
      // (none)
   }

   void advance_deadSatelliteDoesNotMove()
   {
      // SETUP
      Hubble h;
      h.kill();
      Position before = h.getPosition();
      // EXERCISE
      h.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEquals(h.getPosition().getMetersX(), before.getMetersX());
      assertEquals(h.getPosition().getMetersY(), before.getMetersY());
      // TEARDOWN
      // (none)
   }

   void advance_liveSatelliteMoves()
   {
      // SETUP
      Hubble h;
      Position before = h.getPosition();
      // EXERCISE
      h.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(h.getPosition().getMetersX() != before.getMetersX() ||
                h.getPosition().getMetersY() != before.getMetersY());
      // TEARDOWN
      // (none)
   }

   void advance_insideEarth_noMovement()
   {
      // SETUP
      double x0 = EARTH_RADIUS - 100.0;
      double y0 = 0.0;
      SatelliteFixture s(x0, y0, 0.0, 0.0);
      // EXERCISE
      s.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEquals(s.getPosition().getMetersX(), x0);
      assertEquals(s.getPosition().getMetersY(), y0);
      // TEARDOWN
      // (none)
   }

   void advance_zeroDx_onlyDy_motionVertical()
   {
      // SETUP
      double y0 = GEO_DISTANCE;
      double vy = -500.0;
      SatelliteFixture s(0.0, y0, 0.0, vy);
      Position before = s.getPosition();
      // EXERCISE
      s.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEqualsTolerance(s.getPosition().getMetersX(), 0.0, 1.0);
      assertUnit(s.getPosition().getMetersY() != before.getMetersY());
      // TEARDOWN
      // (none)
   }

   void advance_zeroDy_onlyDx_motionHorizontal()
   {
      // SETUP
      double y0 = GEO_DISTANCE;
      double vx = -500.0;
      SatelliteFixture s(0.0, y0, vx, 0.0);
      Position before = s.getPosition();
      // EXERCISE
      s.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(s.getPosition().getMetersX() != before.getMetersX());
      assertEqualsTolerance(s.getPosition().getMetersY(), y0, 100000.0);
      // TEARDOWN
      // (none)
   }

   void advance_orbitApproximateRadiusConstant()
   {
      // SETUP
      Hubble h;
      const int frames = 100;
      const double tol = 20000.0;
      // EXERCISE
      runAdvances(h, frames);
      // VERIFY
      assertEqualsTolerance(std::sqrt(h.getPosition().getMetersX() * h.getPosition().getMetersX() +
                                      h.getPosition().getMetersY() * h.getPosition().getMetersY()),
                           GEO_DISTANCE, tol);
      // TEARDOWN
      // (none)
   }

   void advance_acceleratesTowardEarth()
   {
      // SETUP
      SatelliteFixture s(0.0, GEO_DISTANCE, 0.0, 0.0);
      double distBefore = GEO_DISTANCE;
      // EXERCISE
      s.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(std::sqrt(s.getPosition().getMetersX() * s.getPosition().getMetersX() +
                           s.getPosition().getMetersY() * s.getPosition().getMetersY()) < distBefore);
      // TEARDOWN
      // (none)
   }

   void advance_zeroAngularVelocity_directionUnchanged()
   {
      // SETUP
      SatelliteFixture s(0.0, GEO_DISTANCE, -GEO_VELOCITY, 0.0);
      s.angularVelocity = 0.0;
      double dirBefore = s.getDirectionRadians();
      // EXERCISE
      s.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEquals(s.getDirectionRadians(), dirBefore);
      // TEARDOWN
      // (none)
   }

   // Gravity applies acceleration toward Earth; velocity gains a component toward origin.
   void advance_gravityChangesVelocityTowardEarth()
   {
      // SETUP
      SatelliteFixture s(0.0, GEO_DISTANCE, 0.0, 0.0);
      // EXERCISE
      s.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(s.getVelocity().getDy() < 0.0);
      // TEARDOWN
      // (none)
   }

   // Spin: direction rotates by angularVelocity radians per frame.
   void advance_spinRotatesDirectionByAngularVelocity()
   {
      // SETUP
      Hubble h;
      double dirBefore = h.getDirectionRadians();
      // EXERCISE
      h.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEqualsTolerance(getNormalizedDirectionDelta(dirBefore, h.getDirectionRadians()), 0.02, 0.005);
      // TEARDOWN
      // (none)
   }

   // Inertia: velocity carries the satellite; displacement has a term proportional to velocity.
   void advance_inertiaVelocityProducesDisplacement()
   {
      // SETUP
      double vx = 1000.0;
      SatelliteFixture s(0.0, GEO_DISTANCE, vx, 0.0);
      double xBefore = s.getPosition().getMetersX();
      double expectedInertial = vx * TIME_PER_FRAME;
      // EXERCISE
      s.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertEqualsTolerance(s.getPosition().getMetersX() - xBefore, expectedInertial, expectedInertial * 0.5);
      // TEARDOWN
      // (none)
   }

   // move() test: full initial state, move(1.0), verify position, velocity, angle, age, spin.
   void move_stationaryNorth()
   {
      // SETUP (just above surface so gravity applies: distance > EARTH_RADIUS)
      const double aboveSurface = 1000.0;
      SatelliteFixture s(0.0, EARTH_RADIUS + aboveSurface, 0.0, 0.0);
      s.direction.setRadians(1.234);
      s.angularVelocity = 0.0;
      s.dead = false;
      s.radius = 0.0;
      s.age = 100;
      const double timeStep = 1.0;
      const double tolVel = 0.5;
      const double tolPos = 2.0;
      double expectedY = (EARTH_RADIUS + aboveSurface) + 0.5 * (-GRAVITY_SEA_LEVEL) * timeStep * timeStep;
      // EXERCISE
      s.move(timeStep);
      // VERIFY
      assertEqualsTolerance(0.0, s.getVelocity().getDx(), tolVel);
      assertEqualsTolerance(-GRAVITY_SEA_LEVEL, s.getVelocity().getDy(), tolVel);
      assertEqualsTolerance(0.0, s.getPosition().getMetersX(), tolPos);
      assertEqualsTolerance(expectedY, s.getPosition().getMetersY(), tolPos);
      assertEqualsTolerance(s.getDirectionRadians(), 1.234, tolPos);
      assertEquals(s.age, 101);
      assertEquals(s.angularVelocity, 0.0);
      assertUnit(!s.isDead());
      assertEquals(s.radius, 0.0);
      // TEARDOWN
      // (none)
   }

   // move() test: stationary at south (negative Y); gravity pulls toward origin.
   void move_stationarySouth()
   {
      // SETUP (just outside surface so gravity applies)
      const double aboveSurface = 1000.0;
      SatelliteFixture s(0.0, -EARTH_RADIUS - aboveSurface, 0.0, 0.0);
      s.direction.setRadians(1.234);
      s.angularVelocity = 0.0;
      s.dead = false;
      s.radius = 0.0;
      s.age = 100;
      const double timeStep = 1.0;
      const double tolVel = 0.5;
      const double tolPos = 2.0;
      double expectedY = (-EARTH_RADIUS - aboveSurface) + 0.5 * GRAVITY_SEA_LEVEL * timeStep * timeStep;
      // EXERCISE
      s.move(timeStep);
      // VERIFY
      assertEqualsTolerance(0.0, s.getVelocity().getDx(), tolVel);
      assertEqualsTolerance(GRAVITY_SEA_LEVEL, s.getVelocity().getDy(), tolVel);
      assertEqualsTolerance(0.0, s.getPosition().getMetersX(), tolPos);
      assertEqualsTolerance(expectedY, s.getPosition().getMetersY(), tolPos);
      assertEqualsTolerance(s.getDirectionRadians(), 1.234, tolPos);
      assertEquals(s.age, 101);
      assertEquals(s.angularVelocity, 0.0);
      assertUnit(!s.isDead());
      assertEquals(s.radius, 0.0);
      // TEARDOWN
      // (none)
   }

   // move() test: stationary at east (positive X); gravity pulls toward origin.
   void move_stationaryEast()
   {
      // SETUP (just outside surface so gravity applies)
      const double aboveSurface = 1000.0;
      SatelliteFixture s(EARTH_RADIUS + aboveSurface, 0.0, 0.0, 0.0);
      s.direction.setRadians(1.234);
      s.angularVelocity = 0.0;
      s.dead = false;
      s.radius = 0.0;
      s.age = 100;
      const double timeStep = 1.0;
      const double tolVel = 0.5;
      const double tolPos = 2.0;
      double expectedX = (EARTH_RADIUS + aboveSurface) + 0.5 * (-GRAVITY_SEA_LEVEL) * timeStep * timeStep;
      // EXERCISE
      s.move(timeStep);
      // VERIFY
      assertEqualsTolerance(-GRAVITY_SEA_LEVEL, s.getVelocity().getDx(), tolVel);
      assertEqualsTolerance(0.0, s.getVelocity().getDy(), tolVel);
      assertEqualsTolerance(expectedX, s.getPosition().getMetersX(), tolPos);
      assertEqualsTolerance(0.0, s.getPosition().getMetersY(), tolPos);
      assertEqualsTolerance(s.getDirectionRadians(), 1.234, tolPos);
      assertEquals(s.age, 101);
      assertEquals(s.angularVelocity, 0.0);
      assertUnit(!s.isDead());
      assertEquals(s.radius, 0.0);
      // TEARDOWN
      // (none)
   }

   // move() test: stationary at west (negative X); gravity pulls toward origin.
   void move_stationaryWest()
   {
      // SETUP (just outside surface so gravity applies)
      const double aboveSurface = 1000.0;
      SatelliteFixture s(-EARTH_RADIUS - aboveSurface, 0.0, 0.0, 0.0);
      s.direction.setRadians(1.234);
      s.angularVelocity = 0.0;
      s.dead = false;
      s.radius = 0.0;
      s.age = 100;
      const double timeStep = 1.0;
      const double tolVel = 0.5;
      const double tolPos = 2.0;
      double expectedX = (-EARTH_RADIUS - aboveSurface) + 0.5 * GRAVITY_SEA_LEVEL * timeStep * timeStep;
      // EXERCISE
      s.move(timeStep);
      // VERIFY
      assertEqualsTolerance(GRAVITY_SEA_LEVEL, s.getVelocity().getDx(), tolVel);
      assertEqualsTolerance(0.0, s.getVelocity().getDy(), tolVel);
      assertEqualsTolerance(expectedX, s.getPosition().getMetersX(), tolPos);
      assertEqualsTolerance(0.0, s.getPosition().getMetersY(), tolPos);
      assertEqualsTolerance(s.getDirectionRadians(), 1.234, tolPos);
      assertEquals(s.age, 101);
      assertEquals(s.angularVelocity, 0.0);
      assertUnit(!s.isDead());
      assertEquals(s.radius, 0.0);
      // TEARDOWN
      // (none)
   }

   // Non-default constructor: inheriting from parent, kick in the northern direction.
   void constructor_stationaryNorth()
   {
      // SETUP
      SatelliteFixture sParent(512000000.0, 640000000.0, 0.0, 0.0);
      Direction north;
      north.setUp();
      // EXERCISE
      SatelliteFixture s(sParent, north);
      // VERIFY
      assertEqualsTolerance(0.0, s.getVelocity().getDx(), 250.3);
      assertEqualsTolerance(2000.0, s.getVelocity().getDy(), 1200.0);
      assertEqualsTolerance(512000000.0, s.getPosition().getMetersX(), 512000.0);
      assertEqualsTolerance(640000000.0, s.getPosition().getMetersY(), 512000.0);
      assertEqualsTolerance(s.getDirectionRadians(), M_PI / 2.0, 0.0001);
      assertUnit(!s.isDead());
      // TEARDOWN
      // (none)
   }

   // Non-default constructor: initially not moving but receive a kick in the south direction.
   void constructor_stationarySouth()
   {
      // SETUP
      SatelliteFixture sParent(512000000.0, 640000000.0, 0.0, 0.0);
      Direction south;
      south.setDown();
      // EXERCISE
      SatelliteFixture s(sParent, south);
      // VERIFY
      assertEqualsTolerance(0.0, s.getVelocity().getDx(), 250.0);
      assertEqualsTolerance(-2000.0, s.getVelocity().getDy(), 1200.0);
      assertEqualsTolerance(512000000.0, s.getPosition().getMetersX(), 512000.0);
      assertEqualsTolerance(640000000.0, s.getPosition().getMetersY(), 512000.0);
      assertEqualsTolerance(s.getDirectionRadians(), -M_PI / 2.0, 0.0001);
      assertUnit(!s.isDead());
      assertEquals(s.angularVelocity, 0.0);
      assertEquals(s.radius, 0.0);
      assertEquals(s.age, 0);
      // TEARDOWN
      // (none)
   }

   // Non-default constructor: initially not moving but receive a kick in the east direction.
   void constructor_stationaryEast()
   {
      // SETUP
      SatelliteFixture sParent(512000000.0, 640000000.0, 0.0, 0.0);
      Direction east;
      east.setRight();
      // EXERCISE
      SatelliteFixture s(sParent, east);
      // VERIFY
      assertEqualsTolerance(2000.0, s.getVelocity().getDx(), 250.0);
      assertEqualsTolerance(0.0, s.getVelocity().getDy(), 250.0);
      assertEqualsTolerance(512000000.0, s.getPosition().getMetersX(), 512000.0);
      assertEqualsTolerance(640000000.0, s.getPosition().getMetersY(), 512000.0);
      assertEqualsTolerance(s.getDirectionRadians(), 0.0, 0.0001);
      assertUnit(!s.isDead());
      assertEquals(s.angularVelocity, 0.0);
      assertEquals(s.radius, 0.0);
      assertEquals(s.age, 0);
      // TEARDOWN
      // (none)
   }

   // Non-default constructor: initially not moving but receive a kick in the west direction.
   void constructor_stationaryWest()
   {
      // SETUP
      SatelliteFixture sParent(512000000.0, 640000000.0, 0.0, 0.0);
      Direction west;
      west.setLeft();
      // EXERCISE
      SatelliteFixture s(sParent, west);
      // VERIFY
      assertEqualsTolerance(-2000.0, s.getVelocity().getDx(), 250.0);
      assertEqualsTolerance(0.0, s.getVelocity().getDy(), 250.0);
      assertEqualsTolerance(512000000.0, s.getPosition().getMetersX(), 512000.0);
      assertEqualsTolerance(640000000.0, s.getPosition().getMetersY(), 512000.0);
      assertEqualsTolerance(s.getDirectionRadians(), M_PI, 0.0001);
      assertUnit(!s.isDead());
      assertEquals(s.angularVelocity, 0.0);
      assertEquals(s.radius, 0.0);
      assertEquals(s.age, 0);
      // TEARDOWN
      // (none)
   }

   // Bullet constructor: position = parent + offset, velocity = kick.
   void constructor_bulletFromParent()
   {
      // SETUP
      SatelliteFixture parent(1000000.0, 2000000.0, -100.0, 50.0);
      Position offset(500000.0, 300000.0);
      Velocity kick(200.0, -150.0);
      // EXERCISE
      Bullet p(parent, offset, kick);
      // VERIFY
      assertEqualsTolerance(p.getPosition().getMetersX(), 1500000.0, 1.0);
      assertEqualsTolerance(p.getPosition().getMetersY(), 2300000.0, 1.0);
      assertEquals(p.getVelocity().getDx(), 200.0);
      assertEquals(p.getVelocity().getDy(), -150.0);
      assertUnit(!p.isDead());
      assertUnit(p.getRadius() >= 0.0);
      // TEARDOWN
      // (none)
   }

   // destroy() default on SatelliteFixture: base Satellite::destroy is a no-op.
   void destroy_noOp()
   {
      // SETUP
      SatelliteFixture f(0.0, 0.0, 1000.0, 0.0);
      std::vector<Simulatable*> satellites;
      // EXERCISE
      f.destroy(satellites);
      // VERIFY
      assertUnit(satellites.empty());
      assertUnit(!f.isDead());
      // TEARDOWN
      // (none)
   }

   // input() stub: call with nullptr and list; no crash, list unchanged.
   void input_noOp()
   {
      // SETUP
      Hubble h;
      std::vector<Simulatable*> satellites;
      // EXERCISE
      h.input(nullptr, satellites);
      // VERIFY
      assertUnit(satellites.empty());
      assertUnit(!h.isDead());
      // TEARDOWN
      // (none)
   }
};


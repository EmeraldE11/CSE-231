/***********************************************************************
 * testPhysics.h
 * Unit tests for physics helpers: getGravity, updateVelocity, updatePosition.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "satellite.h"
#include "unitTest.h"

class TestPhysics : public UnitTest
{
public:
   void run()
   {
      getGravity_aboveEarth_pointsTowardOrigin();
      getGravity_atOrigin_returnsZero();
      updateVelocity_addsAccelerationTimesTime();
      updatePosition_updatesPositionFromVelocityAndAcceleration();
      report("Physics");
   }

private:
   void getGravity_aboveEarth_pointsTowardOrigin()
   {
      // SETUP
      Position pos;
      pos.setMeters(0.0, EARTH_RADIUS + 1000000.0);
      double earthRadius = EARTH_RADIUS;
      double gravitySeaLevel = GRAVITY_SEA_LEVEL;
      // EXERCISE
      Acceleration a = getGravity(pos, earthRadius, gravitySeaLevel);
      // VERIFY
      assertUnit(a.getDDy() < 0.0);
      assertEqualsTolerance(a.getDDx(), 0.0, 0.0001);
      // TEARDOWN
      // (none)
   }

   void getGravity_atOrigin_returnsZero()
   {
      // SETUP
      Position pos;
      pos.setMeters(0.0, 0.0);
      double earthRadius = EARTH_RADIUS;
      double gravitySeaLevel = GRAVITY_SEA_LEVEL;
      // EXERCISE
      Acceleration a = getGravity(pos, earthRadius, gravitySeaLevel);
      // VERIFY
      assertEquals(a.getDDx(), 0.0);
      assertEquals(a.getDDy(), 0.0);
      // TEARDOWN
      // (none)
   }

   void updateVelocity_addsAccelerationTimesTime()
   {
      // SETUP
      Velocity v;
      v.setDx(0.0);
      v.setDy(0.0);
      Acceleration a(2.0, 3.0);
      double time = 4.0;
      // EXERCISE
      updateVelocity(v, a, time);
      // VERIFY
      assertEquals(v.getDx(), 8.0);
      assertEquals(v.getDy(), 12.0);
      // TEARDOWN
      // (none)
   }

   void updatePosition_updatesPositionFromVelocityAndAcceleration()
   {
      // SETUP
      Position pos;
      pos.setMeters(0.0, 0.0);
      Velocity v(10.0, 0.0);
      Acceleration a(0.0, 0.0);
      double time = 2.0;
      // EXERCISE
      updatePosition(pos, v, a, time);
      // VERIFY
      assertEquals(pos.getMetersX(), 20.0);
      assertEquals(pos.getMetersY(), 0.0);
      // TEARDOWN
      // (none)
   }
};

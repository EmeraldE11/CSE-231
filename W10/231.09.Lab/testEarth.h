/***********************************************************************
 * testEarth.h
 * Unit tests for the Earth class.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "satellite.h"
#include "unitTest.h"

class TestEarth : public UnitTest
{
public:
   void run()
   {
      constructor_earthInitialState();
      advance_rotatesAngle();
      report("Earth");
   }

private:
   void constructor_earthInitialState()
   {
      // SETUP
      // (none)
      // EXERCISE
      Earth e;
      // VERIFY
      assertEquals(e.position.getMetersX(), 0.0);
      assertEquals(e.position.getMetersY(), 0.0);
      assertEquals(e.angle.getRadians(), 0.0);
      // TEARDOWN
      // (none)
   }

   void advance_rotatesAngle()
   {
      // SETUP
      Earth e;
      double angleBefore = e.angle.getRadians();
      // EXERCISE
      e.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(e.angle.getRadians() != angleBefore);
      assertEquals(e.position.getMetersX(), 0.0);
      assertEquals(e.position.getMetersY(), 0.0);
      // TEARDOWN
      // (none)
   }
};

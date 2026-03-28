/***********************************************************************
 * testStarlink.h
 * Unit tests for the Starlink satellite class.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "starlink.h"
#include "unitTest.h"

class TestStarlink : public UnitTest
{
public:
   void run()
   {
      constructor_starlinkInitialState();
      kill_setsDeadFlag();
      advance_liveStarlinkMoves();
      report("Starlink");
   }

private:
   void constructor_starlinkInitialState()
   {
      // SETUP
      // (none)
      // EXERCISE
      Starlink s;
      // VERIFY
      assertEquals(s.getPosition().getMetersX(), 0.0);
      assertEquals(s.getPosition().getMetersY(), -13020000.0);
      assertEquals(s.getVelocity().getDx(), 5800.0);
      assertEquals(s.getVelocity().getDy(), 0.0);
      assertEquals(s.getRadius(), 6.0);
      assertUnit(!s.isDead());
      // TEARDOWN
      // (none)
   }

   void kill_setsDeadFlag()
   {
      // SETUP
      Starlink s;
      // EXERCISE
      s.kill();
      // VERIFY
      assertUnit(s.isDead());
      // TEARDOWN
      // (none)
   }

   void advance_liveStarlinkMoves()
   {
      // SETUP
      Starlink s;
      double xBefore = s.getPosition().getMetersX();
      double yBefore = s.getPosition().getMetersY();
      // EXERCISE
      s.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(s.getPosition().getMetersX() != xBefore ||
                 s.getPosition().getMetersY() != yBefore);
      // TEARDOWN
      // (none)
   }
};

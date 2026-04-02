/***********************************************************************
 * testSputnik.h
 * Unit tests for the Sputnik satellite class.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "sputnik.h"
#include "unitTest.h"

class TestSputnik : public UnitTest
{
public:
   void run()
   {
      constructor_sputnikInitialState();
      kill_setsDeadFlag();
      advance_liveSputnikMoves();
      report("Sputnik");
   }

private:
   void constructor_sputnikInitialState()
   {
      // SETUP
      // (none)
      // EXERCISE
      Sputnik s;
      // VERIFY
      assertEqualsTolerance(s.getPosition().getMetersX(), -36515095.13, 0.01);
      assertEquals(s.getPosition().getMetersY(), 21082000.0);
      assertEquals(s.getVelocity().getDx(), 2050.0);
      assertEquals(s.getVelocity().getDy(), 2684.68);
      assertEquals(s.getRadius(), 4.0);
      assertUnit(!s.isDead());
      // TEARDOWN
      // (none)
   }

   void kill_setsDeadFlag()
   {
      // SETUP
      Sputnik s;
      // EXERCISE
      s.kill();
      // VERIFY
      assertUnit(s.isDead());
      // TEARDOWN
      // (none)
   }

   void advance_liveSputnikMoves()
   {
      // SETUP
      Sputnik s;
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

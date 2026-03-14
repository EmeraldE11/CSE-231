/***********************************************************************
 * testCrewDragon.h
 * Unit tests for the CrewDragon satellite class.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "crewDragon.h"
#include "unitTest.h"

class TestCrewDragon : public UnitTest
{
public:
   void run()
   {
      constructor_crewDragonInitialState();
      kill_setsDeadFlag();
      advance_liveCrewDragonMoves();
      report("CrewDragon");
   }

private:
   void constructor_crewDragonInitialState()
   {
      // SETUP
      // (none)
      // EXERCISE
      CrewDragon c;
      // VERIFY
      assertEquals(c.getPosition().getMetersX(), 0.0);
      assertEquals(c.getPosition().getMetersY(), 8000000.0);
      assertEquals(c.getVelocity().getDx(), -7900.0);
      assertEquals(c.getVelocity().getDy(), 0.0);
      assertEquals(c.getRadius(), 7.0);
      assertUnit(!c.isDead());
      // TEARDOWN
      // (none)
   }

   void kill_setsDeadFlag()
   {
      // SETUP
      CrewDragon c;
      // EXERCISE
      c.kill();
      // VERIFY
      assertUnit(c.isDead());
      // TEARDOWN
      // (none)
   }

   void advance_liveCrewDragonMoves()
   {
      // SETUP
      CrewDragon c;
      double xBefore = c.getPosition().getMetersX();
      double yBefore = c.getPosition().getMetersY();
      // EXERCISE
      c.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(c.getPosition().getMetersX() != xBefore ||
                 c.getPosition().getMetersY() != yBefore);
      // TEARDOWN
      // (none)
   }
};

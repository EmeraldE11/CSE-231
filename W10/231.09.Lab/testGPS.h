/***********************************************************************
 * testGPS.h
 * Unit tests for the GPS satellite class.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "satellite.h"
#include "unitTest.h"

class TestGPS : public UnitTest
{
public:
   void run()
   {
      constructor_gpsInitialState();
      kill_setsDeadFlag();
      report("GPS");
   }

private:
   void constructor_gpsInitialState()
   {
      // SETUP
      // (none)
      // EXERCISE
      GPS g;
      // VERIFY
      assertEquals(g.getPosition().getMetersX(), 0.0);
      assertEquals(g.getPosition().getMetersY(), GEO_DISTANCE);
      assertEquals(g.getRadius(), 10.0);
      assertUnit(!g.isDead());
      // TEARDOWN
      // (none)
   }

   void kill_setsDeadFlag()
   {
      // SETUP
      GPS g;
      // EXERCISE
      g.kill();
      // VERIFY
      assertUnit(g.isDead());
      // TEARDOWN
      // (none)
   }
};


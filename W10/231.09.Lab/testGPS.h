/***********************************************************************
 * testGPS.h
 * Unit tests for the GPS satellite class.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "gps.h"
#include "unitTest.h"

class TestGPS : public UnitTest
{
public:
   void run()
   {
      constructor_gpsInitialState();
      constructor_gpsWithCoordinates();
      kill_setsDeadFlag();
      advance_liveGpsMoves();
      destroy_spawnsPartsAndFragments();
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
      assertEquals(g.getPosition().getMetersY(), GPS_DISTANCE);
      assertEquals(g.getRadius(), 12.0);
      assertUnit(!g.isDead());
      // TEARDOWN
      // (none)
   }

   void constructor_gpsWithCoordinates()
   {
      // SETUP
      const double x = 23001634.72;
      const double y = 13280000.0;
      const double vx = -1940.0;
      const double vy = 3360.18;
      // EXERCISE
      GPS g(x, y, vx, vy);
      // VERIFY
      assertEqualsTolerance(g.getPosition().getMetersX(), x, 0.01);
      assertEqualsTolerance(g.getPosition().getMetersY(), y, 0.01);
      assertEqualsTolerance(g.getVelocity().getDx(), vx, 0.01);
      assertEqualsTolerance(g.getVelocity().getDy(), vy, 0.01);
      assertEquals(g.getRadius(), 12.0);
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

   void advance_liveGpsMoves()
   {
      // SETUP
      GPS g;
      double xBefore = g.getPosition().getMetersX();
      double yBefore = g.getPosition().getMetersY();
      // EXERCISE
      g.advance(TIME_PER_FRAME, EARTH_RADIUS, GRAVITY_SEA_LEVEL);
      // VERIFY
      assertUnit(g.getPosition().getMetersX() != xBefore ||
                 g.getPosition().getMetersY() != yBefore);
      // TEARDOWN
      // (none)
   }

   void destroy_spawnsPartsAndFragments()
   {
      // SETUP
      GPS g;
      std::vector<Simulatable*> bodies;
      // EXERCISE
      g.destroy(bodies);
      // VERIFY
      assertUnit(bodies.size() == 5);
      // TEARDOWN
      for (Simulatable* p : bodies)
         delete p;
   }
};


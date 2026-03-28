/***********************************************************************
 * testGPS.h
 * Unit tests for the GPS satellite class.
 * Each test: SETUP / EXERCISE / VERIFY / TEARDOWN; EXERCISE one statement; VERIFY asserts only.
 ************************************************************************/

#pragma once

#include "gps.h"
#include "fragment.h"
#include "partTypes.h"
#include "unitTest.h"

class TestGPS : public UnitTest
{
public:
   void run()
   {
      GPS_constructor_default_initialState();
      GPS_constructor_withCoordinates_setsState();
      GPS_kill_setsDeadFlag();
      GPS_advance_whenAlive_positionChanges();
      GPS_destroy_spawnsGpsPartsAndFragments();
      report("GPS");
   }

private:
   void GPS_constructor_default_initialState()
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

   void GPS_constructor_withCoordinates_setsState()
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

   void GPS_kill_setsDeadFlag()
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

   void GPS_advance_whenAlive_positionChanges()
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

   void GPS_destroy_spawnsGpsPartsAndFragments()
   {
      // SETUP
      GPS g;
      std::vector<Simulatable*> bodies;
      // EXERCISE
      g.destroy(bodies);
      // VERIFY
      assertUnit(bodies.size() == 5);
      assertUnit(dynamic_cast<GPSPart*>(bodies[0]) != nullptr);
      assertUnit(dynamic_cast<GPSPart*>(bodies[1]) != nullptr);
      assertUnit(dynamic_cast<GPSPart*>(bodies[2]) != nullptr);
      assertUnit(dynamic_cast<Fragment*>(bodies[3]) != nullptr);
      assertUnit(dynamic_cast<Fragment*>(bodies[4]) != nullptr);
      // TEARDOWN
      for (Simulatable* p : bodies)
         delete p;
   }
};

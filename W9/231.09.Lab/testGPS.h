/***********************************************************************
 * testGPS.h
 * Unit tests for GPS: getRadius, isDead, getPosition, kill.
 ************************************************************************/

#pragma once

#include "satellite.h"
#include "unitTest.h"

class TestGPS : public UnitTest
{
public:
   void run()
   {
      getRadius();
      isDead();
      getPosition();
      kill();
      report("GPS");
   }

private:
   void getRadius()
   {
      GPS g;
      assertEquals(g.getRadius(), 10.0);
   }

   void isDead()
   {
      GPS g;
      assertUnit(!g.isDead());
   }

   void getPosition()
   {
      GPS g;
      const Position& p = g.getPosition();
      assertEquals(p.getMetersX(), 0.0);
      assertEquals(p.getMetersY(), 42164000.0);
   }

   void kill()
   {
      GPS g;
      g.kill();
      assertUnit(g.isDead());
   }
};

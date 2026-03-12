/***********************************************************************
 * testSatellite.h
 * Unit tests for Satellite (via Hubble): getRadius, isDead, getPosition, kill.
 ************************************************************************/

#pragma once

#include "satellite.h"
#include "unitTest.h"

class TestSatellite : public UnitTest
{
public:
   void run()
   {
      getRadius();
      isDead();
      getPosition();
      kill();
      report("Satellite");
   }

private:
   void getRadius()
   {
      Hubble h;
      assertEquals(h.getRadius(), 10.0);
   }

   void isDead()
   {
      Hubble h;
      assertUnit(!h.isDead());
   }

   void getPosition()
   {
      Hubble h;
      const Position& p = h.getPosition();
      assertEquals(p.getMetersX(), 0.0);
      assertEquals(p.getMetersY(), 42164000.0);
   }

   void kill()
   {
      Hubble h;
      h.kill();
      assertUnit(h.isDead());
   }
};

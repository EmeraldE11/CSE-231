/***********************************************************************
 * testAcceleration.h
 * Unit tests for Acceleration: constructors, assign, getDDx/getDDy, getVelocity(time).
 ************************************************************************/

#pragma once

#include "acceleration.h"
#include "unitTest.h"

class TestAcceleration : public UnitTest
{
public:
   void run()
   {
      construct_default();
      construct_components();
      assign();
      getDDx_getDDy();
      getVelocity();
      report("Acceleration");
   }

private:
   void construct_default()
   {
      Acceleration a;
      assertEquals(a.getDDx(), 0.0);
      assertEquals(a.getDDy(), 0.0);
   }

   void construct_components()
   {
      Acceleration a(2.0, 3.0);
      assertEquals(a.getDDx(), 2.0);
      assertEquals(a.getDDy(), 3.0);
   }

   void assign()
   {
      Acceleration x(1.0, 2.0);
      Acceleration y;
      y.assign(x);
      assertEquals(y.getDDx(), 1.0);
      assertEquals(y.getDDy(), 2.0);
   }

   void getDDx_getDDy()
   {
      Acceleration a(5.0, -4.0);
      assertEquals(a.getDDx(), 5.0);
      assertEquals(a.getDDy(), -4.0);
   }

   void getVelocity()
   {
      Acceleration a(10.0, 20.0);
      Velocity v = a.getVelocity(0.5);
      assertEquals(v.getDx(), 5.0);
      assertEquals(v.getDy(), 10.0);
   }
};

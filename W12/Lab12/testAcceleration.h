/***********************************************************************
 * testAcceleration.h
 * Unit tests for Acceleration.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "acceleration.h"
#include "unitTest.h"

class TestAcceleration : public UnitTest
{
public:
   void run()
   {
      constructor_default_zero();
      constructor_components_nonZero();
      assign_copyFromOther();
      getDDxDDy_returnsComponents();
      getVelocity_scalesByTime();
      report("Acceleration");
   }

private:
   void constructor_default_zero()
   {
      // SETUP
      // (none)
      // EXERCISE
      Acceleration a;
      // VERIFY
      assertEquals(a.getDDx(), 0.0);
      assertEquals(a.getDDy(), 0.0);
      // TEARDOWN
      // (none)
   }

   void constructor_components_nonZero()
   {
      // SETUP
      // (none)
      // EXERCISE
      Acceleration a(2.0, 3.0);
      // VERIFY
      assertEquals(a.getDDx(), 2.0);
      assertEquals(a.getDDy(), 3.0);
      // TEARDOWN
      // (none)
   }

   void assign_copyFromOther()
   {
      // SETUP
      Acceleration source(1.0, 2.0);
      Acceleration target;
      // EXERCISE
      target.assign(source);
      // VERIFY
      assertEquals(target.getDDx(), 1.0);
      assertEquals(target.getDDy(), 2.0);
      // TEARDOWN
      // (none)
   }

   void getDDxDDy_returnsComponents()
   {
      // SETUP
      Acceleration a(5.0, -4.0);
      // EXERCISE
      double ddx = a.getDDx();
      double ddy = a.getDDy();
      // VERIFY
      assertEquals(ddx, 5.0);
      assertEquals(ddy, -4.0);
      // TEARDOWN
      // (none)
   }

   void getVelocity_scalesByTime()
   {
      // SETUP
      Acceleration a(10.0, 20.0);
      // EXERCISE
      Velocity v = a.getVelocity(0.5);
      // VERIFY
      assertEquals(v.getDx(), 5.0);
      assertEquals(v.getDy(), 10.0);
      // TEARDOWN
      // (none)
   }
};


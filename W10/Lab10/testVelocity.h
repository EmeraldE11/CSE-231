/***********************************************************************
 * testVelocity.h
 * Unit tests for Velocity.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "velocity.h"
#include "unitTest.h"

class TestVelocity : public UnitTest
{
public:
   void run()
   {
      constructor_default_zero();
      constructor_components_nonZero();
      assign_copyFromOther();
      getDxDy_returnsComponents();
      setDxDy_overwritesComponents();
      getSpeed_threeFourFive();
      setSpeed_scalesMagnitude();
      getDirection_fromVector();
      setDirection_keepsSpeed();
      addDxDy_addsInPlace();
      add_addsOtherVector();
      report("Velocity");
   }

private:
   void constructor_default_zero()
   {
      // SETUP
      // (none)
      // EXERCISE
      Velocity v;
      // VERIFY
      assertEquals(v.getDx(), 0.0);
      assertEquals(v.getDy(), 0.0);
      // TEARDOWN
      // (none)
   }

   void constructor_components_nonZero()
   {
      // SETUP
      // (none)
      // EXERCISE
      Velocity v(3.0, 4.0);
      // VERIFY
      assertEquals(v.getDx(), 3.0);
      assertEquals(v.getDy(), 4.0);
      // TEARDOWN
      // (none)
   }

   void assign_copyFromOther()
   {
      // SETUP
      Velocity source(1.0, 2.0);
      Velocity target;
      // EXERCISE
      target.assign(source);
      // VERIFY
      assertEquals(target.getDx(), 1.0);
      assertEquals(target.getDy(), 2.0);
      // TEARDOWN
      // (none)
   }

   void getDxDy_returnsComponents()
   {
      // SETUP
      Velocity v(5.0, -3.0);
      // EXERCISE
      double dx = v.getDx();
      double dy = v.getDy();
      // VERIFY
      assertEquals(dx, 5.0);
      assertEquals(dy, -3.0);
      // TEARDOWN
      // (none)
   }

   void setDxDy_overwritesComponents()
   {
      // SETUP
      Velocity v;
      // EXERCISE
      v.setDx(10.0);
      v.setDy(20.0);
      // VERIFY
      assertEquals(v.getDx(), 10.0);
      assertEquals(v.getDy(), 20.0);
      // TEARDOWN
      // (none)
   }

   void getSpeed_threeFourFive()
   {
      // SETUP
      Velocity v(3.0, 4.0);
      // EXERCISE
      double speed = v.getSpeed();
      // VERIFY
      assertEquals(speed, 5.0);
      // TEARDOWN
      // (none)
   }

   void setSpeed_scalesMagnitude()
   {
      // SETUP
      Velocity v(3.0, 4.0);
      // EXERCISE
      v.setSpeed(10.0);
      // VERIFY
      assertEquals(v.getSpeed(), 10.0);
      assertEqualsTolerance(v.getDx(), 6.0, 0.0001);
      assertEqualsTolerance(v.getDy(), 8.0, 0.0001);
      // TEARDOWN
      // (none)
   }

   void getDirection_fromVector()
   {
      // SETUP
      Velocity v(1.0, 0.0);
      // EXERCISE
      Direction d = v.getDirection();
      // VERIFY
      assertEqualsTolerance(d.getRadians(), 0.0, 0.0001);
      // TEARDOWN
      // (none)
   }

   void setDirection_keepsSpeed()
   {
      // SETUP
      Velocity v(3.0, 4.0); // speed 5
      Direction up;
      up.setUp();
      // EXERCISE
      v.setDirection(up);
      // VERIFY
      assertEqualsTolerance(v.getDx(), 0.0, 0.0001);
      assertEqualsTolerance(v.getDy(), 5.0, 0.0001);
      // TEARDOWN
      // (none)
   }

   void addDxDy_addsInPlace()
   {
      // SETUP
      Velocity v(1.0, 2.0);
      // EXERCISE
      v.addDx(0.5);
      v.addDy(-0.5);
      // VERIFY
      assertEquals(v.getDx(), 1.5);
      assertEquals(v.getDy(), 1.5);
      // TEARDOWN
      // (none)
   }

   void add_addsOtherVector()
   {
      // SETUP
      Velocity a(1.0, 2.0);
      Velocity b(3.0, 4.0);
      // EXERCISE
      a.add(b);
      // VERIFY
      assertEquals(a.getDx(), 4.0);
      assertEquals(a.getDy(), 6.0);
      // TEARDOWN
      // (none)
   }
};


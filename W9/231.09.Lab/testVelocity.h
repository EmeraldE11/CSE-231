/***********************************************************************
 * testVelocity.h
 * Unit tests for Velocity: constructors, assign, get/set dx/dy, getSpeed,
 * setSpeed, setDirection, getDirection, addDx/addDy, add(Velocity).
 ************************************************************************/

#pragma once

#include "velocity.h"
#include "unitTest.h"

class TestVelocity : public UnitTest
{
public:
   void run()
   {
      construct_default();
      construct_components();
      assign();
      getDx_getDy();
      setDx_setDy();
      getSpeed();
      setSpeed();
      getDirection_setDirection();
      addDx_addDy();
      add();
      report("Velocity");
   }

private:
   void construct_default()
   {
      Velocity v;
      assertEquals(v.getDx(), 0.0);
      assertEquals(v.getDy(), 0.0);
   }

   void construct_components()
   {
      Velocity v(3.0, 4.0);
      assertEquals(v.getDx(), 3.0);
      assertEquals(v.getDy(), 4.0);
   }

   void assign()
   {
      Velocity a(1.0, 2.0);
      Velocity b;
      b.assign(a);
      assertEquals(b.getDx(), 1.0);
      assertEquals(b.getDy(), 2.0);
   }

   void getDx_getDy()
   {
      Velocity v(5.0, -3.0);
      assertEquals(v.getDx(), 5.0);
      assertEquals(v.getDy(), -3.0);
   }

   void setDx_setDy()
   {
      Velocity v;
      v.setDx(10.0);
      v.setDy(20.0);
      assertEquals(v.getDx(), 10.0);
      assertEquals(v.getDy(), 20.0);
   }

   void getSpeed()
   {
      Velocity v(3.0, 4.0);
      assertEquals(v.getSpeed(), 5.0);
   }

   void setSpeed()
   {
      Velocity v(3.0, 4.0);
      v.setSpeed(10.0);
      assertEquals(v.getSpeed(), 10.0);
      assertEqualsTolerance(v.getDx(), 6.0, 0.0001);
      assertEqualsTolerance(v.getDy(), 8.0, 0.0001);
   }

   void getDirection_setDirection()
   {
      Velocity v(1.0, 0.0);
      Direction d = v.getDirection();
      assertEqualsTolerance(d.getRadians(), 0.0, 0.0001);
      Direction d2;
      d2.setUp();
      v.setDirection(d2);
      assertEqualsTolerance(v.getDx(), 0.0, 0.0001);
      assertEquals(v.getDy(), 1.0);
   }

   void addDx_addDy()
   {
      Velocity v(1.0, 2.0);
      v.addDx(0.5);
      v.addDy(-0.5);
      assertEquals(v.getDx(), 1.5);
      assertEquals(v.getDy(), 1.5);
   }

   void add()
   {
      Velocity a(1.0, 2.0);
      Velocity b(3.0, 4.0);
      a.add(b);
      assertEquals(a.getDx(), 4.0);
      assertEquals(a.getDy(), 6.0);
   }
};

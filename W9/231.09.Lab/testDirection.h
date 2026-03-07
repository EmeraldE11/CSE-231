/***********************************************************************
 * testDirection.h
 * Unit tests for the Direction class: constructors, set/get radians/degrees,
 * getDx/getDy, setUp/Down/Left/Right, rotate, setDxDy.
 ************************************************************************/

#pragma once

#include "direction.h"
#include "unitTest.h"

class TestDirection : public UnitTest
{
public:
   void run()
   {
      construct_default();
      construct_radians();
      setRadians_getRadians();
      setDegrees_getDegrees();
      getDx_getDy();
      setUp();
      setDown();
      setLeft();
      setRight();
      rotate();
      setDxDy();
      report("Direction");
   }

private:
   void construct_default()
   {
      Direction d;
      assertEquals(d.getRadians(), 0.0);
   }

   void construct_radians()
   {
      Direction d(1.5);
      assertEquals(d.getRadians(), 1.5);
   }

   void setRadians_getRadians()
   {
      Direction d;
      d.setRadians(2.0);
      assertEquals(d.getRadians(), 2.0);
   }

   void setDegrees_getDegrees()
   {
      Direction d;
      d.setDegrees(90.0);
      assertEquals(d.getDegrees(), 90.0);
   }

   void getDx_getDy()
   {
      Direction d;
      d.setRadians(0.0);
      assertEquals(d.getDx(), 1.0);
      assertEquals(d.getDy(), 0.0);
      d.setRadians(3.14159265358979323846 / 2.0);
      assertEqualsTolerance(d.getDx(), 0.0, 0.0001);
      assertEquals(d.getDy(), 1.0);
   }

   void setUp()
   {
      Direction d;
      d.setUp();
      assertEqualsTolerance(d.getDx(), 0.0, 0.0001);
      assertEquals(d.getDy(), 1.0);
   }

   void setDown()
   {
      Direction d;
      d.setDown();
      assertEqualsTolerance(d.getDx(), 0.0, 0.0001);
      assertEquals(d.getDy(), -1.0);
   }

   void setLeft()
   {
      Direction d;
      d.setLeft();
      assertEquals(d.getDx(), -1.0);
      assertEqualsTolerance(d.getDy(), 0.0, 0.0001);
   }

   void setRight()
   {
      Direction d;
      d.setRight();
      assertEquals(d.getDx(), 1.0);
      assertEqualsTolerance(d.getDy(), 0.0, 0.0001);
   }

   void rotate()
   {
      Direction d;
      d.setRadians(0.5);
      d.rotate(0.3);
      assertEquals(d.getRadians(), 0.8);
   }

   void setDxDy()
   {
      Direction d;
      d.setDxDy(1.0, 0.0);
      assertEqualsTolerance(d.getRadians(), 0.0, 0.0001);
      d.setDxDy(0.0, 1.0);
      assertEqualsTolerance(d.getRadians(), 3.14159265358979323846 / 2.0, 0.0001);
   }
};

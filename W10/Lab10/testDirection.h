/***********************************************************************
 * testDirection.h
 * Unit tests for Direction.
 * Each test follows SETUP / EXERCISE / VERIFY / TEARDOWN.
 ************************************************************************/

#pragma once

#include "direction.h"
#include "unitTest.h"

class TestDirection : public UnitTest
{
public:
   void run()
   {
      constructor_default_zero();
      constructor_withDegrees();
      setRadians_getRadians_roundTrip();
      setDegrees_getDegrees_roundTrip();
      getDxDy_forCardinalAndAngle();
      setUp_setsNorth();
      setDown_setsSouth();
      setLeft_setsWest();
      setRight_setsEast();
      rotate_addsAngle();
      setDxDy_fromVector();
      report("Direction");
   }

private:
   void constructor_default_zero()
   {
      // SETUP
      // (none)
      // EXERCISE
      Direction d;
      // VERIFY
      assertEquals(d.getRadians(), 0.0);
      // TEARDOWN
      // (none)
   }

   void constructor_withDegrees()
   {
      // SETUP
      // (none)
      // EXERCISE
      Direction d(90.0);
      // VERIFY
      assertEquals(d.getDegrees(), 90.0);
      // TEARDOWN
      // (none)
   }

   void setRadians_getRadians_roundTrip()
   {
      // SETUP
      Direction d;
      // EXERCISE
      d.setRadians(2.0);
      // VERIFY
      assertEquals(d.getRadians(), 2.0);
      // TEARDOWN
      // (none)
   }

   void setDegrees_getDegrees_roundTrip()
   {
      // SETUP
      Direction d;
      // EXERCISE
      d.setDegrees(90.0);
      // VERIFY
      assertEquals(d.getDegrees(), 90.0);
      // TEARDOWN
      // (none)
   }

   void getDxDy_forCardinalAndAngle()
   {
      // SETUP
      Direction d;
      // EXERCISE
      d.setRadians(0.0);
      // VERIFY
      assertEquals(d.getDx(), 1.0);
      assertEquals(d.getDy(), 0.0);
      // SETUP
      d.setRadians(3.14159265358979323846 / 2.0);
      // EXERCISE
      double dx = d.getDx();
      double dy = d.getDy();
      // VERIFY
      assertEqualsTolerance(dx, 0.0, 0.0001);
      assertEquals(dy, 1.0);
      // TEARDOWN
      // (none)
   }

   void setUp_setsNorth()
   {
      // SETUP
      Direction d;
      // EXERCISE
      d.setUp();
      // VERIFY
      assertEqualsTolerance(d.getDx(), 0.0, 0.0001);
      assertEquals(d.getDy(), 1.0);
      // TEARDOWN
      // (none)
   }

   void setDown_setsSouth()
   {
      // SETUP
      Direction d;
      // EXERCISE
      d.setDown();
      // VERIFY
      assertEqualsTolerance(d.getDx(), 0.0, 0.0001);
      assertEquals(d.getDy(), -1.0);
      // TEARDOWN
      // (none)
   }

   void setLeft_setsWest()
   {
      // SETUP
      Direction d;
      // EXERCISE
      d.setLeft();
      // VERIFY
      assertEquals(d.getDx(), -1.0);
      assertEqualsTolerance(d.getDy(), 0.0, 0.0001);
      // TEARDOWN
      // (none)
   }

   void setRight_setsEast()
   {
      // SETUP
      Direction d;
      // EXERCISE
      d.setRight();
      // VERIFY
      assertEquals(d.getDx(), 1.0);
      assertEqualsTolerance(d.getDy(), 0.0, 0.0001);
      // TEARDOWN
      // (none)
   }

   void rotate_addsAngle()
   {
      // SETUP
      Direction d;
      d.setRadians(0.5);
      // EXERCISE
      d.rotate(0.3);
      // VERIFY
      assertEquals(d.getRadians(), 0.8);
      // TEARDOWN
      // (none)
   }

   void setDxDy_fromVector()
   {
      // SETUP
      Direction d;
      // EXERCISE
      d.setDxDy(1.0, 0.0);
      // VERIFY
      assertEqualsTolerance(d.getRadians(), 0.0, 0.0001);
      // SETUP
      d.setDxDy(0.0, 1.0);
      // EXERCISE
      double r = d.getRadians();
      // VERIFY
      assertEqualsTolerance(r, 3.14159265358979323846 / 2.0, 0.0001);
      // TEARDOWN
      // (none)
   }
};


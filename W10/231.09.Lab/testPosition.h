/***********************************************************************
 * Header File:
 *    Test Position : Test the Position class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the unit tests for Position
 ************************************************************************/


#pragma once

#include "position.h"
#include "unitTest.h"
#include <sstream>

/*******************************
 * TEST Position
 * A friend class for Position which contains the Position unit tests
 ********************************/
class TestPosition : public UnitTest
{
public:
   void run()
   {
      // Constructors
      construct_default();
      construct_nonDefault();
      construct_copy();
      assign();
 
      // Setters
      setMetersX();
      setMetersY();
      setMeters_bothCoordinates();
      setPixelsX();
      setPixelsY();
      setZoom_setsMetersPerPixel();
      addMetersX();
      addMetersY();
      addPixelsX();
      addPixelsY();

      // Getters
      getMetersX();
      getMetersY();
      getPixelsX();
      getPixelsY();
      getZoom_returnsMetersPerPixel();
      computeDistance_betweenTwoPoints();
      streamInsertion_formatsPosition();
      streamExtraction_parsesPosition();

      report("Position");
   }
   
private:

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  pos=(0, 0))
    *********************************************/
   void construct_default()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      // EXERCISE
      Position pos;
      // VERIFY
      assertEquals(pos.x, 0.0);
      assertEquals(pos.y, 0.0);
      assertEquals(pos.metersFromPixels, 99.9);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    NON-DEFAULT CONSTRUCTOR
    * input:   x=120.0, y=360.0
    * output:  pos=(120.0, 360.0)
    *********************************************/
   void construct_nonDefault()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      double x = 120.0;
      double y = 360.0;
      // EXERCISE
      Position pos(x, y);
      // VERIFY
      assertEquals(pos.x, 120.0);
      assertEquals(pos.y, 360.0);
      assertEquals(pos.metersFromPixels, 99.9);
      assertEquals(x, 120.0);
      assertEquals(y, 360.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    COPY CONSTRUCTOR
    * input:   posRHS = (1234.5, 6789.0)
    * output:  pos = (1234.5, 6789.0)
    *********************************************/
   void construct_copy()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position posRHS;
      posRHS.x = 1234.5;
      posRHS.y = 6789.0;
      // EXERCISE
      Position pos(posRHS);
      // VERIFY
      assertEquals(posRHS.x, 1234.5);
      assertEquals(posRHS.y, 6789.0);
      assertEquals(posRHS.metersFromPixels, 99.9);
      assertEquals(pos.x, 1234.5);
      assertEquals(pos.y, 6789.0);
      assertEquals(pos.metersFromPixels, 99.9);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    ASSIGNMENT OPERATOR
    * input:   posLHS=(-99.9, -88.8)  posRHS=(24.68, -13,57)
    * output:  posLHS=(24.68, -13,57)
    *********************************************/
   void assign()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position posLHS;
      posLHS.x = -99.9;
      posLHS.y = -88.8;
      Position posRHS;
      posRHS.x = 24.68;
      posRHS.y = -13.57;
      // EXERCISE
      posLHS = posRHS;
      // VERIFY
      assertEquals(posRHS.x, 24.68);
      assertEquals(posRHS.y, -13.57);
      assertEquals(posRHS.metersFromPixels, 99.9);
      assertEquals(posLHS.x, 24.68);
      assertEquals(posLHS.y, -13.57);
      assertEquals(posLHS.metersFromPixels, 99.9);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }
   
   /*********************************************
    * name:    GET METERS X
    * input:   pos=(4500.0, 2500.0)
    * output:  x=4500.0
    *********************************************/
   void getMetersX()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 4500.0;
      pos.y = 2500.0;
      // EXERCISE
      double x = pos.getMetersX();
      // VERIFY
      assertEquals(x, 4500.0);
      assertEquals(pos.x, 4500.0);
      assertEquals(pos.y, 2500.0);
      assertEquals(pos.metersFromPixels, 99.9);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    GET METERS Y
    * input:   pos=(4500.0, 2500.0)
    * output:  y=4500.0
    *********************************************/
   void getMetersY()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 4500.0;
      pos.y = 2500.0;
      // EXERCISE
      double y = pos.getMetersY();
      // VERIFY
      assertEquals(pos.x, 4500.0);
      assertEquals(pos.y, 2500.0);
      assertEquals(pos.metersFromPixels, 99.9);
      assertEquals(y, 2500.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    SET METERS Y
    * input:   pos=(999.9, 888.8) x = 123.4
    * output:  pos=(123.4, 888.8)
    *********************************************/
   void setMetersX()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 999.9;
      pos.y = 888.8;
      // EXERCISE
      pos.setMetersX(123.4);
      // VERIFY
      assertEquals(pos.x, 123.4);
      assertEquals(pos.y, 888.8);
      assertEquals(pos.metersFromPixels, 99.9);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   /*********************************************
    * name:    GET METERS Y ZOOM
    * input:   pos=(999.9, 888.8) y = 123.4
    * output:  pos=(999.9, 123.4)
    *********************************************/
   void setMetersY()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 999.9;
      pos.y = 888.8;
      // EXERCISE
      pos.setMetersY(123.4);
      // VERIFY
      assertEquals(pos.x, 999.9);
      assertEquals(pos.y, 123.4);
      assertEquals(pos.metersFromPixels, 99.9);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void setMeters_bothCoordinates()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 100.0;
      Position pos;
      pos.x = 0.0;
      pos.y = 0.0;
      // EXERCISE
      pos.setMeters(2500.0, 3600.0);
      // VERIFY
      assertEquals(pos.x, 2500.0);
      assertEquals(pos.y, 3600.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void getPixelsX()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 100.0;
      Position pos;
      pos.x = 500.0;
      pos.y = 300.0;
      // EXERCISE
      double px = pos.getPixelsX();
      // VERIFY
      assertEquals(px, 5.0);
      assertEquals(pos.getMetersX(), 500.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void getPixelsY()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 50.0;
      Position pos;
      pos.x = 100.0;
      pos.y = 200.0;
      // EXERCISE
      double py = pos.getPixelsY();
      // VERIFY
      assertEquals(py, 4.0);
      assertEquals(pos.getMetersY(), 200.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void setPixelsX()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 40.0;
      Position pos;
      pos.x = 0.0;
      pos.y = 0.0;
      // EXERCISE
      pos.setPixelsX(25.0);
      // VERIFY
      assertEquals(pos.x, 1000.0);
      assertEquals(pos.getPixelsX(), 25.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void setPixelsY()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 20.0;
      Position pos;
      pos.x = 0.0;
      pos.y = 0.0;
      // EXERCISE
      pos.setPixelsY(10.0);
      // VERIFY
      assertEquals(pos.y, 200.0);
      assertEquals(pos.getPixelsY(), 10.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void setZoom_setsMetersPerPixel()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position pos;
      // EXERCISE
      pos.setZoom(128000.0);
      // VERIFY
      assertEquals(pos.getZoom(), 128000.0);
      assertEquals(Position::metersFromPixels, 128000.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void getZoom_returnsMetersPerPixel()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 2500.0;
      Position pos;
      // EXERCISE
      double z = pos.getZoom();
      // VERIFY
      assertEquals(z, 2500.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void addMetersX()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 100.0;
      pos.y = 200.0;
      // EXERCISE
      pos.addMetersX(50.0);
      // VERIFY
      assertEquals(pos.x, 150.0);
      assertEquals(pos.y, 200.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void addMetersY()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 99.9;
      Position pos;
      pos.x = 100.0;
      pos.y = 200.0;
      // EXERCISE
      pos.addMetersY(75.0);
      // VERIFY
      assertEquals(pos.y, 275.0);
      assertEquals(pos.x, 100.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void addPixelsX()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 10.0;
      Position pos;
      pos.x = 100.0;
      pos.y = 0.0;
      // EXERCISE
      pos.addPixelsX(5.0);
      // VERIFY
      assertEquals(pos.getPixelsX(), 15.0);
      assertEquals(pos.x, 150.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void addPixelsY()
   {
      // SETUP
      double metersFromPixels = Position::metersFromPixels;
      Position::metersFromPixels = 8.0;
      Position pos;
      pos.x = 0.0;
      pos.y = 16.0;
      // EXERCISE
      pos.addPixelsY(3.0);
      // VERIFY
      assertEquals(pos.getPixelsY(), 5.0);
      assertEquals(pos.y, 40.0);
      // TEARDOWN
      Position::metersFromPixels = metersFromPixels;
   }

   void computeDistance_betweenTwoPoints()
   {
      // SETUP
      Position a;
      a.setMeters(0.0, 0.0);
      Position b;
      b.setMeters(3.0, 4.0);
      // EXERCISE
      double d = computeDistance(a, b);
      // VERIFY
      assertEquals(d, 5.0);
      // TEARDOWN
      // (none)
   }

   void streamInsertion_formatsPosition()
   {
      // SETUP
      Position pos;
      pos.setMeters(100.5, -200.25);
      std::ostringstream out;
      // EXERCISE
      out << pos;
      // VERIFY
      assertUnit(out.str().find("100.5") != std::string::npos);
      assertUnit(out.str().find("-200.25") != std::string::npos);
      assertUnit(out.str().find("m") != std::string::npos);
      // TEARDOWN
      // (none)
   }

   void streamExtraction_parsesPosition()
   {
      // SETUP
      std::istringstream in("42.0 99.5");
      Position pos;
      // EXERCISE
      in >> pos;
      // VERIFY
      assertEquals(pos.getMetersX(), 42.0);
      assertEquals(pos.getMetersY(), 99.5);
      // TEARDOWN
      // (none)
   }
};

/***********************************************************************
 * Header File:
 *    TEST BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for Board
 ************************************************************************/

#pragma once

#include "unitTest.h"

class Board;

/***************************************************
 * BOARD TEST
 * Test the Board class
 ***************************************************/
class TestBoard : public UnitTest
{
public:
   void run()
   {
      // Ticket 6: Board Core
      construct_dummyBoard();
      construct_emptyBoard();
      getCurrentMove_initial();
      getCurrentMove_second();
      getCurrentMove_middleWhite();
      getCurrentMove_middleBlack();
      whiteTurn_initial();
      whiteTurn_second();
      whiteTurn_middleWhite();
      whiteTurn_middleBlack();

      // Ticket 7: Board Fetch
      fetch_a1();
      fetch_h8();
      fetch_a8();
      set_a1();
      set_h8();
      set_a8();

      report("Board");
   }
private:
   
   void createDummyBoard(Board & board);

   void construct_dummyBoard();
   void construct_emptyBoard();
   void getCurrentMove_initial();
   void getCurrentMove_second();
   void getCurrentMove_middleWhite();
   void getCurrentMove_middleBlack();
   void whiteTurn_initial();
   void whiteTurn_second();
   void whiteTurn_middleWhite();
   void whiteTurn_middleBlack();

   void fetch_a1();
   void fetch_h8();
   void fetch_a8();
   void set_a1();
   void set_h8();
   void set_a8();
};


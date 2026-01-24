/***********************************************************************
 * Test Runner for Move Tests Only
 ************************************************************************/

#include "testMove.h"
#include "move.h"
#include "position.h"
#include "pieceType.h"
#include "unitTest.h"
#include <iostream>

double Position::squareWidth = (double)SIZE_SQUARE;
double Position::squareHeight = (double)SIZE_SQUARE;

int main()
{
   TestMove().run();
   return 0;
}

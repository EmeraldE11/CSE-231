/***********************************************************************
 * Header File:
 *    SPACE
 * Author:
 *    <your name here> 
 * Summary:
 *    The space
 ************************************************************************/

#pragma once

#include "piece.h"

class TestSpace;

 /***************************************************
  * SPACES
  * A space is a trivial piece
  ***************************************************/
class Space : public Piece
{
   friend TestSpace;
public:
	Space(int c, int r) : Piece(c, r) {} // constructor, takes column and row
   ~Space() {} // destructor
   PieceType getType() const
   {
	   return SPACE;
   }
   void display(ogstream* pgout) const
   {
	   //not yet implemented
   }
};
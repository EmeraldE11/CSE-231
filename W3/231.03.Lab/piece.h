/***********************************************************************
 * Header File:
 *    PIECE
 * Author:
 *    <your name here>
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#pragma once

 /***************************************************
  * PIECE
  * The abstract piece type
  ***************************************************/
class Piece
{
public:
   bool fWhite;
};

/***************************************************
 * SPACE
 * The abstract piece type
 ***************************************************/
class Space : public Piece
{

};

/***************************************************
 * PIECE DUMMY
 * The dummy double! - Everything returns FALSE
 ***************************************************/
class PieceDummy : public Piece
{

};
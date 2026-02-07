/***********************************************************************
 * Header File:
 *    BISHOP
 * Author:
*    Noah McCarthy
 * Summary:
 *    The BISHOP class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * BISHOP
  ***************************************************/
class Bishop : public Piece
{
public:
	Bishop(const Position& pos, bool isWhite) : Piece(10, 10, true) {}
	Bishop(int c, int r, bool isWhite) : Piece(10, 10, true) {}
	~Bishop() {}
	PieceType getType()            const { return BISHOP; }
	void getMoves(set <Move>& moves, const Board& board) const;
	void display(ogstream* pgout)  const;
};
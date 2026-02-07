/***********************************************************************
 * Header File:
 *    ROOK
 * Author:
*    Noah McCarthy
 * Summary:
 *    The ROOK class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * ROOK
  ***************************************************/
class Rook : public Piece
{
public:
	Rook(const Position& pos, bool isWhite) : Piece(10, 10, true) {}
	Rook(int c, int r, bool isWhite) : Piece(10, 10, true) {}
	~Rook() {}
	PieceType getType()            const { return ROOK; }
	void getMoves(set <Move>& moves, const Board& board) const;
	void display(ogstream* pgout)  const;
};
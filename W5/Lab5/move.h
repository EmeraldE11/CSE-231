/***********************************************************************
 * Header File:
 *    MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#pragma once

#include <string>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type


class TestMove;
class TestBoard;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
	friend class TestKnight;
	friend class TestBishop;
	friend class TestRook;
public:
	enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

	friend TestMove;
	friend TestBoard;

	// constructor
	Move();
	Move(const string& rhs);

	// comparison operators
	bool operator==(const Move& rhs) const;
	bool operator<(const Move& rhs) const;

	// text operations
	void read(const string& rhs);
	const Move& operator=(const string& rhs);
	string getText() const;

	// getters
	Position getSrc() const { return source; }
	Position getDes() const { return dest; }
	PieceType getCapture() const { return capture; }
	PieceType getPromotion() const { return promote; }
	MoveType getMoveType() const { return moveType; }
	bool getWhiteMove() const { return isWhite; }

	// setters
	void setSrc(const Position& pos) { source = pos; }
	void setDes(const Position& pos) { dest = pos; }
	void setCapture(PieceType pt) { capture = pt; }
	void setPromotion(PieceType pt) { promote = pt; }
	void setEnPassant() { moveType = ENPASSANT; }
	void setCastle(bool isKing);
	void setWhiteMove(bool white) { isWhite = white; }

private:
	char letterFromPieceType(PieceType pt)     const;
	PieceType pieceTypeFromLetter(char letter) const;



	Position  source;    // where the move originated from
	Position  dest;      // where the move finished
	PieceType promote;   // piece to be promoted to
	PieceType capture;   // did a capture happen this move?
	MoveType  moveType;  // what type of move is this?
	bool      isWhite;   // whose turn is it anyway?
	string    text;      // what is the textual version of the move?
};



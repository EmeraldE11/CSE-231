/***********************************************************************
 * Header File:
 *    TEST MOVE
 * Author:
 *    <your name here>
 * Summary:
 *    test the Move class
 ************************************************************************/


#include "testMove.h"
#include "move.h"
#include <cassert>

 /*************************************
  * Constructor : default
  * Input:
  * Output: source=INVALID
  *         dest  =INVALID
  **************************************/
void TestMove::constructor_default()
{
	// SETUP
	Move move;

	// VERIFY
	assertUnit(move.source.isInvalid());
	assertUnit(move.dest.isInvalid());
	assertUnit(move.promote == SPACE);
	assertUnit(move.capture == SPACE);
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.isWhite == false);
	assertUnit(move.text == "");
}

/*************************************
 * CONSTRUCTOR : standard string move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::constructString_simple()
{
	// SETUP & EXERCISE
	Move move("e5e6");

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 4);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::MOVE);
}

/*************************************
 * READ simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::read_simple()
{
	// SETUP
	Move move;

	// EXERCISE
	move.read("e5e6");

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 4);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::MOVE);
}

/*************************************
 * READ capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::read_capture()
{
	// SETUP
	Move move;

	// EXERCISE
	move.read("e5d6r");

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 3);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);
}

/*************************************
 * READ enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::read_enpassant()
{
	// SETUP
	Move move;

	// EXERCISE
	move.read("e5f6E");

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 5);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::ENPASSANT);
	assertUnit(move.capture == PAWN);
}

/*************************************
 * READ king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::read_castleKing()
{
	// SETUP
	Move move;

	// EXERCISE
	move.read("e1g1c");

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 0);
	assertUnit(move.dest.getCol() == 6);
	assertUnit(move.dest.getRow() == 0);
	assertUnit(move.moveType == Move::CASTLE_KING);
}

/*************************************
 * READ queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::read_castleQueen()
{
	// SETUP
	Move move;

	// EXERCISE
	move.read("e1c1C");

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 0);
	assertUnit(move.dest.getCol() == 2);
	assertUnit(move.dest.getRow() == 0);
	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}

/*************************************
 * ASSIGN simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::assign_simple()
{
	// SETUP
	Move move;

	// EXERCISE
	move = "e5e6";

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 4);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::MOVE);
}

/*************************************
 * ASSIGN capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::assign_capture()
{
	// SETUP
	Move move;

	// EXERCISE
	move = "e5d6r";

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 3);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::MOVE);
	assertUnit(move.capture == ROOK);
}

/*************************************
 * ASSIGN enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::assign_enpassant()
{
	// SETUP
	Move move;

	// EXERCISE
	move = "e5f6E";

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 4);
	assertUnit(move.dest.getCol() == 5);
	assertUnit(move.dest.getRow() == 5);
	assertUnit(move.moveType == Move::ENPASSANT);
}

/*************************************
 * ASSIGN king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::assign_castleKing()
{
	// SETUP
	Move move;

	// EXERCISE
	move = "e1g1c";

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 0);
	assertUnit(move.dest.getCol() == 6);
	assertUnit(move.dest.getRow() == 0);
	assertUnit(move.moveType == Move::CASTLE_KING);
}

/*************************************
 * ASSIGN queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::assign_castleQueen()
{
	// SETUP
	Move move;

	// EXERCISE
	move = "e1c1C";

	// VERIFY
	assertUnit(move.source.getCol() == 4);
	assertUnit(move.source.getRow() == 0);
	assertUnit(move.dest.getCol() == 2);
	assertUnit(move.dest.getRow() == 0);
	assertUnit(move.moveType == Move::CASTLE_QUEEN);
}

/*************************************
 * GET TEXT simple move
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 * Output:  e5e6
 **************************************/
void TestMove::getText_simple()
{
	// SETUP
	Move move;
	move.source.set(4, 4);
	move.dest.set(4, 5);
	move.moveType = Move::MOVE;

	// EXERCISE
	string result = move.getText();

	// VERIFY
	assertUnit(result == "e5e6");
}

/*************************************
 * GET TEXT capture
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 *         capture=ROOK
 * Output:  e5e6r
 **************************************/
void TestMove::getText_capture()
{
	// SETUP
	Move move;
	move.source.set(4, 4);
	move.dest.set(4, 5);
	move.moveType = Move::MOVE;
	move.capture = ROOK;

	// EXERCISE
	string result = move.getText();

	// VERIFY
	assertUnit(result == "e5e6r");
}

/*************************************
 * GET TEXT en passant
 * Input : source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 *         capture=PAWN
 * Output:  e5f6E
 **************************************/
void TestMove::getText_enpassant()
{
	// SETUP
	Move move;
	move.source.set(4, 4);
	move.dest.set(5, 5);
	move.moveType = Move::ENPASSANT;
	move.capture = PAWN;

	// EXERCISE
	string result = move.getText();

	// VERIFY
	assertUnit(result == "e5f6E");
}

/*************************************
 * GET TEXT king side castle
 * Input : source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 * Output:  e1g1c
 **************************************/
void TestMove::getText_castleKing()
{
	// SETUP
	Move move;
	move.source.set(4, 0);
	move.dest.set(6, 0);
	move.moveType = Move::CASTLE_KING;

	// EXERCISE
	string result = move.getText();

	// VERIFY
	assertUnit(result == "e1g1c");
}

/*************************************
 * GET TEXT queen side castle
 * Input : source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 * Output:  e1c1C
 **************************************/
void TestMove::getText_castleQueen()
{
	// SETUP
	Move move;
	move.source.set(4, 0);
	move.dest.set(2, 0);
	move.moveType = Move::CASTLE_QUEEN;

	// EXERCISE
	string result = move.getText();

	// VERIFY
	assertUnit(result == "e1c1C");
}

/*************************************
 * LETTER FROM PIECE TYPE space
 * Input :  SPACE
 * Output:  ' '
 **************************************/
void TestMove::letterFromPieceType_space()
{
	// SETUP
	Move move;

	// EXERCISE
	char result = move.letterFromPieceType(SPACE);

	// VERIFY
	assertUnit(result == ' ');
}

/*************************************
 * LETTER FROM PIECE TYPE pawn
 * Input : PAWN
 * Output:  'p'
 **************************************/
void TestMove::letterFromPieceType_pawn()
{
	// SETUP
	Move move;

	// EXERCISE
	char result = move.letterFromPieceType(PAWN);

	// VERIFY
	assertUnit(result == 'p');
}

/*************************************
 * LETTER FROM PIECE TYPE bishop
 * Input : BISHOP
 * Output:  'b'
 **************************************/
void TestMove::letterFromPieceType_bishop()
{
	// SETUP
	Move move;

	// EXERCISE
	char result = move.letterFromPieceType(BISHOP);

	// VERIFY
	assertUnit(result == 'b');
}

/*************************************
 * LETTER FROM PIECE TYPE knight
 * Input : KNIGHT
 * Output:  'n'
 **************************************/
void TestMove::letterFromPieceType_knight()
{
	// SETUP
	Move move;

	// EXERCISE
	char result = move.letterFromPieceType(KNIGHT);

	// VERIFY
	assertUnit(result == 'n');
}

/*************************************
 * LETTER FROM PIECE TYPE rook
 * Input : ROOK
 * Output:  'r'
 **************************************/
void TestMove::letterFromPieceType_rook()
{
	// SETUP
	Move move;

	// EXERCISE
	char result = move.letterFromPieceType(ROOK);

	// VERIFY
	assertUnit(result == 'r');
}

/*************************************
 * LETTER FROM PIECE TYPE queen
 * Input : QUEEN
 * Output:  'q'
 **************************************/
void TestMove::letterFromPieceType_queen()
{
	// SETUP
	Move move;

	// EXERCISE
	char result = move.letterFromPieceType(QUEEN);

	// VERIFY
	assertUnit(result == 'q');
}

/*************************************
 * LETTER FROM PIECE TYPE king
 * Input : KING
 * Output:  'k'
 **************************************/
void TestMove::letterFromPieceType_king()
{
	// SETUP
	Move move;

	// EXERCISE
	char result = move.letterFromPieceType(KING);

	// VERIFY
	assertUnit(result == 'k');
}

/*************************************
 * PIECE TYPE FROM LETTER pawn
 * Input : 'p'
 * Output:  PAWN
 **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
	// SETUP
	Move move;

	// EXERCISE
	PieceType result = move.pieceTypeFromLetter('p');

	// VERIFY
	assertUnit(result == PAWN);
}

/*************************************
 * PIECE TYPE FROM LETTER bishop
 * Input : 'b'
 * Output:  BISHOP
 **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{
	// SETUP
	Move move;

	// EXERCISE
	PieceType result = move.pieceTypeFromLetter('b');

	// VERIFY
	assertUnit(result == BISHOP);
}

/*************************************
 * PIECE TYPE FROM LETTER knight
 * Input : 'n'
 * Output:  KNIGHT
 **************************************/
void TestMove::pieceTypeFromLetter_knight()
{
	// SETUP
	Move move;

	// EXERCISE
	PieceType result = move.pieceTypeFromLetter('n');

	// VERIFY
	assertUnit(result == KNIGHT);
}

/*************************************
 * PIECE TYPE FROM LETTER rook
 * Input : 'r'
 * Output:  ROOK
 **************************************/
void TestMove::pieceTypeFromLetter_rook()
{
	// SETUP
	Move move;

	// EXERCISE
	PieceType result = move.pieceTypeFromLetter('r');

	// VERIFY
	assertUnit(result == ROOK);
}

/*************************************
 * PIECE TYPE FROM LETTER queen
 * Input : 'q'
 * Output:  QUEEN
 **************************************/
void TestMove::pieceTypeFromLetter_queen()
{
	// SETUP
	Move move;

	// EXERCISE
	PieceType result = move.pieceTypeFromLetter('q');

	// VERIFY
	assertUnit(result == QUEEN);
}

/*************************************
 * PIECE TYPE FROM LETTER king
 * Input : 'k'
 * Output:  KING
 **************************************/
void TestMove::pieceTypeFromLetter_king()
{
	// SETUP
	Move move;

	// EXERCISE
	PieceType result = move.pieceTypeFromLetter('k');

	// VERIFY
	assertUnit(result == KING);
}


/*************************************
 * EQUAL - NOT
 * Input : b2b4 == b2b5
 * Output: false
 **************************************/
//void TestMove::equal_not()
//{
//	// SETUP
//	Move move1;
//	move1.source = "b2";
//	move1.dest = "b4";
//	Move move2;
//	move2.source = "b2";
//	move2.dest = "b5";
//
//	// EXERCISE
//	bool result = (move1 == move2);
//
//	// VERIFY
//	assertUnit(result == false);
//}
//
///*************************************
// * EQUAL - EQUALS
// * Input : b2b4 == b2b4
// * Output: true
// **************************************/
//void TestMove::equal_equals()
//{
//	// SETUP
//	Move move1;
//	move1.read("b2b4");
//	Move move2;
//	move2.read("b2b4");
//
//	// EXERCISE
//	bool result = (move1 == move2);
//
//	// VERIFY
//	assertUnit(result == true);
//}
//
///*************************************
// * LESS THAN - LESS THAN
// * Input : b2b2 < b2b4
// * Output: false
// *    Note that the less-than operator is needed
// *    so std::set<T> can sort the elements. Thus,
// *    any T in a set must define less-than. In this
// *    case, I defined it according to the
// *     destination's Position's location.
// **************************************/
//void TestMove::lessthan_lessthan()
//{
//	// SETUP
//	Move move1;
//	move1.dest = "b2";
//	Move move2;
//	move2.dest = "b4";
//
//	// EXERCISE
//	bool result = (move1 < move2);
//
//	// VERIFY
//	assertUnit(result == true);  // b2 < b4
//}
//
///*************************************
// * LESS THAN - EQUALS
// * Input : b2b4 < b2b4
// * Output: false
// **************************************/
//void TestMove::lessthan_equals()
//{
//	// SETUP
//	Move move1;
//	move1.dest = "b4";
//	Move move2;
//	move2.dest = "b4";
//
//	// EXERCISE
//	bool result = (move1 < move2);
//
//	// VERIFY
//	assertUnit(result == false);
//}
//
///*************************************
// * LESS THAN - GREATAER THAN
// * Input : b2b4 < b2b2
// * Output: false
// **************************************/
//void TestMove::lessthan_greaterthan()
//{
//	// SETUP
//	Move move1;
//	move1.dest = "b4";
//	Move move2;
//	move2.dest = "b2";
//
//	// EXERCISE
//	bool result = (move1 < move2);
//
//	// VERIFY
//	assertUnit(result == false);  // b4 is not < b2
//}

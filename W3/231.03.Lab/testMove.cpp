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

   // VERIFY - use raw members, do not assume Position methods work
   assertUnit(0xff == move.source.colRow);
   assertUnit(0xff == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(SPACE == move.capture);
   assertUnit(Move::MOVE == move.moveType);
   assertUnit(false == move.isWhite);
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
   // SETUP - wrong values so we verify read() actually ran
   Move move;
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = BISHOP;
   move.moveType  = Move::MOVE_ERROR;
   move.isWhite   = true;
   move.text      = "ERROR";

   // EXERCISE
   move = string("e5e6");

   // VERIFY - use raw members
   assertUnit(0x44 == move.source.colRow);
   assertUnit(0x45 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(SPACE == move.capture);
   assertUnit(Move::MOVE == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = BISHOP;
   move.moveType  = Move::MOVE_ERROR;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move.read(string("e5e6"));

   // VERIFY
   assertUnit(0x44 == move.source.colRow);
   assertUnit(0x45 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(SPACE == move.capture);
   assertUnit(Move::MOVE == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = SPACE;
   move.moveType  = Move::MOVE_ERROR;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move.read(string("e5d6r"));

   // VERIFY
   assertUnit(0x44 == move.source.colRow);
   assertUnit(0x35 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(ROOK == move.capture);
   assertUnit(Move::MOVE == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = SPACE;
   move.moveType  = Move::MOVE;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move.read(string("e5f6E"));

   // VERIFY
   assertUnit(0x44 == move.source.colRow);
   assertUnit(0x55 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(PAWN == move.capture);
   assertUnit(Move::ENPASSANT == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = BISHOP;
   move.moveType  = Move::MOVE;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move.read(string("e1g1c"));

   // VERIFY
   assertUnit((uint8_t)0x40 == move.source.colRow);
   assertUnit(0x60 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(SPACE == move.capture);
   assertUnit(Move::CASTLE_KING == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = BISHOP;
   move.moveType  = Move::MOVE;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move.read(string("e1c1C"));

   // VERIFY
   assertUnit(0x40 == move.source.colRow);
   assertUnit(0x20 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(SPACE == move.capture);
   assertUnit(Move::CASTLE_QUEEN == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = BISHOP;
   move.moveType  = Move::MOVE_ERROR;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move = string("e5e6");

   // VERIFY
   assertUnit(0x44 == move.source.colRow);
   assertUnit(0x45 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(SPACE == move.capture);
   assertUnit(Move::MOVE == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = SPACE;
   move.moveType  = Move::MOVE_ERROR;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move = string("e5d6r");

   // VERIFY
   assertUnit(0x44 == move.source.colRow);
   assertUnit(0x35 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(ROOK == move.capture);
   assertUnit(Move::MOVE == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = SPACE;
   move.moveType  = Move::MOVE;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move = string("e5f6E");

   // VERIFY
   assertUnit(0x44 == move.source.colRow);
   assertUnit(0x55 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(PAWN == move.capture);
   assertUnit(Move::ENPASSANT == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = BISHOP;
   move.moveType  = Move::MOVE;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move = string("e1g1c");

   // VERIFY
   assertUnit((uint8_t)0x40 == move.source.colRow);
   assertUnit(0x60 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(SPACE == move.capture);
   assertUnit(Move::CASTLE_KING == move.moveType);
   assertUnit(false == move.isWhite);
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
   move.source.colRow = 0xff;
   move.dest.colRow   = 0xff;
   move.promote   = KNIGHT;
   move.capture   = BISHOP;
   move.moveType  = Move::MOVE;
   move.isWhite   = false;
   move.text      = "ERROR";

   // EXERCISE
   move = string("e1c1C");

   // VERIFY
   assertUnit(0x40 == move.source.colRow);
   assertUnit(0x20 == move.dest.colRow);
   assertUnit(SPACE == move.promote);
   assertUnit(SPACE == move.capture);
   assertUnit(Move::CASTLE_QUEEN == move.moveType);
   assertUnit(false == move.isWhite);
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
   // SETUP - use raw colRow, do not assume Position::set() works
   Move move;
   move.source.colRow = 0x44;  // e5 = col 4, row 4
   move.dest.colRow   = 0x45;  // e6 = col 4, row 5
   move.promote   = SPACE;
   move.capture   = SPACE;
   move.moveType  = Move::MOVE;
   move.isWhite   = false;

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
   // SETUP - use raw colRow
   Move move;
   move.source.colRow = 0x44;  // e5
   move.dest.colRow   = 0x45;  // e6
   move.promote   = SPACE;
   move.capture   = ROOK;
   move.moveType  = Move::MOVE;
   move.isWhite   = false;

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
   // SETUP - use raw colRow
   Move move;
   move.source.colRow = 0x44;  // e5
   move.dest.colRow   = 0x55;  // f6
   move.promote   = SPACE;
   move.capture   = PAWN;
   move.moveType  = Move::ENPASSANT;
   move.isWhite   = false;

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
   // SETUP - use raw colRow
   Move move;
   move.source.colRow = 0x40;  // e1
   move.dest.colRow   = 0x60;  // g1
   move.promote   = SPACE;
   move.capture   = SPACE;
   move.moveType  = Move::CASTLE_KING;
   move.isWhite   = false;

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
   // SETUP - use raw colRow
   Move move;
   move.source.colRow = 0x40;  // e1
   move.dest.colRow   = 0x20;  // c1
   move.promote   = SPACE;
   move.capture   = SPACE;
   move.moveType  = Move::CASTLE_QUEEN;
   move.isWhite   = false;

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
void TestMove::equal_not()
{
   // SETUP - use raw colRow, do not assume Position assignment works
   Move move1;
   move1.source.colRow = 0x12;  // b2
   move1.dest.colRow   = 0x14;  // b4
   Move move2;
   move2.source.colRow = 0x12;  // b2
   move2.dest.colRow   = 0x15;  // b5

   // EXERCISE
   bool result = (move1 == move2);

   // VERIFY
   assertUnit(result == false);
}

 /*************************************
  * EQUAL - EQUALS
  * Input : b2b4 == b2b4
  * Output: true
  **************************************/
void TestMove::equal_equals()
{
   // SETUP - use raw colRow so we do not assume read() or Position works
   Move move1;
   move1.source.colRow = 0x12;  // b2
   move1.dest.colRow   = 0x14;  // b4
   move1.promote = SPACE;
   move1.capture = SPACE;
   move1.moveType = Move::MOVE;
   move1.isWhite = false;
   Move move2;
   move2.source.colRow = 0x12;
   move2.dest.colRow   = 0x14;
   move2.promote = SPACE;
   move2.capture = SPACE;
   move2.moveType = Move::MOVE;
   move2.isWhite = false;

   // EXERCISE
   bool result = (move1 == move2);

   // VERIFY
   assertUnit(result == true);
}

 /*************************************
  * LESS THAN - LESS THAN
  * Input : b2b2 < b2b4
  * Output: false
  *    Note that the less-than operator is needed
  *    so std::set<T> can sort the elements. Thus,
  *    any T in a set must define less-than. In this
  *    case, I defined it according to the 
  *     destination's Position's location.
  **************************************/
void TestMove::lessthan_lessthan()
{
   // SETUP
   Move move1;
   move1.dest = "b2";
   Move move2;
   move2.dest = "b4";

   // EXERCISE
   bool result = (move1 < move2);

   // VERIFY
   assertUnit(result == true);  // b2 < b4
}

 /*************************************
  * LESS THAN - EQUALS
  * Input : b2b4 < b2b4
  * Output: false
  **************************************/
void TestMove::lessthan_equals()
{
   // SETUP - use raw colRow
   Move move1;
   move1.dest.colRow = 0x14;  // b4
   Move move2;
   move2.dest.colRow = 0x14;  // b4

   // EXERCISE
   bool result = (move1 < move2);

   // VERIFY
   assertUnit(result == false);
}

 /*************************************
  * LESS THAN - GREATAER THAN
  * Input : b2b4 < b2b2
  * Output: false
  **************************************/
void TestMove::lessthan_greaterthan()
{
   // SETUP - use raw colRow
   Move move1;
   move1.dest.colRow = 0x14;  // b4
   Move move2;
   move2.dest.colRow = 0x12;  // b2

   // EXERCISE
   bool result = (move1 < move2);

   // VERIFY - 0x14 is not < 0x12
   assertUnit(result == false);
}

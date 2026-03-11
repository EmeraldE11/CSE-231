/***********************************************************************
 * Source File:
 *    TEST KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the knight
 ************************************************************************/

#include "testKnight.h"
#include "pieceKnight.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5                     5
  * 4                     4
  * 3             p   .   3
  * 2           P         2
  * 1              (n)    1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestKnight::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   Knight knight(7, 7, false /*white*/); // we will reset all this.
   knight.fWhite = true;
   knight.position.colRow = 0x60;
   board.board[6][0] = &knight;
   Black black(PAWN);
   board.board[4][1] = &black;
   White white(PAWN);
   board.board[5][2] = &white;
   set <Move> moves;
   Move g1e2p;
   g1e2p.source.colRow = 0x60;
   g1e2p.dest.colRow = 0x41;
   g1e2p.capture = PAWN;
   g1e2p.setWhiteMove(true);
   Move g1h3;
   g1h3.source.colRow = 0x60;
   g1h3.dest.colRow = 0x72;
   g1h3.capture = SPACE;
   g1h3.setWhiteMove(true);

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // many possible moves
   assertUnit(moves.find(g1e2p) != moves.end());
   assertUnit(moves.find(g1h3) != moves.end());

   // TEARDOWN
   board.board[6][0] = nullptr; // white knight
   board.board[4][1] = nullptr; // black pawn
   board.board[5][2] = nullptr; // white pawn
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Knight knight(4, 4, true);
   knight.position.colRow = 0x44;
   board.board[4][4] = &knight;
   White white1(PAWN);
   White white2(PAWN);
   White white3(PAWN);
   White white4(PAWN);
   White white5(PAWN);
   White white6(PAWN);
   White white7(PAWN);
   White white8(PAWN);
   board.board[3][6] = &white1;
   board.board[5][6] = &white2;
   board.board[2][5] = &white3;
   board.board[6][5] = &white4;
   board.board[2][3] = &white5;
   board.board[6][3] = &white6;
   board.board[3][2] = &white7;
   board.board[5][2] = &white8;
   set <Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);

   // TEARDOWN
   board.board[4][4] = nullptr;
   board.board[3][6] = nullptr;
   board.board[5][6] = nullptr;
   board.board[2][5] = nullptr;
   board.board[6][5] = nullptr;
   board.board[2][3] = nullptr;
   board.board[6][3] = nullptr;
   board.board[3][2] = nullptr;
   board.board[5][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   Knight knight(4, 4, true);
   knight.fWhite = true;
   knight.position.colRow = 0x44;
   board.board[4][4] = &knight;
   Black black1(PAWN);
   Black black2(PAWN);
   Black black3(PAWN);
   Black black4(PAWN);
   Black black5(PAWN);
   Black black6(PAWN);
   Black black7(PAWN);
   Black black8(PAWN);
   board.board[3][6] = &black1;
   board.board[5][6] = &black2;
   board.board[2][5] = &black3;
   board.board[6][5] = &black4;
   board.board[2][3] = &black5;
   board.board[6][3] = &black6;
   board.board[3][2] = &black7;
   board.board[5][2] = &black8;
   set <Move> moves;
   Move e5d7p;
   e5d7p.source.colRow = 0x44;
   e5d7p.dest.colRow = 0x36;
   e5d7p.capture = PAWN;
   e5d7p.setWhiteMove(true);
   Move e5f7p;
   e5f7p.source.colRow = 0x44;
   e5f7p.dest.colRow = 0x56;
   e5f7p.capture = PAWN;
   e5f7p.setWhiteMove(true);
   Move e5c6p;
   e5c6p.source.colRow = 0x44;
   e5c6p.dest.colRow = 0x25;
   e5c6p.capture = PAWN;
   e5c6p.setWhiteMove(true);
   Move e5g6p;
   e5g6p.source.colRow = 0x44;
   e5g6p.dest.colRow = 0x65;
   e5g6p.capture = PAWN;
   Move e5c4p;
   e5c4p.source.colRow = 0x44;
   e5c4p.dest.colRow = 0x23;
   e5c4p.capture = PAWN;
   e5c4p.setWhiteMove(true);
   Move e5g4p;
   e5g4p.source.colRow = 0x44;
   e5g4p.dest.colRow = 0x63;
   e5g4p.capture = PAWN;
   Move e5d3p;
   e5d3p.source.colRow = 0x44;
   e5d3p.dest.colRow = 0x32;
   e5d3p.capture = PAWN;
   e5d3p.setWhiteMove(true);
   Move e5f3p;
   e5f3p.source.colRow = 0x44;
   e5f3p.dest.colRow = 0x52;
   e5f3p.capture = PAWN;
   e5f3p.setWhiteMove(true);

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(e5d7p) != moves.end());
   assertUnit(moves.find(e5f7p) != moves.end());
   assertUnit(moves.find(e5c6p) != moves.end());
   assertUnit(moves.find(e5g6p) != moves.end());
   assertUnit(moves.find(e5c4p) != moves.end());
   assertUnit(moves.find(e5g4p) != moves.end());
   assertUnit(moves.find(e5d3p) != moves.end());
   assertUnit(moves.find(e5f3p) != moves.end());

   // TEARDOWN
   board.board[4][4] = nullptr;
   board.board[3][6] = nullptr;
   board.board[5][6] = nullptr;
   board.board[2][5] = nullptr;
   board.board[6][5] = nullptr;
   board.board[2][3] = nullptr;
   board.board[6][3] = nullptr;
   board.board[3][2] = nullptr;
   board.board[5][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       .   .         7
 * 6     .       .       6
 * 5        (n)          5
 * 4     .       .       4
 * 3       .   .         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_free()
{
   // SETUP
   BoardEmpty board;
   Knight knight(4, 4, true);
   knight.fWhite = true;
   knight.position.colRow = 0x44;
   board.board[4][4] = &knight;
   set <Move> moves;
   Move e5d7;
   e5d7.source.colRow = 0x44;
   e5d7.dest.colRow = 0x36;
   e5d7.capture = SPACE;
   e5d7.setWhiteMove(true);
   Move e5f7;
   e5f7.source.colRow = 0x44;
   e5f7.dest.colRow = 0x56;
   e5f7.capture = SPACE;
   e5f7.setWhiteMove(true);
   Move e5c6;
   e5c6.source.colRow = 0x44;
   e5c6.dest.colRow = 0x25;
   e5c6.capture = SPACE;
   e5c6.setWhiteMove(true);
   Move e5g6;
   e5g6.source.colRow = 0x44;
   e5g6.dest.colRow = 0x65;
   e5g6.capture = SPACE;
   e5g6.setWhiteMove(true);
   Move e5c4;
   e5c4.source.colRow = 0x44;
   e5c4.dest.colRow = 0x23;
   e5c4.capture = SPACE;
   e5c4.setWhiteMove(true);
   Move e5g4;
   e5g4.source.colRow = 0x44;
   e5g4.dest.colRow = 0x63;
   e5g4.capture = SPACE;
   e5g4.setWhiteMove(true);
   Move e5d3;
   e5d3.source.colRow = 0x44;
   e5d3.dest.colRow = 0x32;
   e5d3.capture = SPACE;
   e5d3.setWhiteMove(true);
   Move e5f3;
   e5f3.source.colRow = 0x44;
   e5f3.dest.colRow = 0x52;
   e5f3.capture = SPACE;
   e5f3.setWhiteMove(true);

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(e5d7) != moves.end());
   assertUnit(moves.find(e5f7) != moves.end());
   assertUnit(moves.find(e5c6) != moves.end());
   assertUnit(moves.find(e5g6) != moves.end());
   assertUnit(moves.find(e5c4) != moves.end());
   assertUnit(moves.find(e5g4) != moves.end());
   assertUnit(moves.find(e5d3) != moves.end());
   assertUnit(moves.find(e5f3) != moves.end());

   // TEARDOWN
   board.board[4][4] = nullptr;
}



/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{
   // SETUP  
   const Knight knight(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = knight.getType();

   // VERIFY
   assertUnit(pt == KNIGHT);
}  // TEARDOWN

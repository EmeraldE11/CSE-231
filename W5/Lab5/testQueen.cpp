/***********************************************************************
 * Source File:
 *    TEST QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the queen
 ************************************************************************/

#include "testQueen.h"
#include "pieceQueen.h"     
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
 * 3     p p p           3
 * 2     p(q)p           2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Queen queen(3, 1, true);
   queen.position.colRow = 0x31;
   board.board[3][1] = &queen;
   White white1(PAWN);
   White white2(PAWN);
   White white3(PAWN);
   White white4(PAWN);
   White white5(PAWN);
   White white6(PAWN);
   White white7(PAWN);
   White white8(PAWN);
   board.board[2][0] = &white1;
   board.board[3][0] = &white2;
   board.board[4][0] = &white3;
   board.board[2][2] = &white4;
   board.board[4][2] = &white5;
   board.board[1][1] = &white6;
   board.board[5][1] = &white7;
   board.board[3][2] = &white8;
   set <Move> moves;

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);

   // TEARDOWN
   board.board[3][1] = nullptr;
   board.board[2][0] = nullptr;
   board.board[3][0] = nullptr;
   board.board[4][0] = nullptr;
   board.board[2][2] = nullptr;
   board.board[4][2] = nullptr;
   board.board[1][1] = nullptr;
   board.board[5][1] = nullptr;
   board.board[3][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .         .   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   .   .   .         4
 * 3     . . .           3
 * 2   . .(q). . . . .   2
 * 1     . . .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Queen queen(3, 1, true);
   queen.position.colRow = 0x31;
   board.board[3][1] = &queen;
   set <Move> moves;
   Move c2a4;
   c2a4.source.colRow = 0x31;
   c2a4.dest.colRow = 0x03;
   c2a4.capture = SPACE;
   c2a4.setWhiteMove(true);
   Move c2e4;
   c2e4.source.colRow = 0x31;
   c2e4.dest.colRow = 0x43;
   c2e4.capture = SPACE;
   c2e4.setWhiteMove(true);
   Move c2a2;
   c2a2.source.colRow = 0x31;
   c2a2.dest.colRow = 0x01;
   c2a2.capture = SPACE;
   c2a2.setWhiteMove(true);
   Move c2h2;
   c2h2.source.colRow = 0x31;
   c2h2.dest.colRow = 0x71;
   c2h2.capture = SPACE;
   c2h2.setWhiteMove(true);
   Move c2c1;
   c2c1.source.colRow = 0x31;
   c2c1.dest.colRow = 0x30;
   c2c1.capture = SPACE;
   c2c1.setWhiteMove(true);
   Move c2c8;
   c2c8.source.colRow = 0x31;
   c2c8.dest.colRow = 0x37;
   c2c8.capture = SPACE;
   c2c8.setWhiteMove(true);
   Move c2a1;
   c2a1.source.colRow = 0x31;
   c2a1.dest.colRow = 0x00;
   c2a1.capture = SPACE;
   c2a1.setWhiteMove(true);
   Move c2h8;
   c2h8.source.colRow = 0x31;
   c2h8.dest.colRow = 0x77;
   c2h8.capture = SPACE;
   c2h8.setWhiteMove(true);

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 23);
   assertUnit(moves.find(c2a4) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2a2) != moves.end());
   assertUnit(moves.find(c2h2) != moves.end());
   assertUnit(moves.find(c2c1) != moves.end());
   assertUnit(moves.find(c2c8) != moves.end());
   assertUnit(moves.find(c2a1) != moves.end());
   assertUnit(moves.find(c2h8) != moves.end());

   // TEARDOWN
   board.board[3][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .         p   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   p   .   .         4
 * 3     . . .           3
 * 2   p .(q). . . . p   2
 * 1     p p p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Queen queen(3, 1, true);
   queen.position.colRow = 0x31;
   board.board[3][1] = &queen;
   White white1(PAWN);
   White white2(PAWN);
   White white3(PAWN);
   White white4(PAWN);
   White white5(PAWN);
   White white6(PAWN);
   White white7(PAWN);
   White white8(PAWN);
   board.board[3][7] = &white1;
   board.board[5][3] = &white2;
   board.board[0][1] = &white3;
   board.board[7][1] = &white4;
   board.board[3][0] = &white5;
   board.board[0][4] = &white6;
   board.board[7][5] = &white7;
   board.board[1][3] = &white8;
   set <Move> moves;
   Move c2c3;
   c2c3.source.colRow = 0x31;
   c2c3.dest.colRow = 0x32;
   c2c3.capture = SPACE;
   c2c3.setWhiteMove(true);
   Move c2c4;
   c2c4.source.colRow = 0x31;
   c2c4.dest.colRow = 0x33;
   c2c4.capture = SPACE;
   c2c4.setWhiteMove(true);
   Move c2c5;
   c2c5.source.colRow = 0x31;
   c2c5.dest.colRow = 0x34;
   c2c5.capture = SPACE;
   c2c5.setWhiteMove(true);
   Move c2c6;
   c2c6.source.colRow = 0x31;
   c2c6.dest.colRow = 0x35;
   c2c6.capture = SPACE;
   c2c6.setWhiteMove(true);
   Move c2d2;
   c2d2.source.colRow = 0x31;
   c2d2.dest.colRow = 0x41;
   c2d2.capture = SPACE;
   c2d2.setWhiteMove(true);
   Move c2d3;
   c2d3.source.colRow = 0x31;
   c2d3.dest.colRow = 0x42;
   c2d3.capture = SPACE;
   c2d3.setWhiteMove(true);
   Move c2d4;
   c2d4.source.colRow = 0x31;
   c2d4.dest.colRow = 0x43;
   c2d4.capture = SPACE;
   c2d4.setWhiteMove(true);
   Move c2b2;
   c2b2.source.colRow = 0x31;
   c2b2.dest.colRow = 0x21;
   c2b2.capture = SPACE;
   c2b2.setWhiteMove(true);
   Move c2b3;
   c2b3.source.colRow = 0x31;
   c2b3.dest.colRow = 0x22;
   c2b3.capture = SPACE;
   c2b3.setWhiteMove(true);
   Move c2a3;
   c2a3.source.colRow = 0x31;
   c2a3.dest.colRow = 0x12;
   c2a3.capture = SPACE;
   c2a3.setWhiteMove(true);

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 10);
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2d4) != moves.end());
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2a3) != moves.end());

   // TEARDOWN
   board.board[3][1] = nullptr;
   board.board[3][7] = nullptr;
   board.board[5][3] = nullptr;
   board.board[0][1] = nullptr;
   board.board[7][1] = nullptr;
   board.board[3][0] = nullptr;
   board.board[0][4] = nullptr;
   board.board[7][5] = nullptr;
   board.board[1][3] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .         P   7
 * 6       .       .     6
 * 5       .     .       5
 * 4   P   .   .         4
 * 3     . . .           3
 * 2   P .(q). . . . P   2
 * 1     P P P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestQueen::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Queen queen(3, 1, true);
   queen.position.colRow = 0x31;
   board.board[3][1] = &queen;
   Black black1(PAWN);
   Black black2(PAWN);
   Black black3(PAWN);
   Black black4(PAWN);
   Black black5(PAWN);
   Black black6(PAWN);
   Black black7(PAWN);
   Black black8(PAWN);
   board.board[3][7] = &black1;
   board.board[5][3] = &black2;
   board.board[0][1] = &black3;
   board.board[7][1] = &black4;
   board.board[3][0] = &black5;
   board.board[0][4] = &black6;
   board.board[7][5] = &black7;
   board.board[1][3] = &black8;
   set <Move> moves;
   Move c2c3;
   c2c3.source.colRow = 0x31;
   c2c3.dest.colRow = 0x32;
   c2c3.capture = SPACE;
   c2c3.setWhiteMove(true);
   Move c2c4;
   c2c4.source.colRow = 0x31;
   c2c4.dest.colRow = 0x33;
   c2c4.capture = SPACE;
   c2c4.setWhiteMove(true);
   Move c2c5;
   c2c5.source.colRow = 0x31;
   c2c5.dest.colRow = 0x34;
   c2c5.capture = SPACE;
   c2c5.setWhiteMove(true);
   Move c2c6;
   c2c6.source.colRow = 0x31;
   c2c6.dest.colRow = 0x35;
   c2c6.capture = SPACE;
   c2c6.setWhiteMove(true);
   Move c2c7p;
   c2c7p.source.colRow = 0x31;
   c2c7p.dest.colRow = 0x36;
   c2c7p.capture = PAWN;
   c2c7p.setWhiteMove(true);
   Move c2d2;
   c2d2.source.colRow = 0x31;
   c2d2.dest.colRow = 0x41;
   c2d2.capture = SPACE;
   c2d2.setWhiteMove(true);
   Move c2d3;
   c2d3.source.colRow = 0x31;
   c2d3.dest.colRow = 0x42;
   c2d3.capture = SPACE;
   c2d3.setWhiteMove(true);
   Move c2e4p;
   c2e4p.source.colRow = 0x31;
   c2e4p.dest.colRow = 0x43;
   c2e4p.capture = PAWN;
   c2e4p.setWhiteMove(true);
   Move c2b2;
   c2b2.source.colRow = 0x31;
   c2b2.dest.colRow = 0x21;
   c2b2.capture = SPACE;
   c2b2.setWhiteMove(true);
   Move c2b3;
   c2b3.source.colRow = 0x31;
   c2b3.dest.colRow = 0x22;
   c2b3.capture = SPACE;
   c2b3.setWhiteMove(true);
   Move c2a4p;
   c2a4p.source.colRow = 0x31;
   c2a4p.dest.colRow = 0x13;
   c2a4p.capture = PAWN;
   c2a4p.setWhiteMove(true);
   Move c2a1p;
   c2a1p.source.colRow = 0x31;
   c2a1p.dest.colRow = 0x01;
   c2a1p.capture = PAWN;
   c2a1p.setWhiteMove(true);
   Move c2h1p;
   c2h1p.source.colRow = 0x31;
   c2h1p.dest.colRow = 0x71;
   c2h1p.capture = PAWN;
   c2h1p.setWhiteMove(true);
   Move c2h5p;
   c2h5p.source.colRow = 0x31;
   c2h5p.dest.colRow = 0x74;
   c2h5p.capture = PAWN;
   c2h5p.setWhiteMove(true);
   Move c2c0p;
   c2c0p.source.colRow = 0x31;
   c2c0p.dest.colRow = 0x30;
   c2c0p.capture = PAWN;
   c2c0p.setWhiteMove(true);
   Move c2b3p;
   c2b3p.source.colRow = 0x31;
   c2b3p.dest.colRow = 0x22;
   c2b3p.capture = PAWN;
   c2b3p.setWhiteMove(true);

   // EXERCISE
   queen.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 18);
   assertUnit(moves.find(c2c3) != moves.end());
   assertUnit(moves.find(c2c4) != moves.end());
   assertUnit(moves.find(c2c5) != moves.end());
   assertUnit(moves.find(c2c6) != moves.end());
   assertUnit(moves.find(c2c7p) != moves.end());
   assertUnit(moves.find(c2d2) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4p) != moves.end());
   assertUnit(moves.find(c2b2) != moves.end());
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2a4p) != moves.end());
   assertUnit(moves.find(c2a1p) != moves.end());
   assertUnit(moves.find(c2h1p) != moves.end());
   assertUnit(moves.find(c2h5p) != moves.end());
   assertUnit(moves.find(c2c0p) != moves.end());
   assertUnit(moves.find(c2b3p) != moves.end());

   // TEARDOWN
   board.board[3][1] = nullptr;
   board.board[3][7] = nullptr;
   board.board[5][3] = nullptr;
   board.board[0][1] = nullptr;
   board.board[7][1] = nullptr;
   board.board[3][0] = nullptr;
   board.board[0][4] = nullptr;
   board.board[7][5] = nullptr;
   board.board[1][3] = nullptr;
}


/*************************************
 * GET TYPE : queen
 * Input:
 * Output: QUEEN
 **************************************/
void TestQueen::getType()
{
   // SETUP
   const Queen queen(7, 7, false);
   PieceType pt = SPACE;

   // EXERCISE
   pt = queen.getType();

   // VERIFY
   assertUnit(pt == QUEEN);
}

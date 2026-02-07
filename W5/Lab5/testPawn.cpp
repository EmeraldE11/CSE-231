/***********************************************************************
 * Source File:
 *    TEST PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the pawn
 ************************************************************************/

#include "testPawn.h"
#include "piecePawn.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      



 /*************************************
  * GET MOVES Simple White
  * White pawn in the middle of the board: b4b5
  *
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5     .               5
  * 4    (p)              4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestPawn::getMoves_simpleWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 3, true);
   pawn.position.colRow = 0x13;
   board.board[1][3] = &pawn;
   set <Move> moves;
   Move b4b5;
   b4b5.source.colRow = 0x13;
   b4b5.dest.colRow = 0x14;
   b4b5.capture = SPACE;
   b4b5.setWhiteMove(true);

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);
   assertUnit(moves.find(b4b5) != moves.end());

   // TEARDOWN
   board.board[1][3] = nullptr;
}

/*************************************
 * GET MOVES Simple Black
 * Black pawn in the middle of the board: b4b3
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4    (P)              4
 * 3     .               3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_simpleBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 3, false);
   pawn.position.colRow = 0x13;
   board.board[1][3] = &pawn;
   set <Move> moves;
   Move b4b3;
   b4b3.source.colRow = 0x13;
   b4b3.dest.colRow = 0x12;
   b4b3.capture = SPACE;
   b4b3.setWhiteMove(false);

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 1);
   assertUnit(moves.find(b4b3) != moves.end());

   // TEARDOWN
   board.board[1][3] = nullptr;
}


/*************************************
 * GET MOVES Initial Advance White
 * White pawn initial advance: b2b3, b2b4
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4     .               4
 * 3     .               3
 * 2    (p)              2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 1, true);
   pawn.position.colRow = 0x11;
   board.board[1][1] = &pawn;
   set <Move> moves;
   Move b2b3;
   b2b3.source.colRow = 0x11;
   b2b3.dest.colRow = 0x12;
   b2b3.capture = SPACE;
   b2b3.setWhiteMove(true);
   Move b2b4;
   b2b4.source.colRow = 0x11;
   b2b4.dest.colRow = 0x13;
   b2b4.capture = SPACE;
   b2b4.setWhiteMove(true);

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b2b3) != moves.end());
   assertUnit(moves.find(b2b4) != moves.end());

   // TEARDOWN
   board.board[1][1] = nullptr;
}

/*************************************
 * GET MOVES Initial Advance Black
 * Black pawn initial advance: c7c6, c7c5
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7      (P)            7
 * 6       .             6
 * 5       .             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_initialAdvanceBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(2, 6, false);
   pawn.position.colRow = 0x26;
   board.board[2][6] = &pawn;
   set <Move> moves;
   Move c7c6;
   c7c6.source.colRow = 0x26;
   c7c6.dest.colRow = 0x25;
   c7c6.capture = SPACE;
   c7c6.setWhiteMove(false);
   Move c7c5;
   c7c5.source.colRow = 0x26;
   c7c5.dest.colRow = 0x24;
   c7c5.capture = SPACE;
   c7c5.setWhiteMove(false);

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(c7c6) != moves.end());
   assertUnit(moves.find(c7c5) != moves.end());

   // TEARDOWN
   board.board[2][6] = nullptr;
}


/*************************************
 * GET MOVES Capture White
 * Double capture with b7 blocked: b6a7p, b6c7p
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7   P P P             7
 * 6    (p)              6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 5, true);
   pawn.position.colRow = 0x15;
   board.board[1][5] = &pawn;
   Black black1(PAWN);
   board.board[0][6] = &black1;
   Black black2(PAWN);
   board.board[2][6] = &black2;
   White white(PAWN);
   board.board[1][6] = &white;
   set <Move> moves;
   Move b6a7p;
   b6a7p.source.colRow = 0x15;
   b6a7p.dest.colRow = 0x06;
   b6a7p.capture = PAWN;
   b6a7p.setWhiteMove(true);
   Move b6c7p;
   b6c7p.source.colRow = 0x15;
   b6c7p.dest.colRow = 0x26;
   b6c7p.capture = PAWN;
   b6c7p.setWhiteMove(true);

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b6a7p) != moves.end());
   assertUnit(moves.find(b6c7p) != moves.end());

   // TEARDOWN
   board.board[1][5] = nullptr;
   board.board[0][6] = nullptr;
   board.board[2][6] = nullptr;
   board.board[1][6] = nullptr;
}


/*************************************
 * GET MOVES Capture Black
 * Double capture with b5 blocked: b6a5p, b6c5p
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6    (P)              6
 * 5   p p p             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_captureBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 5, false);
   pawn.position.colRow = 0x15;
   board.board[1][5] = &pawn;
   White white1(PAWN);
   board.board[0][4] = &white1;
   White white2(PAWN);
   board.board[2][4] = &white2;
   Black black(PAWN);
   board.board[1][4] = &black;
   set <Move> moves;
   Move b6a5p;
   b6a5p.source.colRow = 0x15;
   b6a5p.dest.colRow = 0x04;
   b6a5p.capture = PAWN;
   b6a5p.setWhiteMove(false);
   Move b6c5p;
   b6c5p.source.colRow = 0x15;
   b6c5p.dest.colRow = 0x24;
   b6c5p.capture = PAWN;
   b6c5p.setWhiteMove(false);

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(b6a5p) != moves.end());
   assertUnit(moves.find(b6c5p) != moves.end());

   // TEARDOWN
   board.board[1][5] = nullptr;
   board.board[0][4] = nullptr;
   board.board[2][4] = nullptr;
   board.board[1][4] = nullptr;
}

/*************************************
 * GET MOVES Enpassant White
 * Enpassant with b6 blocked: b5a6E, b5c6E
 * 
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6   . P .             6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantWhite()
{
   // SETUP
   BoardEmpty board;
   board.moveNumber = 10;
   Pawn pawn(1, 4, true);
   pawn.position.colRow = 0x14;
   board.board[1][4] = &pawn;
   Black black1(PAWN);
   black1.lastMove = 9;
   board.board[0][4] = &black1;
   Black black2(PAWN);
   black2.lastMove = 9;
   board.board[2][4] = &black2;
   White white(PAWN);
   board.board[1][5] = &white;
   set <Move> moves;
   Move b5a6E;
   b5a6E.source.colRow = 0x14;
   b5a6E.dest.colRow = 0x05;
   b5a6E.capture = PAWN;
   b5a6E.setWhiteMove(true);
   b5a6E.setEnPassant();
   Move b5c6E;
   b5c6E.source.colRow = 0x14;
   b5c6E.dest.colRow = 0x25;
   b5c6E.capture = PAWN;
   b5c6E.setWhiteMove(true);
   b5c6E.setEnPassant();

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() >= 2);
   assertUnit(moves.find(b5a6E) != moves.end());
   assertUnit(moves.find(b5c6E) != moves.end());

   // TEARDOWN
   board.board[1][4] = nullptr;
   board.board[0][4] = nullptr;
   board.board[2][4] = nullptr;
   board.board[1][5] = nullptr;
}


/*************************************
 * GET MOVES Enpassant Black
 * Enpassant with f3 blocked: f4g3E, f4e3E
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4           p(P)p     4
 * 3           . p .     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantBlack()
{
   // SETUP
   BoardEmpty board;
   board.moveNumber = 11;
   Pawn pawn(5, 3, false);
   pawn.position.colRow = 0x53;
   board.board[5][3] = &pawn;
   White white1(PAWN);
   white1.lastMove = 10;
   board.board[4][3] = &white1;
   White white2(PAWN);
   white2.lastMove = 10;
   board.board[6][3] = &white2;
   Black black(PAWN);
   board.board[5][2] = &black;
   set <Move> moves;
   Move f4g3E;
   f4g3E.source.colRow = 0x53;
   f4g3E.dest.colRow = 0x62;
   f4g3E.capture = PAWN;
   f4g3E.setWhiteMove(false);
   f4g3E.setEnPassant();
   Move f4e3E;
   f4e3E.source.colRow = 0x53;
   f4e3E.dest.colRow = 0x42;
   f4e3E.capture = PAWN;
   f4e3E.setWhiteMove(false);
   f4e3E.setEnPassant();

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() >= 2);
   assertUnit(moves.find(f4g3E) != moves.end());
   assertUnit(moves.find(f4e3E) != moves.end());

   // TEARDOWN
   board.board[5][3] = nullptr;
   board.board[4][3] = nullptr;
   board.board[6][3] = nullptr;
   board.board[5][2] = nullptr;
}


/*************************************
 * GET MOVES Enpassant Denied
 * Enpassant: b6 is blocked with black pawn
 *            pawn at a5 moved twice
 *            pawn at c5 move two turns ago
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6     P               6
 * 5   P(p)P             5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_enpassantDenied()
{
   // SETUP
   BoardEmpty board;
   board.moveNumber = 10;
   Pawn pawn(1, 4, true);
   pawn.position.colRow = 0x14;
   board.board[1][4] = &pawn;
   Black black1(PAWN);
   black1.lastMove = 8;
   board.board[0][4] = &black1;
   Black black2(PAWN);
   black2.lastMove = 8;
   board.board[2][4] = &black2;
   Black black3(PAWN);
   board.board[1][5] = &black3;
   set <Move> moves;

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);
   for (auto it = moves.begin(); it != moves.end(); ++it)
   {
      assertUnit(it->getMoveType() != Move::ENPASSANT);
   }

   // TEARDOWN
   board.board[1][4] = nullptr;
   board.board[0][4] = nullptr;
   board.board[2][4] = nullptr;
   board.board[1][5] = nullptr;
}

/*************************************
 * GET MOVES Promotion White
 * Promotion white pawn b7 can capture two pawns: a8 and c8. 
 *          It can also move into b8. All three are promoted to queen: 
 *          b7a8pQ, b7b8Q, b7c8pQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   P . P             8
 * 7    (p)              7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionWhite()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(1, 6, true);
   pawn.position.colRow = 0x16;
   board.board[1][6] = &pawn;
   Black black1(PAWN);
   board.board[0][7] = &black1;
   Black black2(PAWN);
   board.board[2][7] = &black2;
   set <Move> moves;
   Move b7a8pQ;
   b7a8pQ.source.colRow = 0x16;
   b7a8pQ.dest.colRow = 0x07;
   b7a8pQ.capture = PAWN;
   b7a8pQ.setPromotion(QUEEN);
   b7a8pQ.setWhiteMove(true);
   Move b7b8Q;
   b7b8Q.source.colRow = 0x16;
   b7b8Q.dest.colRow = 0x17;
   b7b8Q.capture = SPACE;
   b7b8Q.setPromotion(QUEEN);
   b7b8Q.setWhiteMove(true);
   Move b7c8pQ;
   b7c8pQ.source.colRow = 0x16;
   b7c8pQ.dest.colRow = 0x27;
   b7c8pQ.capture = PAWN;
   b7c8pQ.setPromotion(QUEEN);
   b7c8pQ.setWhiteMove(true);

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(b7a8pQ) != moves.end());
   assertUnit(moves.find(b7b8Q) != moves.end());
   assertUnit(moves.find(b7c8pQ) != moves.end());

   // TEARDOWN
   board.board[1][6] = nullptr;
   board.board[0][7] = nullptr;
   board.board[2][7] = nullptr;
}


/*************************************
 * GET MOVES Promotion Black
 * Promotion: black pawn e2 can capture two rooks: d1 and f1.
 *            It can also move into e1. All three are promoted to quee
 *            e2d1rQ, e2e1Q, e2f1rQ
 *
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2          (P)        2
 * 1         r . r       1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestPawn::getMoves_promotionBlack()
{
   // SETUP
   BoardEmpty board;
   Pawn pawn(4, 1, false);
   pawn.position.colRow = 0x41;
   board.board[4][1] = &pawn;
   White white1(ROOK);
   board.board[3][0] = &white1;
   White white2(ROOK);
   board.board[5][0] = &white2;
   set <Move> moves;
   Move e2d1rQ;
   e2d1rQ.source.colRow = 0x41;
   e2d1rQ.dest.colRow = 0x30;
   e2d1rQ.capture = ROOK;
   e2d1rQ.setPromotion(QUEEN);
   e2d1rQ.setWhiteMove(false);
   Move e2e1Q;
   e2e1Q.source.colRow = 0x41;
   e2e1Q.dest.colRow = 0x40;
   e2e1Q.capture = SPACE;
   e2e1Q.setPromotion(QUEEN);
   e2e1Q.setWhiteMove(false);
   Move e2f1rQ;
   e2f1rQ.source.colRow = 0x41;
   e2f1rQ.dest.colRow = 0x50;
   e2f1rQ.capture = ROOK;
   e2f1rQ.setPromotion(QUEEN);
   e2f1rQ.setWhiteMove(false);

   // EXERCISE
   pawn.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(e2d1rQ) != moves.end());
   assertUnit(moves.find(e2e1Q) != moves.end());
   assertUnit(moves.find(e2f1rQ) != moves.end());

   // TEARDOWN
   board.board[4][1] = nullptr;
   board.board[3][0] = nullptr;
   board.board[5][0] = nullptr;
}


/*************************************
 * GET TYPE : pawn
 * Input:
 * Output: PAWN
 **************************************/
void TestPawn::getType()
{
   // SETUP
   const Pawn pawn(7, 7, false);
   PieceType pt = SPACE;

   // EXERCISE
   pt = pawn.getType();

   // VERIFY
   assertUnit(pt == PAWN);
}


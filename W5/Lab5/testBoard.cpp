/***********************************************************************
 * Source File:
 *    TEST BOARD
 * Author:
 *    Spencer Palmer
 * Summary:
 *    The unit tests for board
 ************************************************************************/


#include "testBoard.h"
#include "position.h"
#include "piece.h"
#include "board.h"
#include <cassert>



 /********************************************************
   *   a2a3
   * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
   * |                     |       |                     |
   * 8                     8       8                     8
   * 7                     7       7                     7
   * 6                     6       6                     6
   * 5                     5       5                     5
   * 4                     4  -->  4                     4
   * 3   .                 3       3   p                 3
   * 2  (p)                2       2   .                 2
   * 1                     1       1                     1
   * |                     |       |                     |
   * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
   ********************************************************/
void TestBoard::move_pawnSimple()
{
   // SETUP
   Move a2a3;
   a2a3.source.colRow = 0x01;
   a2a3.dest.colRow = 0x02;
   a2a3.capture = SPACE;
   a2a3.promote = SPACE;
   a2a3.isWhite = true;
   a2a3.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[0][1] = new PieceSpy(0, 1, true  /*isWhite*/, PAWN);
   board.board[0][2] = new PieceSpy(0, 2, false /*isWhite*/, SPACE);
   board.board[0][1]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(a2a3);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[0][1])->getType());
   assertUnit(PAWN == (board.board[0][2])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[0][2];
   delete board.board[0][1];
   board.board[0][2] = board.board[0][1] = nullptr;
}


/********************************************************
 *     a6b7r
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7     R               7       7    (p)              7
 * 6  (p)                6       6   .                 6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnCapture()
{
   // SETUP
   Move a6b7;
   a6b7.source.colRow = 0x05;
   a6b7.dest.colRow = 0x16;
   a6b7.capture = ROOK;
   a6b7.promote = SPACE;
   a6b7.isWhite = true;
   a6b7.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[0][5] = new PieceSpy(0, 5, true  /*isWhite*/, PAWN);
   board.board[1][6] = new PieceSpy(1, 6, false /*isWhite*/, ROOK);
   board.board[0][5]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(a6b7);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[0][5])->getType());
   assertUnit(PAWN == (board.board[1][6])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[1][6];
   delete board.board[0][5];
   board.board[1][6] = board.board[0][5] = nullptr;
}


/********************************************************
 *    e2e4
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4           .         4  -->  4          (p)        4
 * 3                     3       3                     3
 * 2          (p)        2       2           .         2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnDouble()
{
   // SETUP
   Move e2e4;
   e2e4.source.colRow = 0x41;
   e2e4.dest.colRow = 0x43;
   e2e4.capture = SPACE;
   e2e4.promote = SPACE;
   e2e4.isWhite = true;
   e2e4.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][1] = new PieceSpy(4, 1, true  /*isWhite*/, PAWN);
   board.board[4][3] = new PieceSpy(4, 3, false /*isWhite*/, SPACE);
   board.board[4][1]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e2e4);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][1])->getType());
   assertUnit(PAWN == (board.board[4][3])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][3];
   delete board.board[4][1];
   board.board[4][3] = board.board[4][1] = nullptr;
}


/********************************************************
*     a5b6E
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6     .               6       6     p               6
 * 5  (p)P               5       5   . .               5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnEnpassant()
{
   Move a5b6;
   a5b6.source.colRow = 0x04;
   a5b6.dest.colRow = 0x15;
   a5b6.capture = PAWN;
   a5b6.promote = SPACE;
   a5b6.isWhite = true;
   a5b6.moveType = Move::ENPASSANT;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[0][4] = new PieceSpy(0, 4, true  /*isWhite*/, PAWN);
   board.board[1][4] = new PieceSpy(1, 4, false /*isWhite*/, PAWN);
   board.board[0][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(a5b6);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[1][4])->getType());
   assertUnit(PAWN == (board.board[1][5])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[1][4];
   delete board.board[1][5];
   board.board[1][5] = board.board[1][4] = nullptr;
}


/********************************************************
 *    a7a8Q
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8   .                 8       8  (r)                8
 * 7  (p)                7       7   .                 7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_pawnPromotion()
{
   // SETUP
   Move a7a8;
   a7a8.source.colRow = 0x06;
   a7a8.dest.colRow = 0x07;
   a7a8.capture = SPACE;
   a7a8.promote = ROOK;
   a7a8.isWhite = true;
   a7a8.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[0][6] = new PieceSpy(4, 1, true  /*isWhite*/, PAWN);
   board.board[0][7] = new PieceSpy(4, 3, false /*isWhite*/, SPACE);
   board.board[0][6]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(a7a8);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[0][6])->getType());
   assertUnit(ROOK == (board.board[0][7])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[0][6];
   delete board.board[0][7];
   board.board[0][6] = board.board[0][7] = nullptr;
}


/********************************************************
 *    e5a5
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5   .      (r)        5       5  (r)      .         5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_rookSlide()
{
   // SETUP
   Move e5a5;
   e5a5.source.colRow = 0x44;
   e5a5.dest.colRow = 0x04;
   e5a5.capture = SPACE;
   e5a5.promote = SPACE;
   e5a5.isWhite = true;
   e5a5.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, ROOK);
   board.board[0][4] = new PieceSpy(0, 4, false /*isWhite*/, SPACE);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5a5);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(ROOK == (board.board[0][4])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][4];
   delete board.board[0][4];
   board.board[4][4] = board.board[0][4] = nullptr;
}


/********************************************************
 *    e5a5b
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5   B      (r)        5       5  (r)      .         5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_rookAttack()
{
   // SETUP
   Move e5a5;
   e5a5.source.colRow = 0x44;
   e5a5.dest.colRow = 0x04;
   e5a5.capture = BISHOP;
   e5a5.promote = SPACE;
   e5a5.isWhite = true;
   e5a5.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, ROOK);
   board.board[0][4] = new PieceSpy(0, 4, false /*isWhite*/, BISHOP);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5a5);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(ROOK == (board.board[0][4])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][4];
   delete board.board[0][4];
   board.board[4][4] = board.board[0][4] = nullptr;
}


/********************************************************
 *    e5g3
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5          (b)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3               .     3       3               b     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_bishopSlide()
{
   // SETUP
   Move e5g3;
   e5g3.source.colRow = 0x44;
   e5g3.dest.colRow = 0x62;
   e5g3.capture = SPACE;
   e5g3.promote = SPACE;
   e5g3.isWhite = true;
   e5g3.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, BISHOP);
   board.board[6][2] = new PieceSpy(6, 2, false /*isWhite*/, SPACE);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5g3);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(BISHOP == (board.board[6][2])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][4];
   delete board.board[6][2];
   board.board[4][4] = board.board[6][2] = nullptr;
}


/********************************************************
 *    e5g3q
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5          (b)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3               Q     3       3               b     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_bishopAttack()
{
   Move e5g3;
   e5g3.source.colRow = 0x44;
   e5g3.dest.colRow = 0x62;
   e5g3.capture = QUEEN;
   e5g3.promote = SPACE;
   e5g3.isWhite = true;
   e5g3.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, BISHOP);
   board.board[6][2] = new PieceSpy(6, 2, false /*isWhite*/, QUEEN);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5g3);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(BISHOP == (board.board[6][2])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][4];
   delete board.board[6][2];
   board.board[4][4] = board.board[6][2] = nullptr;
}

/********************************************************
 *    e5g3
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5          (q)        5       5                     5
 * 4                     4  -->  4           .         4
 * 3                .    3       3               q     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_queenSlide()
{
   // SETUP
   Move e5g3;
   e5g3.source.colRow = 0x44;
   e5g3.dest.colRow = 0x62;
   e5g3.capture = SPACE;
   e5g3.promote = SPACE;
   e5g3.isWhite = true;
   e5g3.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, QUEEN);
   board.board[6][2] = new PieceSpy(6, 2, false /*isWhite*/, SPACE);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5g3);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(QUEEN == (board.board[6][2])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][4];
   delete board.board[6][2];
   board.board[4][4] = board.board[6][2] = nullptr;
}


/********************************************************
*    e5a5b
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
* |                     |       |                     |
* 8                     8       8                     8
* 7                     7       7                     7
* 6                     6       6                     6
* 5   B      (q)        5       5  (q)      .         5
* 4                     4  -->  4                     4
* 3                     3       3                     3
* 2                     2       2                     2
* 1                     1       1                     1
* |                     |       |                     |
* +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
********************************************************/
void TestBoard::move_queenAttack()
{
   // SETUP
   Move e5a5;
   e5a5.source.colRow = 0x44;
   e5a5.dest.colRow = 0x04;
   e5a5.capture = BISHOP;
   e5a5.promote = SPACE;
   e5a5.isWhite = true;
   e5a5.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, QUEEN);
   board.board[0][4] = new PieceSpy(0, 4, false /*isWhite*/, BISHOP);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5a5);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(QUEEN == (board.board[0][4])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][4];
   delete board.board[0][4];
   board.board[4][4] = board.board[0][4] = nullptr;
}


/********************************************************
 *  e1f1
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1          (k).       1       1           . k       1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_kingMove()
{
   // SETUP
   Move e1f1;
   e1f1.source.colRow = 0x40;
   e1f1.dest.colRow = 0x50;
   e1f1.capture = SPACE;
   e1f1.promote = SPACE;
   e1f1.isWhite = true;
   e1f1.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][0] = new PieceSpy(4, 0, true  /*isWhite*/, KING);
   board.board[5][0] = new PieceSpy(5, 0, false /*isWhite*/, SPACE);
   board.board[4][0]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e1f1);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][0])->getType());
   assertUnit(KING == (board.board[5][0])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][0];
   delete board.board[5][0];
   board.board[4][0] = board.board[5][0] = nullptr;
}


/********************************************************
 *    e1f1r
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1          (k)R       1       1           . k       1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_kingAttack()
{
   // SETUP
   Move e1f1;
   e1f1.source.colRow = 0x40;
   e1f1.dest.colRow = 0x50;
   e1f1.capture = ROOK;
   e1f1.promote = SPACE;
   e1f1.isWhite = true;
   e1f1.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][0] = new PieceSpy(4, 0, true  /*isWhite*/, KING);
   board.board[5][0] = new PieceSpy(5, 0, false /*isWhite*/, ROOK);
   board.board[4][0]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e1f1);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][0])->getType());
   assertUnit(KING == (board.board[5][0])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][0];
   delete board.board[5][0];
   board.board[4][0] = board.board[5][0] = nullptr;
}

/********************************************************
 *    e1g1c
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1          (k). . r   1       1           . r k .   1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_kingShortCastle()
{
   // SETUP
   Move e1g1; // Castling also moves a rook.
   e1g1.source.colRow = 0x40;
   e1g1.dest.colRow = 0x60;
   e1g1.capture = SPACE;
   e1g1.promote = SPACE;
   e1g1.isWhite = true;
   e1g1.moveType = Move::CASTLE_KING;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][0] = new PieceSpy(4, 0, true  /*isWhite*/, KING);
   board.board[7][0] = new PieceSpy(7, 0, false /*isWhite*/, ROOK);
   board.board[6][0] = new PieceSpy(6, 0, false /*isWhite*/, SPACE);
   board.board[4][0]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e1g1);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[7][0])->getType());
   assertUnit(KING == (board.board[6][0])->getType());
   assertUnit(ROOK == (board.board[4][0])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][0];
   delete board.board[6][0];
   delete board.board[7][0];
   board.board[4][0] = board.board[7][0] = board.board[6][0] = nullptr;
}



/********************************************************
 *    e1c1C
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6                     6       6                     6
 * 5                     5       5                     5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1   r . . .(k)        1       1   . . k r .         1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_kingLongCastle()
{
   Move e1c1; // Castling also moves a rook.
   e1c1.source.colRow = 0x40;
   e1c1.dest.colRow = 0x20;
   e1c1.capture = SPACE;
   e1c1.promote = SPACE;
   e1c1.isWhite = true;
   e1c1.moveType = Move::CASTLE_QUEEN;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][0] = new PieceSpy(4, 0, true  /*isWhite*/, KING);
   board.board[0][0] = new PieceSpy(0, 0, false /*isWhite*/, ROOK);
   board.board[2][0] = new PieceSpy(2, 0, false /*isWhite*/, SPACE);
   board.board[3][0] = new PieceSpy(3, 0, false /*isWhite*/, SPACE);
   board.board[4][0]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e1c1);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[0][0])->getType());
   assertUnit(KING == (board.board[2][0])->getType());
   assertUnit(ROOK == (board.board[3][0])->getType());
   assertUnit(SPACE == (board.board[4][0])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[4][0];
   delete board.board[3][0];
   delete board.board[2][0];
   delete board.board[0][0];
   board.board[4][0] = board.board[3][0] = board.board[2][0] = board.board[0][0] = nullptr;
}



/********************************************************
 *        +---a-b-c-d-e-f-g-h---+
 *        |                     |
 *        8   R N B Q K B N R   8
 *        7   P P P P P P P P   7
 *        6                     6
 *        5                     5
 *   -->  4                     4
 *        3                     3
 *        2   p p p p p p p p   2
 *        1   r n b q k b n r   1
 *        |                     |
 *        +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::construct_default()
{
   // SETUP
   Board board(nullptr, false);
   
   // Verify Black back-rank (row 0)
   assertUnit(board[Position(0, 0)].getType() == ROOK);
   assertUnit(board[Position(0, 0)].isWhite() == true);
   assertUnit(board[Position(1, 0)].getType() == KNIGHT);
   assertUnit(board[Position(4, 0)].getType() == KING);

   // Verify Black pawns (row 1)
   for (int c = 0; c < 8; c++)
   {
      assertUnit(board[Position(c, 1)].getType() == PAWN);
      assertUnit(board[Position(c, 1)].isWhite() == true);
   }

   // Verify middle empty spaces (rows 2-5)
   for (int r = 2; r <= 5; r++)
   {
      for (int c = 0; c < 8; c++)
      {
         assertUnit(board[Position(c, r)].getType() == SPACE);
      }
   }

   // Verify White pawns (row 6)
   for (int c = 0; c < 8; c++)
   {
      assertUnit(board[Position(c, 6)].getType() == PAWN);
      assertUnit(board[Position(c, 6)].isWhite() == false);
   }

   // Verify White back-rank (row 7)
   assertUnit(board[Position(0, 7)].getType() == ROOK);
   assertUnit(board[Position(0, 7)].isWhite() == false);
   assertUnit(board[Position(3, 7)].getType() == QUEEN);
   assertUnit(board[Position(7, 7)].getType() == ROOK);
   
   // TEARDOWN
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
      {
         delete board.board[c][r];
         board.board[c][r] = nullptr;
      }
}



/********************************************************
 *    e5c6
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7                     7       7                     7
 * 6       .             6       6       n             6
 * 5          (n)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 ********************************************************/
void TestBoard::move_knightMove()
{  // SETUP
   Move e5c6;
   e5c6.source.colRow = 0x44;
   e5c6.dest.colRow = 0x25;
   e5c6.capture = SPACE;
   e5c6.promote = SPACE;
   e5c6.isWhite = true;
   e5c6.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, KNIGHT);
   board.board[2][5] = new PieceSpy(2, 5, false /*isWhite*/, SPACE);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5c6);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(KNIGHT == (board.board[2][5])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[2][5];
   delete board.board[4][4];
   board.board[2][5] = board.board[4][4] = nullptr;
}



 /********************************************************
 *    e5c6r
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
 * |                     |       |                     |
 * 8                     8       8                     8
 * 7       R             7       7                     7
 * 6                     6       6       n             6
 * 5          (n)        5       5           .         5
 * 4                     4  -->  4                     4
 * 3                     3       3                     3
 * 2                     2       2                     2
 * 1                     1       1                     1
 * |                     |       |                     |
 * +---a-b-c-d-e-f-g-h---+       +---a-b-c-d-e-f-g-h---+
  ********************************************************/
void TestBoard::move_knightAttack()
{  // SETUP
   Move e5c6r;
   e5c6r.source.colRow = 0x44;
   e5c6r.dest.colRow = 0x25;
   e5c6r.capture = ROOK;
   e5c6r.promote = SPACE;
   e5c6r.isWhite = true;
   e5c6r.moveType = Move::MOVE;
   Board board(nullptr, true /*noreset*/);
   board.numMoves = 17;
   board.board[4][4] = new PieceSpy(4, 4, true  /*isWhite*/, KNIGHT);
   board.board[2][5] = new PieceSpy(2, 5, false /*isWhite*/, ROOK);
   board.board[4][4]->nMoves = 17;
   PieceSpy::reset();

   // EXERCISE
   board.move(e5c6r);

   // VERIFY
   assertUnit(18 == board.numMoves);
   assertUnit(SPACE == (board.board[4][4])->getType());
   assertUnit(KNIGHT == (board.board[2][5])->getType());
   assertUnit(PieceSpy::numConstruct == 0);
   assertUnit(PieceSpy::numCopy == 0);
   assertUnit(PieceSpy::numDelete == 0);
   assertUnit(PieceSpy::numAssign == 0);
   assertUnit(PieceSpy::numMove == 0);

   // TEARDOWN
   delete board.board[2][5];
   delete board.board[4][4];
   board.board[2][5] = board.board[4][4] = nullptr;
}


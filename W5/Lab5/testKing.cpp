/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
#include "pieceRook.h"
#include "pieceKing.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       p p p         6
 * 5       p(k)p         5
 * 4       p p p         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   King king(4, 4, true);
   king.position.colRow = 0x44;
   board.board[4][4] = &king;
   White white1(PAWN);
   White white2(PAWN);
   White white3(PAWN);
   White white4(PAWN);
   White white5(PAWN);
   White white6(PAWN);
   White white7(PAWN);
   White white8(PAWN);
   board.board[3][5] = &white1;
   board.board[4][5] = &white2;
   board.board[5][5] = &white3;
   board.board[3][4] = &white4;
   board.board[5][4] = &white5;
   board.board[3][3] = &white6;
   board.board[4][3] = &white7;
   board.board[5][3] = &white8;
   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);

   // TEARDOWN
   board.board[4][4] = nullptr;
   board.board[3][5] = nullptr;
   board.board[4][5] = nullptr;
   board.board[5][5] = nullptr;
   board.board[3][4] = nullptr;
   board.board[5][4] = nullptr;
   board.board[3][3] = nullptr;
   board.board[4][3] = nullptr;
   board.board[5][3] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   King king(4, 4, true);
   king.position.colRow = 0x44;
   board.board[4][4] = &king;
   Black black1(PAWN);
   Black black2(PAWN);
   Black black3(PAWN);
   Black black4(PAWN);
   Black black5(PAWN);
   Black black6(PAWN);
   Black black7(PAWN);
   Black black8(PAWN);
   board.board[3][5] = &black1;
   board.board[4][5] = &black2;
   board.board[5][5] = &black3;
   board.board[3][4] = &black4;
   board.board[5][4] = &black5;
   board.board[3][3] = &black6;
   board.board[4][3] = &black7;
   board.board[5][3] = &black8;
   set <Move> moves;
   Move e5d6p;
   e5d6p.source.colRow = 0x44;
   e5d6p.dest.colRow = 0x35;
   e5d6p.capture = PAWN;
   e5d6p.setWhiteMove(true);
   Move e5e6p;
   e5e6p.source.colRow = 0x44;
   e5e6p.dest.colRow = 0x45;
   e5e6p.capture = PAWN;
   e5e6p.setWhiteMove(true);
   Move e5f6p;
   e5f6p.source.colRow = 0x44;
   e5f6p.dest.colRow = 0x55;
   e5f6p.capture = PAWN;
   e5f6p.setWhiteMove(true);
   Move e5d5p;
   e5d5p.source.colRow = 0x44;
   e5d5p.dest.colRow = 0x34;
   e5d5p.capture = PAWN;
   e5d5p.setWhiteMove(true);
   Move e5f5p;
   e5f5p.source.colRow = 0x44;
   e5f5p.dest.colRow = 0x54;
   e5f5p.capture = PAWN;
   e5f5p.setWhiteMove(true);
   Move e5d4p;
   e5d4p.source.colRow = 0x44;
   e5d4p.dest.colRow = 0x33;
   e5d4p.capture = PAWN;
   e5d4p.setWhiteMove(true);
   Move e5e4p;
   e5e4p.source.colRow = 0x44;
   e5e4p.dest.colRow = 0x43;
   e5e4p.capture = PAWN;
   e5e4p.setWhiteMove(true);
   Move e5f4p;
   e5f4p.source.colRow = 0x44;
   e5f4p.dest.colRow = 0x53;
   e5f4p.capture = PAWN;
   e5f4p.setWhiteMove(true);

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(e5d6p) != moves.end());
   assertUnit(moves.find(e5e6p) != moves.end());
   assertUnit(moves.find(e5f6p) != moves.end());
   assertUnit(moves.find(e5d5p) != moves.end());
   assertUnit(moves.find(e5f5p) != moves.end());
   assertUnit(moves.find(e5d4p) != moves.end());
   assertUnit(moves.find(e5e4p) != moves.end());
   assertUnit(moves.find(e5f4p) != moves.end());

   // TEARDOWN
   board.board[4][4] = nullptr;
   board.board[3][5] = nullptr;
   board.board[4][5] = nullptr;
   board.board[5][5] = nullptr;
   board.board[3][4] = nullptr;
   board.board[5][4] = nullptr;
   board.board[3][3] = nullptr;
   board.board[4][3] = nullptr;
   board.board[5][3] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{
   // SETUP
   BoardEmpty board;
   King king(4, 4, true);
   king.position.colRow = 0x44;
   board.board[4][4] = &king;
   set <Move> moves;
   Move e5d6;
   e5d6.source.colRow = 0x44;
   e5d6.dest.colRow = 0x35;
   e5d6.capture = SPACE;
   e5d6.setWhiteMove(true);
   Move e5e6;
   e5e6.source.colRow = 0x44;
   e5e6.dest.colRow = 0x45;
   e5e6.capture = SPACE;
   e5e6.setWhiteMove(true);
   Move e5f6;
   e5f6.source.colRow = 0x44;
   e5f6.dest.colRow = 0x55;
   e5f6.capture = SPACE;
   e5f6.setWhiteMove(true);
   Move e5d5;
   e5d5.source.colRow = 0x44;
   e5d5.dest.colRow = 0x34;
   e5d5.capture = SPACE;
   e5d5.setWhiteMove(true);
   Move e5f5;
   e5f5.source.colRow = 0x44;
   e5f5.dest.colRow = 0x54;
   e5f5.capture = SPACE;
   e5f5.setWhiteMove(true);
   Move e5d4;
   e5d4.source.colRow = 0x44;
   e5d4.dest.colRow = 0x33;
   e5d4.capture = SPACE;
   e5d4.setWhiteMove(true);
   Move e5e4;
   e5e4.source.colRow = 0x44;
   e5e4.dest.colRow = 0x43;
   e5e4.capture = SPACE;
   e5e4.setWhiteMove(true);
   Move e5f4;
   e5f4.source.colRow = 0x44;
   e5f4.dest.colRow = 0x53;
   e5f4.capture = SPACE;
   e5f4.setWhiteMove(true);

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(e5d6) != moves.end());
   assertUnit(moves.find(e5e6) != moves.end());
   assertUnit(moves.find(e5f6) != moves.end());
   assertUnit(moves.find(e5d5) != moves.end());
   assertUnit(moves.find(e5f5) != moves.end());
   assertUnit(moves.find(e5d4) != moves.end());
   assertUnit(moves.find(e5e4) != moves.end());
   assertUnit(moves.find(e5f4) != moves.end());

   // TEARDOWN
   board.board[4][4] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   King king(0, 0, true);
   king.position.colRow = 0x00;
   board.board[0][0] = &king;
   set <Move> moves;
   Move a1a2;
   a1a2.source.colRow = 0x00;
   a1a2.dest.colRow = 0x01;
   a1a2.capture = SPACE;
   a1a2.setWhiteMove(true);
   Move a1b1;
   a1b1.source.colRow = 0x00;
   a1b1.dest.colRow = 0x10;
   a1b1.capture = SPACE;
   a1b1.setWhiteMove(true);
   Move a1b2;
   a1b2.source.colRow = 0x00;
   a1b2.dest.colRow = 0x11;
   a1b2.capture = SPACE;
   a1b2.setWhiteMove(true);

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(a1a2) != moves.end());
   assertUnit(moves.find(a1b1) != moves.end());
   assertUnit(moves.find(a1b2) != moves.end());

   // TEARDOWN
   board.board[0][0] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
   // SETUP
   BoardEmpty board;
   King king(4, 0, true);
   king.position.colRow = 0x40;
   king.nMoves = 0;
   board.board[4][0] = &king;
   White rook1(ROOK);
   rook1.nMoves = 0;
   board.board[0][0] = &rook1;
   White rook2(ROOK);
   rook2.nMoves = 0;
   board.board[7][0] = &rook2;
   White pawn1(PAWN);
   board.board[3][1] = &pawn1;
   White pawn2(PAWN);
   board.board[4][1] = &pawn2;
   White pawn3(PAWN);
   board.board[5][1] = &pawn3;
   set <Move> moves;
   Move e1c1C;
   e1c1C.source.colRow = 0x40;
   e1c1C.dest.colRow = 0x20;
   e1c1C.capture = SPACE;
   e1c1C.setWhiteMove(true);
   e1c1C.setCastle(false);
   Move e1g1c;
   e1g1c.source.colRow = 0x40;
   e1g1c.dest.colRow = 0x60;
   e1g1c.capture = SPACE;
   e1g1c.setWhiteMove(true);
   e1g1c.setCastle(true);

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() >= 2);
   assertUnit(moves.find(e1c1C) != moves.end());
   assertUnit(moves.find(e1g1c) != moves.end());

   // TEARDOWN
   board.board[4][0] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[3][1] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blackCastle()
{
   // SETUP
   BoardEmpty board;
   King king(4, 7, false);
   king.position.colRow = 0x47;
   king.nMoves = 0;
   board.board[4][7] = &king;
   Black rook1(ROOK);
   rook1.nMoves = 0;
   board.board[0][7] = &rook1;
   Black rook2(ROOK);
   rook2.nMoves = 0;
   board.board[7][7] = &rook2;
   Black pawn1(PAWN);
   board.board[3][6] = &pawn1;
   Black pawn2(PAWN);
   board.board[4][6] = &pawn2;
   Black pawn3(PAWN);
   board.board[5][6] = &pawn3;
   set <Move> moves;
   Move e8c8C;
   e8c8C.source.colRow = 0x47;
   e8c8C.dest.colRow = 0x27;
   e8c8C.capture = SPACE;
   e8c8C.setWhiteMove(false);
   e8c8C.setCastle(false);
   Move e8g8c;
   e8g8c.source.colRow = 0x47;
   e8g8c.dest.colRow = 0x67;
   e8g8c.capture = SPACE;
   e8g8c.setWhiteMove(false);
   e8g8c.setCastle(true);

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() >= 2);
   assertUnit(moves.find(e8c8C) != moves.end());
   assertUnit(moves.find(e8g8c) != moves.end());

   // TEARDOWN
   board.board[4][7] = nullptr;
   board.board[0][7] = nullptr;
   board.board[7][7] = nullptr;
   board.board[3][6] = nullptr;
   board.board[4][6] = nullptr;
   board.board[5][6] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
   // SETUP
   BoardEmpty board;
   King king(4, 0, true);
   king.position.colRow = 0x40;
   king.nMoves = 1;
   board.board[4][0] = &king;
   White rook1(ROOK);
   rook1.nMoves = 0;
   board.board[0][0] = &rook1;
   White rook2(ROOK);
   rook2.nMoves = 0;
   board.board[7][0] = &rook2;
   White pawn1(PAWN);
   board.board[3][1] = &pawn1;
   White pawn2(PAWN);
   board.board[4][1] = &pawn2;
   White pawn3(PAWN);
   board.board[5][1] = &pawn3;
   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() >= 0);
   for (auto it = moves.begin(); it != moves.end(); ++it)
   {
      assertUnit(it->getMoveType() != Move::CASTLE_KING);
      assertUnit(it->getMoveType() != Move::CASTLE_QUEEN);
   }

   // TEARDOWN
   board.board[4][0] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[3][1] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
   // SETUP
   BoardEmpty board;
   King king(4, 0, true);
   king.position.colRow = 0x40;
   king.nMoves = 0;
   board.board[4][0] = &king;
   White rook1(ROOK);
   rook1.nMoves = 1;
   board.board[0][0] = &rook1;
   White rook2(ROOK);
   rook2.nMoves = 1;
   board.board[7][0] = &rook2;
   White pawn1(PAWN);
   board.board[3][1] = &pawn1;
   White pawn2(PAWN);
   board.board[4][1] = &pawn2;
   White pawn3(PAWN);
   board.board[5][1] = &pawn3;
   set <Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() >= 0);
   for (auto it = moves.begin(); it != moves.end(); ++it)
   {
      assertUnit(it->getMoveType() != Move::CASTLE_KING);
      assertUnit(it->getMoveType() != Move::CASTLE_QUEEN);
   }

   // TEARDOWN
   board.board[4][0] = nullptr;
   board.board[0][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[3][1] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{
   // SETUP
   const King king(7, 7, false);
   PieceType pt = SPACE;

   // EXERCISE
   pt = king.getType();

   // VERIFY
   assertUnit(pt == KING);
}



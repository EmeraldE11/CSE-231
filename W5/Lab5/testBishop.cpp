/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    Noah McCarthy
 * Summary:
 *    The unit tests for a bishop
 ************************************************************************/


#include "testBishop.h"
#include "pieceBishop.h"     
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
 * 3     p   p           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_blocked()
{
   // SETUP
	BoardEmpty board;
	Bishop bishop(3, 1, true); // d2
	bishop.fWhite = true;
	bishop.position.colRow = 0x31;
	board.board[3][1] = &bishop;

	White white1(PAWN);
	White white2(PAWN);
	White white3(PAWN);
	White white4(PAWN);

	board.board[2][2] = &white1; // c3
	board.board[4][2] = &white2; // e3
	board.board[2][0] = &white3; // c1
	board.board[4][0] = &white4; // e1

	set <Move> moves;

	// EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 0);

   // TEARDOWN
   board.board[3][1] = nullptr;
   board.board[2][2] = nullptr;
   board.board[4][2] = nullptr;
   board.board[2][0] = nullptr;
   board.board[4][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToEnd()
{
	// SETUP
	BoardEmpty board;
	Bishop bishop(3, 1, true); // d2
	bishop.fWhite = true;
	bishop.position.colRow = 0x31;
	board.board[3][1] = &bishop;

	set <Move> moves;

	Move d2c3; d2c3.source.colRow = 0x31; d2c3.dest.colRow = 0x22; d2c3.capture = SPACE; d2c3.setWhiteMove(true);
	Move d2b4; d2b4.source.colRow = 0x31; d2b4.dest.colRow = 0x13; d2b4.capture = SPACE; d2b4.setWhiteMove(true);
	Move d2a5; d2a5.source.colRow = 0x31; d2a5.dest.colRow = 0x04; d2a5.capture = SPACE; d2a5.setWhiteMove(true);

	Move d2e3; d2e3.source.colRow = 0x31; d2e3.dest.colRow = 0x42; d2e3.capture = SPACE; d2e3.setWhiteMove(true);
	Move d2f4; d2f4.source.colRow = 0x31; d2f4.dest.colRow = 0x53; d2f4.capture = SPACE; d2f4.setWhiteMove(true);
	Move d2g5; d2g5.source.colRow = 0x31; d2g5.dest.colRow = 0x64; d2g5.capture = SPACE; d2g5.setWhiteMove(true);
	Move d2h6; d2h6.source.colRow = 0x31; d2h6.dest.colRow = 0x75; d2h6.capture = SPACE; d2h6.setWhiteMove(true);


	Move d2c1; d2c1.source.colRow = 0x31; d2c1.dest.colRow = 0x20; d2c1.capture = SPACE; d2c1.setWhiteMove(true);
	Move d2e1; d2e1.source.colRow = 0x31; d2e1.dest.colRow = 0x40; d2e1.capture = SPACE; d2e1.setWhiteMove(true);

	// EXERCISE
	bishop.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 9);
	assertUnit(moves.find(d2c3) != moves.end());
	assertUnit(moves.find(d2b4) != moves.end());
	assertUnit(moves.find(d2a5) != moves.end());
	assertUnit(moves.find(d2e3) != moves.end());
	assertUnit(moves.find(d2f4) != moves.end());
	assertUnit(moves.find(d2g5) != moves.end());
	assertUnit(moves.find(d2h6) != moves.end());
	assertUnit(moves.find(d2c1) != moves.end());
	assertUnit(moves.find(d2e1) != moves.end());

	// TEARDOWN
	board.board[3][1] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToBlock()
{
	// SETUP
	BoardEmpty board;
	Bishop bishop(3, 1, true); // d2
	bishop.fWhite = true;
	bishop.position.colRow = 0x31;
	board.board[3][1] = &bishop;

	Black black1(PAWN);
	Black black2(PAWN);

	White white1(PAWN);
	White white2(PAWN);
	White white3(PAWN);

	board.board[0][4] = &black1; // a5
	board.board[6][6] = &black2; // g7

	board.board[4][2] = &white1; // e3
	board.board[2][0] = &white2; // c1
	board.board[4][0] = &white3; // e1

	set <Move> moves;

	Move d2c3; d2c3.source.colRow = 0x31; d2c3.dest.colRow = 0x22; d2c3.capture = SPACE; d2c3.setWhiteMove(true);
	Move d2b4; d2b4.source.colRow = 0x31; d2b4.dest.colRow = 0x13; d2b4.capture = SPACE; d2b4.setWhiteMove(true);
	Move d2a5; d2a5.source.colRow = 0x31; d2a5.dest.colRow = 0x04; d2a5.capture = PAWN; d2a5.setWhiteMove(true);

	// EXERCISE
	bishop.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 3);
	assertUnit(moves.find(d2c3) != moves.end());
	assertUnit(moves.find(d2b4) != moves.end());
	assertUnit(moves.find(d2a5) != moves.end());

	// TEARDOWN
	board.board[3][1] = nullptr;
	board.board[0][4] = nullptr;
	board.board[6][6] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToCapture()
{
	// SETUP
	BoardEmpty board;
	Bishop bishop(3, 1, true); // d2
	bishop.fWhite = true;
	bishop.position.colRow = 0x31;
	board.board[3][1] = &bishop;

	Black black1(PAWN);
	board.board[4][2] = &black1; // e3

	White white1(PAWN);
	White white2(PAWN);
	White white3(PAWN);

	board.board[2][2] = &white1; // c3
	board.board[2][0] = &white2; // c1
	board.board[4][0] = &white3; // e1


	set<Move> moves;
	Move d2e3;
	d2e3.source.colRow = 0x31;
	d2e3.dest.colRow = 0x42;
	d2e3.capture = PAWN;
	d2e3.setWhiteMove(true);

	// EXERCISE
	bishop.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 1);
	assertUnit(moves.find(d2e3) != moves.end());

	// TEARDOWN
	board.board[3][1] = nullptr;
	board.board[4][2] = nullptr;
}


/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
	// SETUP
	const Bishop bishop(3, 1, true); // d2
	PieceType pt = SPACE;

	// EXERCISE
	pt = bishop.getType();

	// VERIFY
	assertUnit(pt == BISHOP);
}

/***********************************************************************
 * Source File:
 *    TEST ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the rook
 ************************************************************************/

#include "testRook.h"
#include "pieceRook.h"     
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
 * 3       p             3
 * 2     p(r)p           2
 * 1       p             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_blocked()
{
	// SETUP
	BoardEmpty board;
	Rook rook(3, 1, true); // d2
	rook.fWhite = true;
	rook.position.colRow = 0x31;
	board.board[3][1] = &rook;

	White white1(PAWN);
	White white2(PAWN);
	White white3(PAWN);
	White white4(PAWN);

	board.board[3][2] = &white1; // d3
	board.board[3][0] = &white2; // d1
	board.board[2][1] = &white3; // c2
	board.board[4][1] = &white4; // e2

	set <Move> moves;

	// EXERCISE
	rook.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 0);

	// TEARDOWN
	board.board[3][1] = nullptr;
	board.board[3][2] = nullptr;
	board.board[3][0] = nullptr;
	board.board[2][1] = nullptr;
	board.board[4][1] = nullptr;
}



/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       .             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   . .(r). . . . .   2
 * 1       .             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToEnd()
{
	// SETUP
	BoardEmpty board;
	Rook rook(3, 1, true); // d2
	rook.fWhite = true;
	rook.position.colRow = 0x31;
	board.board[3][1] = &rook;

	set <Move> moves;

	Move d2d3; d2d3.source.colRow = 0x31; d2d3.dest.colRow = 0x32; d2d3.capture = SPACE; d2d3.setWhiteMove(true);
	Move d2d4; d2d4.source.colRow = 0x31; d2d4.dest.colRow = 0x33; d2d4.capture = SPACE; d2d4.setWhiteMove(true);
	Move d2d5; d2d5.source.colRow = 0x31; d2d5.dest.colRow = 0x34; d2d5.capture = SPACE; d2d5.setWhiteMove(true);
	Move d2d6; d2d6.source.colRow = 0x31; d2d6.dest.colRow = 0x35; d2d6.capture = SPACE; d2d6.setWhiteMove(true);
	Move d2d7; d2d7.source.colRow = 0x31; d2d7.dest.colRow = 0x36; d2d7.capture = SPACE; d2d7.setWhiteMove(true);
	Move d2d8; d2d8.source.colRow = 0x31; d2d8.dest.colRow = 0x37; d2d8.capture = SPACE; d2d8.setWhiteMove(true);

	Move d2d1; d2d1.source.colRow = 0x31; d2d1.dest.colRow = 0x30; d2d1.capture = SPACE; d2d1.setWhiteMove(true);

	Move d2c2; d2c2.source.colRow = 0x31; d2c2.dest.colRow = 0x21; d2c2.capture = SPACE; d2c2.setWhiteMove(true);
	Move d2b2; d2b2.source.colRow = 0x31; d2b2.dest.colRow = 0x11; d2b2.capture = SPACE; d2b2.setWhiteMove(true);
	Move d2a2; d2a2.source.colRow = 0x31; d2a2.dest.colRow = 0x01; d2a2.capture = SPACE; d2a2.setWhiteMove(true);

	Move d2e2; d2e2.source.colRow = 0x31; d2e2.dest.colRow = 0x41; d2e2.capture = SPACE; d2e2.setWhiteMove(true);
	Move d2f2; d2f2.source.colRow = 0x31; d2f2.dest.colRow = 0x51; d2f2.capture = SPACE; d2f2.setWhiteMove(true);
	Move d2g2; d2g2.source.colRow = 0x31; d2g2.dest.colRow = 0x61; d2g2.capture = SPACE; d2g2.setWhiteMove(true);
	Move d2h2; d2h2.source.colRow = 0x31; d2h2.dest.colRow = 0x71; d2h2.capture = SPACE; d2h2.setWhiteMove(true);

	// EXERCISE
	rook.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 14);
	assertUnit(moves.find(d2d8) != moves.end());
	assertUnit(moves.find(d2a2) != moves.end());
	assertUnit(moves.find(d2h2) != moves.end());

	// TEARDOWN
	board.board[3][1] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       p             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   p .(r). . . . p   2
 * 1       p             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToBlock()
{
	// SETUP
	BoardEmpty board;
	Rook rook(3, 1, true); // d2
	rook.fWhite = true;
	rook.position.colRow = 0x31;
	board.board[3][1] = &rook;

	Black black1(PAWN);

	White white1(PAWN);
	White white2(PAWN);
	White white3(PAWN);

	board.board[3][4] = &black1; // d5

	board.board[2][1] = &white1; // c2
	board.board[4][1] = &white2; // e2
	board.board[3][0] = &white3; // d1

	set <Move> moves;

	Move d2d3; d2d3.source.colRow = 0x31; d2d3.dest.colRow = 0x32; d2d3.capture = SPACE; d2d3.setWhiteMove(true);
	Move d2d4; d2d4.source.colRow = 0x31; d2d4.dest.colRow = 0x33; d2d4.capture = SPACE; d2d4.setWhiteMove(true);
	Move d2d5; d2d5.source.colRow = 0x31; d2d5.dest.colRow = 0x34; d2d5.capture = PAWN; d2d5.setWhiteMove(true);

	// EXERCISE
	rook.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 3);
	assertUnit(moves.find(d2d3) != moves.end());
	assertUnit(moves.find(d2d4) != moves.end());
	assertUnit(moves.find(d2d5) != moves.end());

	// TEARDOWN
	board.board[3][1] = nullptr;
	board.board[2][1] = nullptr;
	board.board[4][1] = nullptr;
	board.board[3][0] = nullptr;
	board.board[3][4] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8       P             8
 * 7       .             7
 * 6       .             6
 * 5       .             5
 * 4       .             4
 * 3       .             3
 * 2   P .(r). . . . P   2
 * 1       P             1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestRook::getMoves_slideToCapture()
{
	// SETUP
	BoardEmpty board;
	Rook rook(3, 1, true); // d2
	rook.fWhite = true;
	rook.position.colRow = 0x31;
	board.board[3][1] = &rook;

	Black black1(PAWN);
	board.board[3][2] = &black1; // d3

	White white1(PAWN);
	White white2(PAWN);
	White white3(PAWN);

	board.board[2][1] = &white1; // c2
	board.board[4][1] = &white2; // e2
	board.board[3][0] = &white3; // d1


	set<Move> moves;
	Move d2d3;
	d2d3.source.colRow = 0x31;
	d2d3.dest.colRow = 0x32;
	d2d3.capture = PAWN;
	d2d3.setWhiteMove(true);

	// EXERCISE
	rook.getMoves(moves, board);

	// VERIFY
	assertUnit(moves.size() == 1);
	assertUnit(moves.find(d2d3) != moves.end());

	// TEARDOWN
	board.board[3][1] = nullptr;
	board.board[4][1] = nullptr;
}



/*************************************
 * GET TYPE : rook
 * Input:
 * Output: ROOK
 **************************************/
void TestRook::getType()
{
	// SETUP
	const Rook rook(3, 1, true); // d2
	PieceType pt = SPACE;

	// EXERCISE
	pt = rook.getType();

	// VERIFY
	assertUnit(pt == ROOK);
}

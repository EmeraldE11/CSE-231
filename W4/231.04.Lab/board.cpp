/***********************************************************************
 * Source File:
 *    BOARD 
 * Author:
 *    Spencer Palmer
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include <cassert>
using namespace std;



/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   // free everything
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;
   
   // White Pieces
//   board[0][0] = new Rook(0, 0, true);
   board[1][0] = new Knight(1, 0, true);
//   board[2][0] = new Bishop(2, 0, true);
//   board[3][0] = new Queen(3, 0, true);
//   board[4][0] = new King(4, 0, true);
//   board[5][0] = new Bishop(5, 0, true);
   board[6][0] = new Knight(6, 0, true);
//   board[7][0] = new Rook(7, 0, true);

   // Black Pieces
//   board[0][7] = new Rook(0, 7, false);
   board[1][7] = new Knight(1, 7, false);
//   board[2][7] = new Bishop(2, 7, false);
//   board[3][7] = new Queen(3, 7, false);
//   board[4][7] = new King(4, 7, false);
//   board[5][7] = new Bishop(5, 7, false);
   board[6][7] = new Knight(6, 7, false);
//   board[7][7] = new Rook(7, 7, false);
   
}

// we really REALLY need to delete this.
//Space space(0,0);

/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
    assert(board[pos.getCol()][pos.getRow()]);
    return *(board[pos.getCol()][pos.getRow()]);
}
Piece& Board::operator [] (const Position& pos)
{
    assert(board[pos.getCol()][pos.getRow()]);
    return *(board[pos.getCol()][pos.getRow()]);
}

 /***********************************************
 * BOARD : DISPLAY
 *         Display the board
 ***********************************************/
void Board::display(const Position & posHover, const Position & posSelect) const
{
   
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   if (!noreset)
      reset(false);
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{

}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{

}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move & move)
{  

   // increment move counter
   numMoves++;
   
   Position src = move.getSrc();
   Position des = move.getDes();

   int srcCol = src.getCol();
   int srcRow = src.getRow();
   int dstCol = des.getCol();
   int dstRow = des.getRow();

   // create move pointer
   Piece* pMoving = board[srcCol][srcRow];

   // destination becomes moving piece
   board[dstCol][dstRow] = pMoving;

   // source becomes SPACE
   board[srcCol][srcRow] = new Space(srcCol, srcRow);
   
}



/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
   pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty() 
{
   delete pSpace;
}

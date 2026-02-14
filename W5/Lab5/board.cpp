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
#include "pieceType.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "pieceBishop.h"
#include "pieceRook.h"
#include "pieceKing.h"
#include "pieceQueen.h"
#include "piecePawn.h"
#include "move.h"
#include <cassert>
#include <set>
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
   if (fFree)
      free();
   
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = new Space(c, r);
   
   // Black Pieces
   board[0][0] = new Rook(0, 0, true);
   board[1][0] = new Knight(1, 0, true);
   board[2][0] = new Bishop(2, 0, true);
   board[3][0] = new Queen(3, 0, true);
   board[4][0] = new King(4, 0, true);
   board[5][0] = new Bishop(5, 0, true);
   board[6][0] = new Knight(6, 0, true);
   board[7][0] = new Rook(7, 0, true);
   for(int c = 0; c < 8; c++)
      board[c][1] = new Pawn(c, 1, true);

   // White Pieces
   board[0][7] = new Rook(0, 7, false);
   board[1][7] = new Knight(1, 7, false);
   board[2][7] = new Bishop(2, 7, false);
   board[3][7] = new Queen(3, 7, false);
   board[4][7] = new King(4, 7, false);
   board[5][7] = new Bishop(5, 7, false);
   board[6][7] = new Knight(6, 7, false);
   board[7][7] = new Rook(7, 7, false);
   for(int c = 0; c < 8; c++)
      board[c][6] = new Pawn(c, 6, false);
   
}

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
   
   assert(pgout != nullptr);

   // draw squares
   pgout->drawBoard();

   // when a piece is selected, show its possible moves (red squares) as in the spec
   if (posSelect.isValid())
   {
      const Piece& pieceSelected = (*this)[posSelect];
      if (pieceSelected.getType() != SPACE && pieceSelected.isWhite() == whiteTurn())
      {
         set<Move> possibleMoves;
         pieceSelected.getMoves(possibleMoves, *this);
         for (const Move& move : possibleMoves)
            pgout->drawPossible(move.getDes());
      }
      pgout->drawSelected(posSelect);
   }

   if (posHover.isValid())
       pgout->drawHover(posHover);

   for (int row = 0; row < 8; row++)
   {
       for (int col = 0; col < 8; col++)
       {
          Position pos(col, row);
          Piece* pPiece = board[col][row];

          if (pPiece != nullptr)
          {
             switch (pPiece->getType())
             {
                case KNIGHT: pgout->drawKnight(pos, pPiece->isWhite()); break;
                case KING: pgout->drawKing(pos, pPiece->isWhite()); break;
                case QUEEN: pgout->drawQueen(pos, pPiece->isWhite()); break;
                case BISHOP: pgout->drawBishop(pos, pPiece->isWhite()); break;
                case ROOK: pgout->drawRook(pos, pPiece->isWhite()); break;
                case PAWN: pgout->drawPawn(pos, pPiece->isWhite()); break;
                case SPACE:  break; // empty square, nothing to draw
                default: assert(false); // unknown type
             }
          }
       }
   }
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;
   
   if (!noreset)
      reset(false);
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
   for (int r = 0; r < 8; r++)
   {
      for (int c = 0; c < 8; c++)
      {
         if (board[c][r] != nullptr)
         {
            delete board[c][r];
            board[c][r] = nullptr;
         }
      }
   }
}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{
   for (int r = 0; r < 8; r++)
   {
      for (int c = 0; c < 8; c++)
      {
         // Every square must contain a valid Piece
         assert(board[c][r] != nullptr);
      }
   }
}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions.
 *         Handles simple moves, captures, castling, en passant, promotion.
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move & move)
{
   numMoves++;

   Position src = move.getSrc();
   Position des = move.getDes();
   int srcCol = src.getCol();
   int srcRow = src.getRow();
   int dstCol = des.getCol();
   int dstRow = des.getRow();
   Piece* pMoving = board[srcCol][srcRow];
   Move::MoveType moveType = move.getMoveType();

   // En passant: remove the captured pawn (the one that was passed over)
   if (moveType == Move::ENPASSANT)
   {
      int capCol = des.getCol();
      int capRow = src.getRow();
      if (board[capCol][capRow] != nullptr)
      {
         delete board[capCol][capRow];
         board[capCol][capRow] = new Space(capCol, capRow);
      }
   }

   // Capture or clear destination before placing moving piece
   if (board[dstCol][dstRow] != nullptr)
   {
      delete board[dstCol][dstRow];
      board[dstCol][dstRow] = nullptr;
   }

   // Move the piece
   board[dstCol][dstRow] = pMoving;
   pMoving->setPosition(des);
   pMoving->setLastMove(numMoves);
   board[srcCol][srcRow] = new Space(srcCol, srcRow);

   // Castling: move the rook
   if (moveType == Move::CASTLE_KING)
   {
      int rookSrcCol = 7, rookDstCol = 5;
      int row = srcRow;
      Piece* pRook = board[rookSrcCol][row];
      if (pRook != nullptr)
      {
         delete board[rookDstCol][row];
         board[rookDstCol][row] = pRook;
         pRook->setPosition(Position(rookDstCol, row));
         pRook->setLastMove(numMoves);
         board[rookSrcCol][row] = new Space(rookSrcCol, row);
      }
   }
   else if (moveType == Move::CASTLE_QUEEN)
   {
      int rookSrcCol = 0, rookDstCol = 3;
      int row = srcRow;
      Piece* pRook = board[rookSrcCol][row];
      if (pRook != nullptr)
      {
         delete board[rookDstCol][row];
         board[rookDstCol][row] = pRook;
         pRook->setPosition(Position(rookDstCol, row));
         pRook->setLastMove(numMoves);
         board[rookSrcCol][row] = new Space(rookSrcCol, row);
      }
   }

   // Pawn promotion: replace with Queen when reaching last rank (per spec)
   if (pMoving->getType() == PAWN && (dstRow == 0 || dstRow == 7))
   {
      bool white = pMoving->isWhite();
      delete pMoving;
      board[dstCol][dstRow] = new Queen(dstCol, dstRow, white);
      board[dstCol][dstRow]->setLastMove(numMoves);
   }
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

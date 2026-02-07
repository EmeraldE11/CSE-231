/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    <your name here>
 * Summary:
 *    The king class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "move.h"

/**********************************************
 * KING : GET MOVES
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
   if (!position.isValid())
      return;

   // One-square moves in any direction: non-capture and capture.
   Delta directions[8] = {
      {1, 1}, {1, 0}, {1, -1},
      {0, 1}, {0, -1},
      {-1, 1}, {-1, 0}, {-1, -1}
   };

   for (int i = 0; i < 8; i++)
   {
      Position dest(position, directions[i]);
      if (dest.isValid())
      {
         const Piece& destPiece = board[dest];
         if (destPiece.getType() == SPACE)
         {
            Move move;
            move.setSrc(position);
            move.setDes(dest);
            move.setCapture(SPACE);
            move.setWhiteMove(fWhite);
            moves.insert(move);
         }
         else if (destPiece.isWhite() != fWhite)
         {
            Move move;
            move.setSrc(position);
            move.setDes(dest);
            move.setCapture(destPiece.getType());
            move.setWhiteMove(fWhite);
            moves.insert(move);
         }
      }
   }

   // Castling: only if king has never moved.
   if (getNMoves() == 0)
   {
      if (fWhite)
      {
         // White king on e1: queen-side (a1 rook) and king-side (h1 rook).
         if (position.getRow() == 0 && position.getCol() == 4)
         {
            const Piece& rook1 = board[Position(0, 0)];
            if (rook1.getType() == ROOK && rook1.isWhite() && rook1.getNMoves() == 0)
            {
               if (board[Position(1, 0)].getType() == SPACE &&
                   board[Position(2, 0)].getType() == SPACE &&
                   board[Position(3, 0)].getType() == SPACE)
               {
                  Move move;
                  move.setSrc(position);
                  move.setDes(Position(2, 0));
                  move.setCapture(SPACE);
                  move.setWhiteMove(true);
                  move.setCastle(false);
                  moves.insert(move);
               }
            }
            const Piece& rook2 = board[Position(7, 0)];
            if (rook2.getType() == ROOK && rook2.isWhite() && rook2.getNMoves() == 0)
            {
               if (board[Position(5, 0)].getType() == SPACE &&
                   board[Position(6, 0)].getType() == SPACE)
               {
                  Move move;
                  move.setSrc(position);
                  move.setDes(Position(6, 0));
                  move.setCapture(SPACE);
                  move.setWhiteMove(true);
                  move.setCastle(true);
                  moves.insert(move);
               }
            }
         }
      }
      else
      {
         // Black king on e8: queen-side (a8 rook) and king-side (h8 rook).
         if (position.getRow() == 7 && position.getCol() == 4)
         {
            const Piece& rook1 = board[Position(0, 7)];
            if (rook1.getType() == ROOK && !rook1.isWhite() && rook1.getNMoves() == 0)
            {
               if (board[Position(1, 7)].getType() == SPACE &&
                   board[Position(2, 7)].getType() == SPACE &&
                   board[Position(3, 7)].getType() == SPACE)
               {
                  Move move;
                  move.setSrc(position);
                  move.setDes(Position(2, 7));
                  move.setCapture(SPACE);
                  move.setWhiteMove(false);
                  move.setCastle(false);
                  moves.insert(move);
               }
            }
            const Piece& rook2 = board[Position(7, 7)];
            if (rook2.getType() == ROOK && !rook2.isWhite() && rook2.getNMoves() == 0)
            {
               if (board[Position(5, 7)].getType() == SPACE &&
                   board[Position(6, 7)].getType() == SPACE)
               {
                  Move move;
                  move.setSrc(position);
                  move.setDes(Position(6, 7));
                  move.setCapture(SPACE);
                  move.setWhiteMove(false);
                  move.setCastle(true);
                  moves.insert(move);
               }
            }
         }
      }
   }
}

/***************************************************
 * KING : DISPLAY
 ***************************************************/
void King::display(ogstream* pgout) const
{
}


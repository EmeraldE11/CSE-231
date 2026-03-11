/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The pawn class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "move.h"

/**********************************************
 * PAWN : GET MOVES
 *********************************************/
void Pawn::getMoves(set <Move>& moves, const Board& board) const
{
   if (!position.isValid())
      return;

   int currentRow = position.getRow();
   int currentCol = position.getCol();
   int direction = fWhite ? 1 : -1;
   int startRow = fWhite ? 1 : 6;
   int promotionRow = fWhite ? 7 : 0;

   // Forward move: one square (and two from start). Non-capture; promote on last rank.
   Position forward(position, Delta(0, direction));
   if (forward.isValid())
   {
      const Piece& forwardPiece = board[forward];
      if (forwardPiece.getType() == SPACE)
      {
         Move move;
         move.setSrc(position);
         move.setDes(forward);
         move.setCapture(SPACE);
         move.setWhiteMove(fWhite);
         if (forward.getRow() == promotionRow)
         {
            move.setPromotion(QUEEN);
         }
         moves.insert(move);

         if (currentRow == startRow)
         {
            Position doubleForward(position, Delta(0, 2 * direction));
            if (doubleForward.isValid())
            {
               const Piece& doubleForwardPiece = board[doubleForward];
               if (doubleForwardPiece.getType() == SPACE)
               {
                  Move move2;
                  move2.setSrc(position);
                  move2.setDes(doubleForward);
                  move2.setCapture(SPACE);
                  move2.setWhiteMove(fWhite);
                  moves.insert(move2);
               }
            }
         }
      }
   }

   // Diagonal capture left; promote on last rank.
   Position captureLeft(position, Delta(-1, direction));
   if (captureLeft.isValid())
   {
      const Piece& captureLeftPiece = board[captureLeft];
      if (captureLeftPiece.getType() != SPACE && captureLeftPiece.isWhite() != fWhite)
      {
         Move move;
         move.setSrc(position);
         move.setDes(captureLeft);
         move.setCapture(captureLeftPiece.getType());
         move.setWhiteMove(fWhite);
         if (captureLeft.getRow() == promotionRow)
         {
            move.setPromotion(QUEEN);
         }
         moves.insert(move);
      }
   }

   // Diagonal capture right; promote on last rank.
   Position captureRight(position, Delta(1, direction));
   if (captureRight.isValid())
   {
      const Piece& captureRightPiece = board[captureRight];
      if (captureRightPiece.getType() != SPACE && captureRightPiece.isWhite() != fWhite)
      {
         Move move;
         move.setSrc(position);
         move.setDes(captureRight);
         move.setCapture(captureRightPiece.getType());
         move.setWhiteMove(fWhite);
         if (captureRight.getRow() == promotionRow)
         {
            move.setPromotion(QUEEN);
         }
         moves.insert(move);
      }
   }

   // En passant: pawn on 5th rank (white) or 4th (black); enemy pawn on adjacent file just moved two.
   int currentMove = board.getCurrentMove();
   if (currentRow == (fWhite ? 4 : 3))
   {
      Position leftPos(currentCol - 1, currentRow);
      if (leftPos.isValid())
      {
         const Piece& leftPiece = board[leftPos];
         if (leftPiece.getType() == PAWN && leftPiece.isWhite() != fWhite)
         {
            if (leftPiece.justMoved(currentMove))
            {
               Position enPassantDest(currentCol - 1, currentRow + direction);
               Move move;
               move.setSrc(position);
               move.setDes(enPassantDest);
               move.setCapture(PAWN);
               move.setWhiteMove(fWhite);
               move.setEnPassant();
               moves.insert(move);
            }
         }
      }

      Position rightPos(currentCol + 1, currentRow);
      if (rightPos.isValid())
      {
         const Piece& rightPiece = board[rightPos];
         if (rightPiece.getType() == PAWN && rightPiece.isWhite() != fWhite)
         {
            if (rightPiece.justMoved(currentMove))
            {
               Position enPassantDest(currentCol + 1, currentRow + direction);
               Move move;
               move.setSrc(position);
               move.setDes(enPassantDest);
               move.setCapture(PAWN);
               move.setWhiteMove(fWhite);
               move.setEnPassant();
               moves.insert(move);
            }
         }
      }
   }
}

/***************************************************
 * PAWN : DISPLAY
 ***************************************************/
void Pawn::display(ogstream* pgout) const
{
}


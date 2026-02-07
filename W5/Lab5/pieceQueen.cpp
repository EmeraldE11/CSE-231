/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    <your name here>
 * Summary:
 *    The queen class
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "move.h"

/**********************************************
 * QUEEN : GET MOVES
 *********************************************/
void Queen::getMoves(set <Move>& moves, const Board& board) const
{
   if (!position.isValid())
      return;

   Delta directions[8] = {
      {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}
   };

   for (int i = 0; i < 8; i++)
   {
      Position dest = position;
      dest += directions[i];
      
      while (dest.isValid())
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
            break;
         }
         else
         {
            break;
         }
         
         dest += directions[i];
      }
   }
}

/***************************************************
 * QUEEN : DISPLAY
 ***************************************************/
void Queen::display(ogstream* pgout) const
{
}


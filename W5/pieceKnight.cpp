/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The knight class
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include "position.h"
#include "move.h"

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Knight::display(ogstream* pgout) const
{

}


/**********************************************
 * KNIGHT : GET POSITIONS
 *********************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
{
   if (!position.isValid())
      return;

   Delta offsets[8] = {
      {-1,  2}, { 1,  2},
      {-2,  1}, { 2,  1},
      {-2, -1}, { 2, -1},
      {-1, -2}, { 1, -2}
   };

   for (int i = 0; i < 8; i++)
   {
      Position dest(position, offsets[i]);
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
}
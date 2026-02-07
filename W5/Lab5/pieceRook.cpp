/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    Noah McCarthy
 * Summary:
 *    The Rook class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include "position.h"
#include "move.h"

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Rook::display(ogstream* pgout) const
{

}


/**********************************************
 * BISHOP : GET POSITIONS
 *********************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
    if (!position.isValid())
        return;

    Delta directions[4] = {
       { 0, -1}, { 0,  1},
       { 1,  0}, {-1,  0},
    };

    for (int d = 0; d < 4; d++)
    {
        Position dest(position);
        while (true)
        {
            dest = Position(dest, directions[d]);
            if (!dest.isValid())
                break;
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
            else
            {
                if (destPiece.isWhite() != fWhite)
                {
                    Move move;
                    move.setSrc(position);
                    move.setDes(dest);
                    move.setCapture(destPiece.getType());
                    move.setWhiteMove(fWhite);
                    moves.insert(move);
                }
                break; // stop sliding after hitting a piece
            }
        }
    }
}
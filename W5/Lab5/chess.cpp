/**********************************************************************
* Source File:
*    Lab 04: Chess
* Author:
*    <your name here>
* Summary:
*    Play the game of chess
************************************************************************/


#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for OGSTREAM
#include "position.h"     // for POSITION
#include "piece.h"        // for PIECE and company
#include "pieceType.h"    // for SPACE
#include "board.h"        // for BOARD
#include "move.h"         // for Move
#include "test.h"
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
using namespace std;


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface *pUI, void * p)
{
   Board * pBoard = (Board *)p;

   Position posHover = pUI->getHoverPosition();
   Position posSelect = pUI->getSelectPosition();
   Position posSelectPrevious = pUI->getPreviousPosition();

   // If user clicked two different squares, try to execute a move (source = previous, dest = current)
   if (posSelect.isValid() && posSelectPrevious.isValid() && posSelect != posSelectPrevious)
   {
      const Piece& pieceSrc = (*pBoard)[posSelectPrevious];
      if (pieceSrc.getType() != SPACE && pieceSrc.isWhite() == pBoard->whiteTurn())
      {
         set<Move> moves;
         pieceSrc.getMoves(moves, *pBoard);
         for (const Move& move : moves)
         {
            if (move.getDes() == posSelect)
            {
               pBoard->move(move);
               pUI->clearSelectPosition();
               pUI->clearPreviousPosition();
               break;
            }
         }
      }
   }

   pBoard->display(posHover, posSelect);
}


/*********************************
 * MAIN - Where it all begins...
 *********************************/
#ifdef _WIN32
#include <windows.h>
#endif
int main(int argc, char** argv)
{

   // run all the unit tests
   testRunner();
   
   // Instantiate the graphics window
   Interface ui("Chess");

   // Initialize the game class
   ogstream* pgout = new ogstream;
   Board board(pgout);

   // Read and play moves from a file if one is given (e.g. Lab5 castle.txt)
   if (argc >= 2)
   {
      ifstream file(argv[1]);
      if (file.good())
      {
         string line;
         while (getline(file, line))
         {
            // Trim whitespace
            size_t start = line.find_first_not_of(" \t\r\n");
            if (start == string::npos) continue;
            size_t end = line.find_last_not_of(" \t\r\n");
            line = line.substr(start, end - start + 1);
            if (line.empty()) continue;

            Move m;
            m.read(line);
            if (m.getMoveType() != Move::MOVE_ERROR && m.getSrc().isValid() && m.getDes().isValid())
            {
               m.setWhiteMove(board.whiteTurn());
               board.move(m);
            }
         }
      }
   }

   // set everything into action
   ui.run(callBack, (void *)(&board));      
   
   // All done.
   delete pgout;
   return 0;
}

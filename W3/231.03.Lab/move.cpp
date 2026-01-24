/***********************************************************************
 * Source File:
 *    MOVE 
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move()
{
   source.setInvalid();
   dest.setInvalid();
   promote = SPACE;
   capture = SPACE;
   moveType = MOVE;
   isWhite = false;
   text = "";
}

/***************************************************
 * MOVE : CONSTRUCTOR FROM STRING
 ***************************************************/
Move::Move(const string & rhs)
{
   read(rhs);
}

/***************************************************
 * MOVE : EQUALITY OPERATOR
 ***************************************************/
bool Move::operator==(const Move & rhs) const
{
   return source == rhs.source &&
          dest == rhs.dest &&
          promote == rhs.promote &&
          capture == rhs.capture &&
          moveType == rhs.moveType &&
          isWhite == rhs.isWhite;
}

/***************************************************
 * MOVE : LESS THAN OPERATOR
 * Compare based on destination position
 ***************************************************/
bool Move::operator<(const Move & rhs) const
{
   return dest < rhs.dest;
}

/***************************************************
 * MOVE : READ
 * Parse a move from Smith notation string
 ***************************************************/
void Move::read(const string & rhs)
{
   // Initialize defaults
   promote = SPACE;
   capture = SPACE;
   moveType = MOVE;
   isWhite = false;
   text = rhs;

   if (rhs.length() < 4)
   {
      source.setInvalid();
      dest.setInvalid();
      moveType = MOVE_ERROR;
      return;
   }

   // Parse source position (first 2 characters: e.g., "e5")
   string srcStr = rhs.substr(0, 2);
   source = srcStr;

   // Parse destination position (next 2 characters: e.g., "e6")
   string destStr = rhs.substr(2, 2);
   dest = destStr;

   // Parse additional flags (characters 4 and beyond)
   for (size_t i = 4; i < rhs.length(); i++)
   {
      char c = rhs[i];
      switch (c)
      {
      case 'p':   // capture a pawn
      case 'n':   // capture a knight
      case 'b':   // capture a bishop
      case 'r':   // capture a rook
      case 'q':   // capture a queen
         capture = pieceTypeFromLetter(tolower(c));
         break;

      case 'c':  // short castling or king's castle
         moveType = CASTLE_KING;
         break;
      case 'C':  // long castling or queen's castle
         moveType = CASTLE_QUEEN;
         break;
      case 'E':  // En-passant
         moveType = ENPASSANT;
         capture = PAWN;
         break;

      case 'N':  // Promote to knight
      case 'B':  // Promote to Bishop
      case 'R':  // Promote to Rook
      case 'Q':  // Promote to Queen
         promote = pieceTypeFromLetter(tolower(c));
         break;
      }
   }

   // Error checking
   if (!source.isValid() || !dest.isValid())
   {
      moveType = MOVE_ERROR;
   }
}

/***************************************************
 * MOVE : ASSIGNMENT OPERATOR FROM STRING
 ***************************************************/
const Move & Move::operator=(const string & rhs)
{
   read(rhs);
   return *this;
}

/***************************************************
 * MOVE : GET TEXT
 * Convert move to Smith notation string
 ***************************************************/
string Move::getText() const
{
   if (!source.isValid() || !dest.isValid())
      return "";

   ostringstream oss;
   
   // Source position
   int srcCol = source.getCol();
   int srcRow = source.getRow();
   oss << (char)('a' + srcCol) << (char)('1' + srcRow);

   // Destination position
   int destCol = dest.getCol();
   int destRow = dest.getRow();
   oss << (char)('a' + destCol) << (char)('1' + destRow);

   // Handle special moves
   if (moveType == ENPASSANT)
   {
      // En passant uses 'E' instead of capture letter
      oss << 'E';
   }
   else if (moveType == CASTLE_KING)
   {
      oss << 'c';
   }
   else if (moveType == CASTLE_QUEEN)
   {
      oss << 'C';
   }
   else
   {
      // Regular move: output capture and promotion
      // Capture
      if (capture != SPACE)
      {
         oss << letterFromPieceType(capture);
      }

      // Promotion
      if (promote != SPACE)
      {
         oss << (char)toupper(letterFromPieceType(promote));
      }
   }

   return oss.str();
}

/***************************************************
 * MOVE : SET CASTLE
 ***************************************************/
void Move::setCastle(bool isKing)
{
   if (isKing)
      moveType = CASTLE_KING;
   else
      moveType = CASTLE_QUEEN;
}

/***************************************************
 * MOVE : LETTER FROM PIECE TYPE
 ***************************************************/
char Move::letterFromPieceType(PieceType pt) const
{
   switch (pt)
   {
   case SPACE:   return ' ';
   case PAWN:    return 'p';
   case BISHOP:  return 'b';
   case KNIGHT:  return 'n';
   case ROOK:    return 'r';
   case QUEEN:   return 'q';
   case KING:    return 'k';
   default:      return ' ';
   }
}

/***************************************************
 * MOVE : PIECE TYPE FROM LETTER
 ***************************************************/
PieceType Move::pieceTypeFromLetter(char letter) const
{
   switch (tolower(letter))
   {
   case 'p': return PAWN;
   case 'b': return BISHOP;
   case 'n': return KNIGHT;
   case 'r': return ROOK;
   case 'q': return QUEEN;
   case 'k': return KING;
   default:  return SPACE;
   }
}




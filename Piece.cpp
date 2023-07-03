/************************************************************************
* Source File:
*    Piece.h
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Everything each piece needs as a whole to be based off of.
************************************************************************/

#include "Piece.h"
#include "Board.h"
#include "Position.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include <iostream>

using namespace std;

#pragma once

/***************************************************************
 * GET MOVES NO SLIDE
 * Finds the movement options of pieces that do not slide,
 * such as pawn, king and knight.
 **************************************************************/
set <int> Piece::getMovesNoSlide(const Delta d[], Board board, int row, int col, int numMoves)
{
   // Setup set to hold all possible moves.
   set<int> possible;

   int r = position.getRow();      // the row we are checking
   int c = position.getColumn();   // the column we are checking

   Position posChecker(r, c);

   // Loops through different move options.
   for (int i = 0; i < numMoves; i++)
   {
      r = (fWhite) ? row + d[i].row : row - d[i].row;
      c = col + d[i].col;
      posChecker.set(r, c);

      if (posChecker.isValid(r, c))
      {
         // Make sure there is no pieces in the direction the king is moving.
         // If the location does not have a piece.
         if (&board[posChecker] == nullptr)
            possible.insert(r * 8 + c);

         // If the location has a piece of the enemy color, it can move there, assuming this piece is not a pawn.
         else if ((board[posChecker].isWhite() != fWhite) && (getLetter() != 'p'))
            possible.insert(r * 8 + c);
      }
   }
   return possible;
}

/***************************************************************
 * GET MOVES SLIDE
 * Finds the movement options of sliding pieces, such as
 * the rook, bishop, and queen.
 **************************************************************/
set <int> Piece::getMovesSlide(const Delta d[], Board board, int row, int col, int numMoves)
{
   // Setup set to hold all possible moves.
   set<int> possible;

   int r = position.getRow();      // the row we are checking
   int c = position.getColumn();   // the column we are checking

   Position posChecker(r, c);

   // Loops through different move options.
   for (int i = 0; i < numMoves; i++)
   {
      r = row + d[i].row;
      c = col + d[i].col;
      posChecker.set(r, c);

      // As long as there is nothing to stop it and it hasn't run off the board yet.
      while ((posChecker.isValid(r, c)) &&
         (&board[r * 8 + c] == nullptr))
      {
         possible.insert(r * 8 + c);
         r = r + d[i].row;
         c = c + d[i].col;
         posChecker.set(r, c);
      }

      // As long as it hasn't run off the board, see if you can take the piece.
      if (posChecker.isValid(r, c))
      {
         // Make sure there is no pieces in the direction the piece is moving.
         // If the location does not have a piece.
         if (&board[posChecker] == nullptr)
            possible.insert(r * 8 + c);

         // If the location has a piece of the enemy color, it can move there, 
         // assuming this piece is not a pawn.
         else if ((board[posChecker].isWhite() != fWhite) && (getLetter() != 'p'))
            possible.insert(r * 8 + c);
      }
   }
   return possible;
}

/***************************************************************
 * GET MOVES NO SLIDE
 * Finds the movement options of sliding pieces, such as
 * the rook, bishop, and queen.
 **************************************************************/

/***************************************************************
 * CHECK FOR PROMOTION
 * Sees if the pawn is ready to promote.
 **************************************************************/
bool Piece::checkForPromotion()
{
   // Make sure the piece is a pawn.
   if (getLetter() == 'p')
   {
      // If white and on the other side, promote.
      if ((fWhite) && (position.getRow() == 7))
      {
         return true;
      }

      // If black and on the other side, do likewise.
      else if ((!fWhite) && (position.getRow() == 0))
      {
         return true;
      }
   }
   return false;
}

/***************************************************************
 * DRAW functions
 * For each piece, have it call its draw function in uiDraw.
 **************************************************************/
void Pawn::draw()
{
   ogstream gout;

   gout.drawPawn(position.getLocation(), fWhite); 
}

void King::draw()
{
   ogstream gout;
   gout.drawKing(position.getLocation(), fWhite);
}

void Rook::draw()
{
   ogstream gout;
   gout.drawRook(position.getLocation(), fWhite);
}

void Queen::draw()
{
   ogstream gout;
   gout.drawQueen(position.getLocation(), fWhite);
}

void Bishop::draw()
{
   ogstream gout;
   gout.drawBishop(position.getLocation(), fWhite);
}

void Knight::draw()
{
   ogstream gout;
   gout.drawKnight(position.getLocation(), fWhite);
}

/***************************************************************
 * GET MOVES functions
 * For each piece, make a movement algorithm, send it to the
 * different move option (slide or no slide), then take care
 * of any special move rules.
 **************************************************************/
set<int> Pawn::getMoves(Board& board)
{
   // Set up list of possible moves.
   const Delta p[] =
   {
      {1, 0}
   };

   set<int> possible;

   int location = position.getLocation();

   // return the empty set if there simply are no possible moves
   if (location < 0 || location >= 64 || &board[position] == nullptr)
      return possible;

   int row = location / 8;  // current location row
   int col = location % 8;  // current location column

   possible = getMovesNoSlide(p, board, row, col, 1);

   int r = 1;                   // the row we are checking
   int c = 1;                   // the column we are checking

   Position posChecker(r, c);

   //
   // INITIAL MOVE
   //

   // Check two spaces forward from the current position for the double move as long as it has not moved.
   c = col;
   r = (fWhite) ? row + 2 : row - 2;
   posChecker.set(r, c);
   if ((row == 1 || row == 6) && &board[posChecker] == nullptr)
      possible.insert(r * 8 + c);

   //
   // CAPTURE
   //

   // Check diagonally to the left for enemies to take.
   c = col - 1;
   r = (fWhite) ? row + 1 : row - 1;
   posChecker.set(r, c);
   if (&board[posChecker] != nullptr && posChecker.isValid(r, c))
   {
      if (board[posChecker].isWhite() != fWhite)
         possible.insert(r * 8 + c);
   }

   // Check diagonally to the right for enemies to take.
   c = col + 1;
   r = (fWhite) ? row + 1 : row - 1;
   posChecker.set(r, c);
   if (&board[posChecker] != nullptr && posChecker.isValid(r, c))
   {
      if (board[posChecker].isWhite() != fWhite)
         possible.insert(r * 8 + c);
   }

   //
   // EN-PASSANT
   //
   if (position.getRow() == ((fWhite) ? 4 : 3))
   {
      // Check left side.
      c = col - 1;
      r = row;
      posChecker.set(r, c);

      if (&board[posChecker] != nullptr)
      {
         if (board[posChecker].getLetter() == 'p' && board[posChecker].getNMoves() == 1)
         {
            r = r + ((fWhite) ? 1 : -1);
            posChecker.set(r, c);
            possible.insert((int)posChecker.getLocation());
         }
      }

      // Check right side.
      c = col + 1;
      r = row;
      posChecker.set(r, c);
      if (&board[posChecker] != nullptr)
      {
         if (board[posChecker].getLetter() == 'p' && board[posChecker].getNMoves() == 1)
         {
            r = r + ((fWhite) ? 1 : -1);
            posChecker.set(r, c);
            possible.insert((int)posChecker.getLocation());
         }
      }
   }
   return possible;
}

set<int> King::getMoves(Board& board)
{
   // Set up list of possible moves.
   const Delta k[] =
   {
      {1 , -1}, { 1, 0}, { 1, 1},
      {0 , -1}, /* K */  { 0, 1},
      {-1, -1}, {-1, 0}, {-1, 1}
   };

   set <int> possible;

   int location = position.getLocation();

   // return the empty set if there simply are no possible moves
   if (location < 0 || location >= 64 || &board[position] == nullptr)
      return possible;

   int row = location / 8;  // current location row
   int col = location % 8;  // current location column

   possible = getMovesNoSlide(k, board, row, col, 8);

   int r = 1;                   // the row we are checking
   int c = 1;                   // the column we are checking

   Position posChecker(r, c);

   // Castling
   if (nMoves == 0)
   {
      // Get the king's position.
      int kingPos = (fWhite) ? 4 : 60;

      // Make sure there is a piece there.
      if (&board[kingPos - 4] != nullptr)
      {
         // Queen-Side Castle.
         // Make sure each position between it and the rook are empty and that the rook has not moved.
         if ((&board[kingPos - 1] == nullptr) && (&board[kingPos - 2] == nullptr) &&
         (&board[kingPos - 3] == nullptr) && (board[kingPos - 4].getLetter() == 'r') &&
         (board[kingPos - 4].getNMoves() == 0))
         {
            possible.insert(kingPos - 2);
         }
      }

      // Make sure there is a piece on the other side too before checking for castling.
      if (&board[kingPos + 3] != nullptr)
      {
         // King-Side Castle.
         if ((&board[kingPos + 1] == nullptr) && (&board[kingPos + 2] == nullptr) &&
         (board[kingPos + 3].getLetter() == 'r') && (board[kingPos + 3].getNMoves() == 0))
         {
            possible.insert(kingPos + 2);
         }
      }
   }
   return possible;
}

set<int> Rook::getMoves(Board& board)
{
   // Set up list of possible moves.
   const Delta r[] =
   {
                { 1, 0},
      {0 , -1}, /* r */  { 0, 1},
                {-1, 0}
   };

   set <int> possible;

   int location = position.getLocation();

   // return the empty set if there simply are no possible moves
   if (location < 0 || location >= 64 || &board[position] == nullptr)
      return possible;

   int row = location / 8;  // current location row
   int col = location % 8;  // current location column

   possible = getMovesSlide(r, board, row, col, 4);

   return possible;
}

set<int> Queen::getMoves(Board& board)
{
   // Set up list of possible moves.
   const Delta q[] =
   {
      {1 , -1}, { 1, 0}, { 1, 1},
      {0 , -1}, /* q */  { 0, 1},
      {-1, -1}, {-1, 0}, {-1, 1}
   };

   set <int> possible;

   int location = position.getLocation();

   // return the empty set if there simply are no possible moves
   if (location < 0 || location >= 64 || &board[position] == nullptr)
      return possible;

   int row = location / 8;  // current location row
   int col = location % 8;  // current location column

   possible = getMovesSlide(q, board, row, col, 8);

   return possible;
}

set<int> Bishop::getMoves(Board& board)
{
   // Set up list of possible moves.
   const Delta b[] =
   {
      {1 , -1},          { 1, 1},
                /* B */ 
      {-1, -1},          {-1, 1}
   };

   set <int> possible;

   int location = position.getLocation();

   // return the empty set if there simply are no possible moves
   if (location < 0 || location >= 64 || &board[position] == nullptr)
      return possible;

   int row = location / 8;  // current location row
   int col = location % 8;  // current location column

   possible = getMovesSlide(b, board, row, col, 4);

   return possible;
}

set<int> Knight::getMoves(Board& board)
{
   // Set up list of possible moves.
   const Delta n[] =
   {
                {2,  -1},          {2,  1},
      {1 , -2},                            {1 , 2},
                          /* N */
      {-1, -2},                            {-1, 2},
                {-2, -1},          {-2, 1}
   };

   set <int> possible;

   int location = position.getLocation();

   // return the empty set if there simply are no possible moves
   if (location < 0 || location >= 64 || &board[position] == nullptr)
      return possible;

   int row = location / 8;  // current location row
   int col = location % 8;  // current location column

   possible = getMovesNoSlide(n, board, row, col, 8); 

   return possible;
}

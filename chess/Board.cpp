/************************************************************************
* Source File:
*    Board.h
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Everything to do with the board and how it works.
************************************************************************/

#include "Board.h"
#include "Piece.h"
#include "Position.h"
#include "uiDraw.h"

/****************************************************
 * INITIALIZE
 * Move a piece from positionFrom to positionTo.
 ***************************************************/
Board::Board() : board()
{
   ogstream gout;
   this->pGout = &gout;

   // Set move counter.
   currentMove = 0;

   // Loop through each row.
   for (int row = 0; row < 8; row++)
   {

      // Loop through each column.
      for (int column = 0; column < 8; column++)
      {

         // If in the back-line of either side...
         if (row == 0 || row == 7)
         {
            bool fWhite = (row == 0) ? true : false;

            // If in the corners, make rooks.
            if (column == 0 || column == 7)
            {
               Rook* r = new Rook(row, column, fWhite);
               placePiece(r);
            }

            // If next to corners, make knights (not days).
            else if (column == 1 || column == 6)
            {
               Knight* n = new Knight(row, column, fWhite);
               placePiece(n);
            }

            // If next to middle, make bishops (not stake presidents).
            else if (column == 2 || column == 5)
            {
               Bishop* b = new Bishop(row, column, fWhite);
               placePiece(b);
            }

            // If in middle but queen-side, make a queen.
            else if (column == 3)
            {
               Queen* q = new Queen(row, column, fWhite);
               placePiece(q);
            }

            // Lastly, if on king-side, make a king.
            else if (column == 4)
            {
               King* k = new King(row, column, fWhite);
               placePiece(k);
            }
         }

         // For the front row of each side, place the pawns.
         else if (row == 1 || row == 6)
         {
            bool fWhite = (row == 1) ? true : false;
            Pawn* p = new Pawn(row, column, fWhite);
            placePiece(p);
         }

         // Otherwise, place nothing.
         else
         {
            this->board[row][column] == nullptr;
         }
      }
   }
}

/****************************************************
 * EXECUTE MOVE
 * Moves a piece to its new home, doing any
 * fancy move rules along the way.
 ***************************************************/
void Board::executeMove(int positionFrom, int positionTo)
{
   // Make variable names for ease of readability.
   int positionFromRow = positionFrom / 8;
   int positionFromCol = positionFrom % 8;
   int positionToRow = positionTo / 8;
   int positionToCol = positionTo % 8;

   Piece* pPiece = board[positionFromRow][positionFromCol];

   // Check pawn moving for en-passant purposes.
   if (pPiece->getLetter() == 'p')
   {
      // If the pawn is moving diagonally, aka in a new column,
      // and not to take a piece normally.
      if ((positionFromCol != positionToCol) && (board[positionToRow][positionToCol] == nullptr))
      {
         // Remove the pawn that is being taken.
         board[positionFromRow][positionToCol] = nullptr;
      }
   }

   // Relocate the piece.
   pPiece->getPosition().set(positionToRow, positionToCol);
   placePiece(pPiece);
   pPiece->increaseMoves();

   // If the moving piece is a king, see if it is castling.
   if (pPiece->getLetter() == 'k')
   {
      // If the king moved two spaces to the left.
      if (positionFrom - positionTo == 2)
      {
         executeMove(positionTo - 2, positionTo + 1);
      }

      // If the king moved two spaces to the right.
      else if (positionTo - positionFrom == 2)
      {
         executeMove(positionTo + 1, positionTo - 1);
      }
   }

   // Make sure the previous location is now empty.
   board[positionFromRow][positionFromCol] = nullptr;

   // Finally, push promotion if the conditions are right.
   if (board[positionToRow][positionToCol] != nullptr)
   {
      // If a pawn has just moved and has reached the backrow.
      if (board[positionToRow][positionToCol]->checkForPromotion())
      {
         // Make a queen, then replace the pawn with it.
         bool white = board[positionToRow][positionToCol]->isWhite();
         Queen* q = new Queen(positionTo / 8, positionTo % 8, white);
         replace(q, positionTo);
      }
   }
}

/****************************************************
 * DISPLAY
 * Display the board.
 ***************************************************/
void Board::display(const Interface& ui)
{
   for (int row = 0; row < 8; row++)
   {
      for (int column = 0; column < 8; column++)
      {
         if (board[row][column] != nullptr)
            board[row][column]->draw();
      }
   }
}

/***************************************************
 * [] OPERATORS
 * Get various piece pointers from the board.
 ***************************************************/
Piece& Board::operator[](Position& position)
{
   return *board[position.getRow()][position.getColumn()];
}

const Piece& Board::operator[](const Position& position) const
{
   return *board[position.getRow()][position.getColumn()];
}

Piece& Board::operator[](int position)
{
   int col = position % 8;
   int row = (position - col) / 8;
   return *board[row][col];
}

const Piece& Board::operator[](const int position) const
{
   int col = position % 8;
   int row = (position - col) / 8;
   return *board[row][col];
}

/***************************************************************
 * REPLACE
 * Remove a piece from the board and replace it with a new one.
 **************************************************************/
void Board::replace(Piece* piece, int pos)
{
   removePiece(pos);
   placePiece(piece);
}

/***************************************************************
 * PLACE PIECE
 * Using the position of a piece, put it on the board at
 * that location.
 **************************************************************/
void Board::placePiece(Piece* piece)
{
   int row = piece->getPosition().getRow();
   int col = piece->getPosition().getColumn();
   board[row][col] = piece;
}

/***************************************************************
 * REMOVE PIECE
 * Take a piece off the board and completely remove it
 * from memory.
 **************************************************************/
void Board::removePiece(int pos)
{
   board[pos / 8][pos % 8]->deleteSelf();
   board[pos / 8][pos % 8] == nullptr;
}

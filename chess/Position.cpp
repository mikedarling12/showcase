/************************************************************************
* Source File:
*    Position.h
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Everything to do with the position of the pieces.
************************************************************************/

#include "Position.h"

using namespace std;

/*************************************************************
 * IS VALID
 * Checks to make sure the row and columns are both in range, 
 * reventing wrapping or falling off the board.
 ************************************************************/
bool Position::isValid(int row, int col)
{
   if ((row >= 0) && (row < 8))
      if ((col >= 0) && (col < 8))
      {
         return true;
      }
   return false;
}

/*********************************************
 * SETTERS
 * Sets the row and column respectively.
 *********************************************/
void Position::setRow(int row)
{
   int col = location % 8;
   set(row, col);
}

void Position::setColumn(int col)
{
   int row = location / 8;
   set(row, col);
}

/*********************************************
 * ADJUSTERS
 * Adjusts the rows and columns respectively.
 *********************************************/
void Position::adjustRow(int dRow)
{
   int row = location / 8;
   int col = location % 8;
   if ((row + dRow <= 7) && (row + dRow >= 0))
      set(row + dRow, col);
}

void Position::adjustCol(int dCol)
{
   int row = location / 8;
   int col = location % 8;
   if ((col + dCol <= 7) && (col + dCol >= 0))
      set(row, col + dCol);
}

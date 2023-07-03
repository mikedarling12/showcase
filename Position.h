/************************************************************************
* Header File:
*    Position
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Everything to do with the position of the pieces.
************************************************************************/

#pragma once
#include <string>
#include <iostream>

using namespace std;

/**********************************************************
* POSITION
* This will take care of the position of all the pieces.
**********************************************************/
class Position
{
private:
   char location;
   double squareWidth = 10.0;
   double squareHeight = 10.0;
public:
   Position() : location(0) {}
   Position(const char * position) : location(*position) {}
   Position(int row, int col) { set(row, col); }
   char getLocation() const { return location; }
   int getRow() const { return location / 8; }
   int getColumn() const { return location % 8; }
   bool isValid(int row, int col);
   void setRow(int row);
   void setColumn(int col);
   void set(int row, int col) { location = row * 8 + col; }
   void adjustRow(int dRow);
   void adjustCol(int dCol);
   bool operator==(Position rhs) { return this->location == rhs.getLocation(); }
   void operator=(Position rhs) { this->location = rhs.getLocation(); }
};
/************************************************************************
* Header File:
*    Board
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Everything to do with the board and how it works.
************************************************************************/

using namespace std;
#include "uiInteract.h"
#pragma once

class ogstream;
class Position;
class Piece;
class TestPawn;

/**********************************************************
* BOARD
* Everything we need to deal with the board.

* +---a--b--c--d--e--f--g--h---+
* |                            |
* 8   56 57 58 59 60 61 62 63  8
* 7   48 49 50 51 52 53 54 55  7
* 6   40 41 42 43 44 45 46 47  6
* 5   32 33 34 35 36 37 38 39  5
* 4   24 25 26 27 28 29 30 31  4
* 3   16 17 18 19 20 21 22 23  3
* 2   8  9  10 11 12 13 14 15  2
* 1   0  1  2  3  4  5  6  7   1
* |                            |
* +---a--b--c--d--e--f--g--h---+

**********************************************************/
class Board
{
   friend TestPawn;
private:
   Piece* board[8][8];
   int currentMove;
   ogstream* pGout;

public:
   Board();
   void executeMove(int positionFrom, int positionTo);
   int getCurrentMove() { return currentMove; }
   void display(const Interface& ui);
   Piece& operator [](Position& position);
   const Piece& operator [](const Position& position) const;
   Piece& operator [](int position);
   const Piece& operator [](const int position) const;
   void replace(Piece* piece, int pos);
   void placePiece(Piece* piece);
   void removePiece(int pos);
};
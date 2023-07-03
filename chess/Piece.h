/************************************************************************
* Header File:
*    Piece
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Everything each piece needs as a whole to be based off of.
************************************************************************/

#pragma once

#include "Position.h"
#include <cassert>
#include <set>

class Interface;
class TestPawn;
class TestKing;
class Board;
class ogstream;
class Pawn;

/**********************************************************
* DELTA
* This will take our row and column when we are setting 
* up the moves for each piece.
**********************************************************/
struct Delta 
{
   int row;
   int col;
};


/**********************************************************
* PIECE
* Everything the piece needs to know about
**********************************************************/
class Piece
{
protected:
   Position position;
   bool fWhite;
   int nMoves;
   int lastMove;
   set <int> getMovesNoSlide(const Delta d[], Board board, int row, int col, int numMoves);
   set <int> getMovesSlide(const Delta d[], Board board, int row, int col, int numMoves);
public:
   Piece(int r, int c, bool white) : position(r, c), fWhite(white), nMoves(0), lastMove(0) {}
   bool isWhite() const { return fWhite; }
   bool isMove() const { return nMoves == 0; }
   int getNMoves() const { return nMoves; } 
   Position& getPosition() { return position; }
   void increaseMoves() { nMoves += 1; }
   bool justMoved(int currentMove) { return currentMove - 1 == lastMove; }
   void deleteSelf() { delete this; }
   bool checkForPromotion();
   virtual char getLetter() const { return ' '; }
   virtual void draw() = 0;
   virtual set <int> getMoves(Board& board) = 0;
};

/**********************************************************
* PAWN
* This will take care of the pawn piece.
**********************************************************/
class Pawn : public Piece
{
   friend TestPawn;
public:
   Pawn(int r, int c, bool white) : Piece(r, c, white) {}
   char getLetter() const { return 'p'; }
   void draw();
   set <int> getMoves(Board& board);
};

/**********************************************************
* KING
* This will take care of the king piece.
**********************************************************/
class King : public Piece
{
   friend TestKing;
public:
   King(int r, int c, bool white) : Piece(r, c, white) {}
   char getLetter() const { return 'k'; }
   void draw();
   set <int> getMoves(Board& board);
};

/**********************************************************
* Queen
* This will take care of the queen piece.
**********************************************************/
class Queen : public Piece
{
   friend TestKing;
public:
   Queen(int r, int c, bool white) : Piece(r, c, white) {}
   char getLetter() const { return 'q'; }
   void draw();
   set <int> getMoves(Board& board);
};

/***********************************************************
* ROOK
* This will take care of the rook piece.
**********************************************************/
class Rook : public Piece
{
   friend TestKing;
public:
   Rook(int r, int c, bool white) : Piece(r, c, white) {}
   char getLetter() const { return 'r'; }
   void draw();
   set <int> getMoves(Board& board);
};

/***********************************************************
* Bishop
* This will take care of the bishop piece.
**********************************************************/
class Bishop : public Piece
{
public:
   Bishop(int r, int c, bool white) : Piece(r, c, white) {}
   char getLetter() const { return 'b'; }
   void draw();
   set <int> getMoves(Board& board);
};

/***********************************************************
* Knight
* This will take care of the knight piece.
**********************************************************/
class Knight : public Piece
{
public:
   Knight(int r, int c, bool white) : Piece(r, c, white) {}
   char getLetter() const { return 'n'; }
   void draw();
   set <int> getMoves(Board& board);
};

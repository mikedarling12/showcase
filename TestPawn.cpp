/***********************************************************************
* Source File:
*    TestPawn
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Testing the pawn class with variety of test cases.
************************************************************************/

#pragma once

#include "TestPawn.h"
#include "Board.h"
#include "Piece.h"
#include "uiDraw.h"

using namespace std;

void TestPawn::run()
{
   // Moves
   test_blocked();
   test_simpleMove();
   test_initialMove();
   test_capture();
   test_enpassant();
   test_promotion();
}

/******************************
* BLOCKED TEST
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6                     6
* 5         P           5
* 4        (p)          4
* 3                     3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestPawn::test_blocked()
{
   // setup
   Board board;
   Pawn* p = new Pawn(3, 3, true); // d4
   Pawn* pBlock = new Pawn(4, 3, false); // d5
   board.placePiece(p);
   board.placePiece(pBlock);
   set<int> moves;

   // exercise.
   moves = p->getMoves(board);

   // verify.
   assert(moves.size() == 0);

   // teardown.
}

/******************************
* SIMPLE MOVE TEST
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6                     6
* 5                     5
* 4         .           4
* 3        (p)          3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestPawn::test_simpleMove()
{
   // setup.
   Board board;
   Pawn* p = new Pawn(2, 3, true); // d3
   board.placePiece(p);
   set<int> moves;

   // exercise.
   moves = p->getMoves(board);

   // verify.
   assert(moves.size() == 1);
   assert(moves.find(27) != moves.end());
}

///******************************
//* INITIAL MOVE
//* +---a-b-c-d-e-f-g-h---+
//* |                     |
//* 8                     8
//* 7                     7
//* 6                     6
//* 5                     5
//* 4         .           4
//* 3         .           3
//* 2        (p)          2
//* 1                     1
//* |                     |
//* +---a-b-c-d-e-f-g-h---+
//*******************************/
void TestPawn::test_initialMove()
{
   // setup.
   Board board;
   Pawn* p = new Pawn(1, 3, true); // d2
   board.placePiece(p);
   set <int> moves;

   // exercise.
   moves = p->getMoves(board);

   // verify.
   assert(moves.size() == 2);
   assert(moves.find(19) != moves.end());
   assert(moves.find(27) != moves.end());

   // teardown.
}

/******************************
* CAPTURE TEST
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7   P P P             7
* 6    (p)              6
* 5                     5
* 4                     4
* 3                     3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestPawn::test_capture()
{
   // setup.
   Board board;
   Pawn* p = new Pawn(5, 1, true); // b6
   Pawn* pBlock1 = new Pawn(6, 0, false); // a7
   Pawn* pBlock2 = new Pawn(6, 1, false); // b7
   Pawn* pBlock3 = new Pawn(6, 2, false); // c7
   board.placePiece(p);
   board.placePiece(pBlock1);
   board.placePiece(pBlock2);
   board.placePiece(pBlock3);
   set<int> moves;

   // exercise.
   moves = p->getMoves(board);

   // verify.
   assert(moves.size() == 2);
   assert(moves.find(48) != moves.end());
   assert(moves.find(50) != moves.end());

   // teardown.
}

/******************************
* TEST ENPASSANT
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6   . P .             6
* 5   P(p)P             5
* 4                     4
* 3                     3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestPawn::test_enpassant()
{
   // setup.
   Board board;
   Pawn* p = new Pawn(5, 1, true); // b5
   Pawn* pLeft = new Pawn(5, 0, false); // a5
   Pawn* pRight = new Pawn(5, 2, false); // c5
   Pawn* pBlock = new Pawn(6, 1, false); // b6
   board.placePiece(p);
   board.placePiece(pLeft);
   board.placePiece(pRight);
   board.placePiece(pBlock);
   pLeft->nMoves = 1;
   pRight->nMoves = 1;
   // board.enpassant = true;
   set <int> moves;

   // exercise.
   moves = p->getMoves(board);

   // verify.
   assert(moves.size() == 2);
   assert(moves.find(40) != moves.end());
   assert(moves.find(42) != moves.end());

   // teardown.
}

/******************************
* TEST PROMOTION
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8    (p)              8
* 7                     7
* 6                     6
* 5                     5
* 4                     4
* 3                     3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestPawn::test_promotion()
{
   // setup.
   Board board;
   Pawn* p = new Pawn(7, 1, true); // b8
   Position testPosition(p->getPosition());
   board.placePiece(p);

   // exercise.
   bool promote = p->checkForPromotion();

   // cout << board[testPosition].getLetter() << endl;

   // verify.
   assert(promote == true);

   // teardown.
}
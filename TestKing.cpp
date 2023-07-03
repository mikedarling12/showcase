/***********************************************************************
* Source File:
*    TestKing.h
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Testing the king class with variety of test cases.
************************************************************************/

#include "TestKing.h"
#include "Piece.h"
#include "Board.h"
#include "uiDraw.h"

void TestKing::run()
{
   // Moves
   test_free();
   test_edgeCase();
   test_blocked();
   test_capture();
   test_CastleKingMoved();
   test_CastleRookMoved();
   test_castleBlocked();
   test_castle();
}

/*******************************
* FREE TEST
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6         . . .       6
* 5         .(k).       5
* 4         . . .       4
* 3                     3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestKing::test_free()
{
   // setup.
   Board board;
   King* k = new King(4, 4, true);       // e5
   board.placePiece(k);
   set<int> moves;

   //exercise.
   moves = k->getMoves(board);

   // verify.
   assert(moves.size() == 8);
   assert(moves.find(43) != moves.end());
   assert(moves.find(44) != moves.end());
   assert(moves.find(45) != moves.end());
   assert(moves.find(35) != moves.end());
   assert(moves.find(37) != moves.end());
   assert(moves.find(27) != moves.end());
   assert(moves.find(28) != moves.end());
   assert(moves.find(29) != moves.end());

   // teardown.
}

/*************************************
* EDGE CASE TEST - Cannot leave board.
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6   . .               6
* 5  (k).               5
* 4   . .               4
* 3                     3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
**************************************/
void TestKing::test_edgeCase()
{
   // setup.
   Board board;
   King* k = new King(4, 0, true);       // e5
   board.placePiece(k);
   set<int> moves;

   //exercise.
   moves = k->getMoves(board);

   // verify.
   assert(moves.size() == 5);
   assert(moves.find(40) != moves.end());
   assert(moves.find(41) != moves.end());
   assert(moves.find(33) != moves.end());
   assert(moves.find(25) != moves.end());
   assert(moves.find(24) != moves.end());

   // teardown.
}


/******************************
* BLOCKED TEST
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6         p p p       6
* 5         p(k)p       5
* 4         p p p       4
* 3                     3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestKing::test_blocked()
{
   // setup.
   Board board;
   King* k = new King(4, 4, true);  // e5
   Pawn* p1 = new Pawn(5, 3, true); // d6
   Pawn* p2 = new Pawn(5, 4, true); // e6
   Pawn* p3 = new Pawn(5, 5, true); // f6
   Pawn* p4 = new Pawn(4, 3, true); // d5
   Pawn* p5 = new Pawn(4, 5, true); // f5
   Pawn* p6 = new Pawn(3, 3, true); // d4
   Pawn* p7 = new Pawn(3, 4, true); // e4
   Pawn* p8 = new Pawn(3, 5, true); // f4
   board.placePiece(k);
   board.placePiece(p1);
   board.placePiece(p2);
   board.placePiece(p3);
   board.placePiece(p4);
   board.placePiece(p5);
   board.placePiece(p6);
   board.placePiece(p7);
   board.placePiece(p8);
   set<int> moves;

   //exercise.
   moves = k->getMoves(board);

   // verify.
   assert(moves.size() == 0);

   // teardown.
}


/******************************
* CAPTURE TEST
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6         P P P       6
* 5         P(k)P       5
* 4         P P P       4
* 3                     3
* 2                     2
* 1                     1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestKing::test_capture()
{
   // setup.
   Board board;
   King* k = new King(4, 4, true);   // e5
   Pawn* p1 = new Pawn(5, 3, false); // d6
   Pawn* p2 = new Pawn(5, 4, false); // e6
   Pawn* p3 = new Pawn(5, 5, false); // f6
   Pawn* p4 = new Pawn(4, 3, false); // d5
   Pawn* p5 = new Pawn(4, 5, false); // f5
   Pawn* p6 = new Pawn(3, 3, false); // d4
   Pawn* p7 = new Pawn(3, 4, false); // e4
   Pawn* p8 = new Pawn(3, 5, false); // f4
   board.placePiece(k);
   board.placePiece(p1);
   board.placePiece(p2);
   board.placePiece(p3);
   board.placePiece(p4);
   board.placePiece(p5);
   board.placePiece(p6);
   board.placePiece(p7);
   board.placePiece(p8);

   set<int> moves;

   //exercise.
   moves = k->getMoves(board);

   // verify.
   assert(moves.size() == 8);
   assert(moves.find(43) != moves.end());
   assert(moves.find(44) != moves.end());
   assert(moves.find(45) != moves.end());
   assert(moves.find(35) != moves.end());
   assert(moves.find(37) != moves.end());
   assert(moves.find(27) != moves.end());
   assert(moves.find(28) != moves.end());
   assert(moves.find(29) != moves.end());

   // teardown.
}


/******************************
* CASTLE KING MOVED - Cannot castle.
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6                     6
* 5                     5
* 4                     4
* 3                     3
* 3                     3
* 2         p p p       2
* 1   r     .(k).   r   1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestKing::test_CastleKingMoved()
{
   // setup.
   Board board;
   King* k = new King(0, 4, true);  // e1
   k->nMoves = 1;
   board.placePiece(k);

   Pawn* p1 = new Pawn(1, 3, true); // d2
   Pawn* p2 = new Pawn(1, 4, true); // e2
   Pawn* p3 = new Pawn(1, 5, true); // f2
   board.placePiece(p1);
   board.placePiece(p2);
   board.placePiece(p3);

   Rook* rLeft = new Rook(1, 1, true);  // a1
   Rook* rRight = new Rook(1, 8, true); // h1
   board.placePiece(rLeft);
   board.placePiece(rRight);

   set<int> moves;

   //exercise.
   moves = k->getMoves(board);
 
   // verify.
   assert(moves.size() == 2);
   assert(moves.find(3) != moves.end());
   assert(moves.find(5) != moves.end());
   // teardown.
}


/************************************
* CASTLE ROOK MOVED - Cannot castle.
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6                     6
* 5                     5
* 4                     4
* 3                     3
* 2         p p p       2
* 1   r     .(k).   r   1
* |                     |
* +---a-b-c-d-e-f-g-h---+
***********************************/
void TestKing::test_CastleRookMoved()
{
   // setup.
   Board board;
   King* k = new King(0, 4, true);  // e1
   board.placePiece(k);

   Pawn* p1 = new Pawn(1, 3, true); // d2
   Pawn* p2 = new Pawn(1, 4, true); // e2
   Pawn* p3 = new Pawn(1, 5, true); // f2
   board.placePiece(p1);
   board.placePiece(p2);
   board.placePiece(p3);

   Rook* rLeft = new Rook(0, 0, true);  // a1
   rLeft->nMoves = 1;
   Rook* rRight = new Rook(0, 7, true); // h1
   rRight->nMoves = 1;
   board.placePiece(rLeft);
   board.placePiece(rRight);

   set<int> moves;

   //exercise.
   moves = k->getMoves(board);

   // verify.
   assert(moves.size() == 2);
   assert(moves.find(3) != moves.end());
   assert(moves.find(5) != moves.end());
   // teardown.
}


/*************************************
* CASTLE BLOCKED TEST - Cannot castle.
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6                     6
* 5                     5
* 4                     4
* 3                     3
* 2         p p p       2
* 1   r p   .(k). p r   1
* |                     |
* +---a-b-c-d-e-f-g-h---+
**************************************/
void TestKing::test_castleBlocked()
{
   // setup.
   Board board;
   King* k = new King(0, 4, true);  // e1
   k->nMoves = 1;
   board.placePiece(k);

   // Front pawns.
   Pawn* p1 = new Pawn(1, 3, true); // d2
   Pawn* p2 = new Pawn(1, 4, true); // e2
   Pawn* p3 = new Pawn(1, 5, true); // f2
   board.placePiece(p1);
   board.placePiece(p2);
   board.placePiece(p3);

   // Side blocking pawns.
   Pawn* pBlockLeft = new Pawn(0, 2, true); // b1
   Pawn* pBlockRight = new Pawn(0, 6, true); // g1
   board.placePiece(pBlockLeft);
   board.placePiece(pBlockRight);

   // Rooks.
   Rook* rLeft = new Rook(0, 0, true);  // a1
   Rook* rRight = new Rook(0, 7, true); // h1
   board.placePiece(rLeft);
   board.placePiece(rRight);

   set<int> moves;

   //exercise.
   moves = k->getMoves(board);
 
   // verify.
   assert(moves.size() == 2);
   assert(moves.find(3) != moves.end());
   assert(moves.find(5) != moves.end());
   // teardown.
}


/******************************
* CASTLE TEST - Can castle.
* +---a-b-c-d-e-f-g-h---+
* |                     |
* 8                     8
* 7                     7
* 6                     6
* 5                     5
* 4                     4
* 3                     3
* 2         p p p       2
* 1   r   . .(k). . r   1
* |                     |
* +---a-b-c-d-e-f-g-h---+
*******************************/
void TestKing::test_castle()
{
   // setup.
   Board board;
   King* k = new King(0, 4, true);  // e1
   board.placePiece(k);

   Pawn* p1 = new Pawn(1, 3, true); // d2
   Pawn* p2 = new Pawn(1, 4, true); // e2
   Pawn* p3 = new Pawn(1, 5, true); // f2
   board.placePiece(p1);
   board.placePiece(p2);
   board.placePiece(p3);

   Rook* rLeft = new Rook(0, 0, true);  // a1
   Rook* rRight = new Rook(0, 7, true); // h1
   board.placePiece(rLeft);
   board.placePiece(rRight);

   set<int> moves;

   //exercise.
   moves = k->getMoves(board);

   //cout << moves.size() << endl;
   //for (auto move : moves)
   //   cout << move << endl;

   // verify.
   assert(moves.size() == 4);
   assert(moves.find(2) != moves.end());
   assert(moves.find(3) != moves.end());
   assert(moves.find(5) != moves.end());
   assert(moves.find(6) != moves.end());
   // teardown.
}
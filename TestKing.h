/************************************************************************
* Header File:
*    TestKing
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Testing the King class with variety of test cases.
************************************************************************/

#pragma once
#include <iostream>
#include <cassert>
#include <set>

using namespace std;

class Board;
class Piece;
class King;
class uiInteract;
class uiDraw;

class TestKing
{
public:
   void run();

private:
   void test_free();
   void test_edgeCase();
   void test_blocked();
   void test_capture();
   void test_CastleKingMoved();
   void test_CastleRookMoved();
   void test_castleBlocked();
   void test_castle();
};
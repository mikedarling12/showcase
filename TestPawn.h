/***********************************************************************
* Header File:
*    TestPawn
* Author:
*    Andrew Olson, Michael Darling.
* Summary:
*    Testing the pawn class with variety of test cases.
************************************************************************/

#pragma once
#include <iostream>
#include <cassert>
#include <set>

using namespace std;

class Board;
class Piece;
class Pawn;
class uiInteract;
class uiDraw;

class TestPawn
{
public:
   void run();

private:
   void test_blocked();
   void test_simpleMove();
   void test_initialMove();
   void test_capture();
   void test_enpassant();
   void test_promotion();
};
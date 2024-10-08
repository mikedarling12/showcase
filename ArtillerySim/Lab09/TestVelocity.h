/***********************************************************************
 * Source File:
 *    TestVelocity
 * Author:
 *    Andrew Olson, Michael Darling.
 * Summary:
 *    Testing the velocity clss with variety of test cases.
 ************************************************************************/

#pragma once

#include <iostream>
#include <cassert>
#include <cmath>
#include "Velocity.h"

using namespace std;

class TestVelocity
{
public:
   void run()
   {
      // Getters.
      test_getDX();
      test_getDY();
      test_getSpeed_small();
      test_getSpeed_neg();
      test_getSpeed_mid();
      test_getSpeed_extreme();
      test_getDirection_small();
      test_getDirection_negative();
      test_getDirection_mid();
      test_getDirection_extreme();

      // Setters.
      test_setDX();
      test_setDY();
      test_setDxDy_dx();
      test_setDxDy_dy();
      test_setDirection_dxSmall();
      test_setDirection_dySmall();
      test_setDirection_dxMid();
      test_setDirection_dyMid();
      test_setDirection_dxExtreme();
      test_setDirection_dyExtreme();
      test_setSpeed_dxSmall();
      test_setSpeed_dySmall();
      test_setSpeed_dxMid();
      test_setSpeed_dyMid();
      test_setSpeed_dxExtreme();
      test_setSpeed_dyExtreme();

      // Adders.
      test_addDx_pos();
      test_addDx_neg();
      test_addDy_pos();
      test_addDy_neg();
      test_addV_dxPos();
      test_addV_dyPos();
      test_addV_dxNeg();
      test_addV_dyNeg();
      test_reverse_dx();
      test_reverse_dy();

    cout << "'Velocity tests' passed!" << endl;
   }

private:

   /*******************
   * GET TESTS
   *******************/
   void test_getDX()
   {
      // setup.
      Velocity v;
      v.dx = 1.0;
      v.dy = 1.0;
      // exercise.
      double dx = v.getDX();
      // verify.
      assert(dx == 1.0);
      assert(v.dx == 1.0);
      //teardown.
   }
   void test_getDY()
   {
      // setup.
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // exercise.
      double dy = v.getDY();
      // verify.
      assert(dy == 0.0);
      assert(v.dy == 0.0);
      //teardown.
   }
   void test_getSpeed_small()
   {
      // setup.
      Velocity v;
      v.dx = 1.0;
      v.dy = 1.0;
      // exercise.
      double speed = v.getSpeed();
      // verify.
      assert(1.4142 <= speed <= 1.4143);
      //teardown.
   }
   void test_getSpeed_neg()
   {
      // setup.
      Velocity v;
      v.dx = 1.0;
      v.dy = -1.0;
      // exercise.
      double speed = v.getSpeed();
      // verify.
      assert(1.4142 <= speed <= 1.4143);
      //teardown.
   }
   void test_getSpeed_mid()
   {
      // setup.
      Velocity v;
      v.dx = 300.0;
      v.dy = 300.0;
      // exercise.
      double speed = v.getSpeed();
      // verify.
      assert(424.2640 <= speed <= 424.2641);
      //teardown.
   }
   void test_getSpeed_extreme()
   {
      // setup.
      Velocity v;
      v.dx = 500.0;
      v.dy = 500.0;
      // exercise.
      double speed = v.getSpeed();
      // verify.
      assert(707.1067 <= speed <= 707.1068);
      //teardown.
   }
   void test_getDirection_small()
   {
      // setup.
      Velocity v;
      v.dx = 1.0;
      v.dy = 1.0;
      // exercise.
      Direction angle = v.getDirection();
      double degrees = angle.getDegrees();
      // verify.
      assert(44.99999999 < degrees < 45.000000);
      //teardown.
   }
   void test_getDirection_negative()
   {
      // setup.
      Velocity v;
      v.dx = -1.0;
      v.dy = -1.0;
      // exercise.
      Direction angle = v.getDirection();
      double degrees = angle.getDegrees();
      // verify.
      assert(degrees == -45);
      //teardown.
   }
   void test_getDirection_mid()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 300.0;
      // exercise.
      Direction angle = v.getDirection();
      double degrees = angle.getDegrees();
      // verify.
      assert(degrees == 18.4349);
      //teardown.
   }
   void test_getDirection_extreme()
   {
      // setup.
      Velocity v;
      v.dx = 300.0;
      v.dy = 500.0;
      // exercise.
      Direction angle = v.getDirection();
      double degrees = angle.getDegrees();
      // verify.
      assert(degrees == 30.9638);
      //teardown.
   }

   /*******************
   * SET TESTS
   *******************/
   void test_setDX()
   {
      // setup.
      Velocity v;
      v.dx = 400.0;
      v.dy = 400.0;
      // exercise.
      v.setDX(300.0);
      // verify.
      assert(v.dx == 300.0);
      assert(v.dy == 400.0);
      //teardown.
   }
   void test_setDY()
   {
      // setup.
      Velocity v;
      v.dx = 400.0;
      v.dy = 400.0;
      // exercise.
      v.setDY(300.0);
      // verify.
      assert(v.dx == 400.0);
      assert(v.dy == 300.0);
      //teardown.
   }
   void test_setDxDy_dx()
   {
      // setup.
      Velocity v;
      v.dx = 400.0;
      v.dy = 400.0;
      // exercise.
      v.setDxDy(300.0, 300);
      // verify.
      assert(v.dx == 300.0);
      //teardown.
   }
   void test_setDxDy_dy()
   {
      // setup.
      Velocity v;
      v.dx = 400.0;
      v.dy = 400.0;
      // exercise.
      v.setDxDy(300.0, 300);
      // verify.
      assert(v.dy == 300.0);
      //teardown.
   }
   void test_setDirection_dxSmall()
   {
      // setup.
      Velocity v;
      v.dx = 50.0;
      v.dy = 100.0;
      // exercise.
      v.setDirection(45);
      // verify.
      assert(79.0569 <= v.dx <= 79.0570);
      //teardown.
   }
   void test_setDirection_dySmall()
   {
      // setup.
      Velocity v;
      v.dx = 50.0;
      v.dy = 100.0;
      // exercise.
      v.setDirection(45);
      // verify.
      assert(79.0569 <= v.dy <= 79.0570);
      //teardown.
   }
   void test_setDirection_dxMid()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 100.0;
      // exercise.
      v.setDirection(30);
      // verify.
      assert(70.7107 <= v.dx <= 70.7108);
      //teardown.
   }
   void test_setDirection_dyMid()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 100.0;
      // exercise.
      v.setDirection(30);
      // verify.
      assert(122.4745 <= v.dy <= 122.4746);
      //teardown.
   }
   void test_setDirection_dxExtreme()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 100.0;
      // exercise.
      v.setDirection(60);
      // verify.
      assert(122.4745 <= v.dx <= 122.4746);
      //teardown.
   }
   void test_setDirection_dyExtreme()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 100.0;
      // exercise.
      v.setDirection(60);
      // verify.
      assert(70.7107 <= v.dy <= 70.7108);
      //teardown.
   }
   void test_setSpeed_dxSmall()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 100.0;
      // exercise.
      v.setSpeed(50);
      // verify.
      assert(35.3553 <= v.dx <= 35.3554);
      //teardown.
   }
   void test_setSpeed_dySmall()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 100.0;
      // exercise.
      v.setSpeed(50);
      // verify.
      assert(35.3553 <= v.dy <= 35.3554);
      //teardown.
   }
   void test_setSpeed_dxMid()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 200.0;
      // exercise.
      v.setSpeed(150);
      // verify.
      assert(129.9038 <= v.dx <= 129.9039);
      //teardown.
   }
   void test_setSpeed_dyMid()
   {
      // setup.
      Velocity v;
      v.dx = 100.0;
      v.dy = 200.0;
      // exercise.
      v.setSpeed(150);
      // verify.
      assert(74.99999 <= v.dy < 75.0);
      //teardown.
   }
   void test_setSpeed_dxExtreme()
   {
      // setup.
      Velocity v;
      v.dx = 200.0;
      v.dy = 100.0;
      // exercise.
      v.setSpeed(400);
      // verify.
      assert(199.99999 <= v.dx < 200.0);
      //teardown.
   }
   void test_setSpeed_dyExtreme()
   {
      // setup.
      Velocity v;
      v.dx = 200.0;
      v.dy = 100.0;
      // exercise.
      v.setSpeed(400);
      // verify.
      assert(346.4101 <= v.dy < 346.4102);
      //teardown.
   }

   /*******************
   * ADD TESTS
   *******************/
   void test_addDx_pos()
   {
      // setup.
      Velocity v;
      v.dx = 10.0;
      v.dy = 10.0;
      // exercise.
      v.addDX(10);
      // verify.
      assert(v.dx == 20.0);
      assert(v.dy == 10.0);
      //teardown.
   }
   void test_addDy_pos()
   {
      // setup.
      Velocity v;
      v.dx = 10.0;
      v.dy = 10.0;
      // exercise.
      v.addDY(10.0);
      // verify.
      assert(v.dx == 10.0);
      assert(v.dy == 20.0);
      //teardown.
   }
   void test_addDx_neg()
   {
      // setup.
      Velocity v;
      v.dx = 20.0;
      v.dy = 20.0;
      // exercise.
      v.addDX(-10.0);
      // verify.
      assert(v.dx == 10.0);
      assert(v.dy == 20.0);
      //teardown.
   }
   void test_addDy_neg()
   {
      // setup.
      Velocity v;
      v.dx = 20.0;
      v.dy = 20.0;
      // exercise.
      v.addDY(-10.0);
      // verify.
      assert(v.dx == 20.0);
      assert(v.dy == 10.0);
      //teardown.
   }
   void test_addV_dxPos()
   {
      // setup.
      Velocity v;
      v.dx = 10.0;
      v.dy = 0.0;
      Velocity newV;
      newV.dx = 10.0;
      newV.dy = 10.0;
      // exercise.
      v.addV(newV);
      // verify.
      assert(v.dx == 20.0);
      //teardown.
   }
   void test_addV_dyPos()
   {
      // setup.
      Velocity v;
      v.dx = 10.0;
      v.dy = 0.0;
      Velocity newV;
      newV.dx = 10.0;
      newV.dy = 10.0;
      // exercise.
      v.addV(newV);
      // verify.
      assert(v.dy == 10.0);
      //teardown.
   }
   void test_addV_dxNeg()
   {
      // setup.
      Velocity v;
      v.dx = 300.0;
      v.dy = 250.0;
      Velocity newV;
      // angle = 30
      newV.dx = -20.0;
      newV.dy = -20.0;
      // exercise.
      v.addV(newV);
      // verify.
      assert(v.dx == 280);
      //teardown.
   }
   void test_addV_dyNeg()
   {
      // setup.
      Velocity v;
      v.dx = 300.0;
      v.dy = 250.0;
      Velocity newV;
      newV.dx = -20.0;
      newV.dy = -20.0;
      // exercise.
      v.addV(newV);
      // verify.
      assert(v.dy == 230.0);
      //teardown.
   }
   void test_reverse_dx()
   {
      // setup.
      Velocity v;
      v.dx = 250.0;
      v.dy = 300.0;
      // exercise.
      v.reverse();
      // verify.
      assert(v.dx == -250);
      //teardown.
   }
   void test_reverse_dy()
   {
      // setup.
      Velocity v;
      v.dx = 250.0;
      v.dy = 300.0;
      // exercise.
      v.reverse();
      // verify.
      assert(v.dy == -300);
      //teardown.
   }
};
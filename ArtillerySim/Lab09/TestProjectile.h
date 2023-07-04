/***********************************************************************
 * Source File:
 *    TestProjectile
 * Author:
 *    Andrew Olson, Michael Darling.
 * Summary:
 *    Testing the projectile clss with variety of test cases..
 ************************************************************************/

#pragma once

#include "Projectile.h"
#include <cassert>
#include <cmath>

using namespace std;

class TestProjectile
{
public:
   void run()
   {
      // Getters
      test_getAltitude();
      test_getPositionX();
      test_getPositionY();
      test_getFlightTime();
      test_getFlightDistance();
      test_getSpeed();
      test_getFlying();
      // Setters
      test_setMass();
      test_setRadius();
      test_setFlying();
      // Look up gravity
      test_lookUpGravity_small();
      test_lookUpGravity_quarter();
      test_lookUpGravity_half();
      test_lookUpGravity_large();
      // Look up mach
      test_lookUpMach_small();
      test_lookUpMach_quarter();
      test_lookUpMach_half();
      test_lookUpMach_large();
      // Look up density
      test_lookUpDensity_small();
      test_lookUpDensity_quarter();
      test_lookUpDensity_half();
      test_lookUpDensity_large();
      // Look up drag co
      test_lookUpDragCo_small();
      test_lookUpDragCo_quarter();
      test_lookUpDragCo_half();
      test_lookUpDragCo_large();
      // More mathing
      test_linearInterpolation();
      test_dragForceEquation_small();
      test_dragForceEquation_quarter();
      test_dragForceEquation_half();
      test_dragForceEquation_large();

       cout << "'Projectile tests' passed!" << endl;
   }

private:
   /*******************
   * GET TESTS
   *******************/
   void test_getAltitude()
   {
      // setup.
      Projectile p;
      p.pos.y = 0.0;
      // exercise.
      int altitude = p.getAltitude();
      // verify.
      assert(altitude == 0.0);
      //teardown.
   }
   void test_getPositionX()
   {
      // setup.
      Projectile p;
      p.pos.x = 1.0;
      p.pos.y = 0.0;
      // exercise.
      Position pos = p.getPosition();
      // verify.
      assert(pos.x == 1.0);
      //teardown.
   }
   void test_getPositionY()
   {
      // setup.
      Projectile p;
      p.pos.x = 1.0;
      p.pos.y = 0.0;
      // exercise.
      Position pos = p.getPosition();
      // verify.
      assert(pos.y == 0.0);
      //teardown.
   }
   void test_getFlightTime()
   {
      // setup.
      Projectile p;
      p.flightTime = 10.0;
      // exercise.
      double flightTime = p.getFlightTime();
      // verify.
      assert(flightTime == 10.0);
      //teardown.
   }
   void test_getFlightDistance()
   {
      // setup.
      Projectile p;
      p.flightDistance = 100.0;
      // exercise.
      double flightDistance = p.getFlightDistance();
      // verify.
      assert(flightDistance == 100.0);
      //teardown.
   }
   void test_getSpeed()
   {
      // setup.
      Projectile p;
      p.v.dx = 300.0;
      p.v.dy = 300.0;
      // exercise. 
      double speed = p.getSpeed();
      // verify. 
      assert(424.2640 <= speed <= 424.2641);
      //teardown. 
   }
   void test_getFlying()
   {
      // setup.
      Projectile p;
      p.isFlying = false;
      // exercise. 
      bool isFlying = p.getFlying();
      // verify. 
      assert(isFlying == false);
      //teardown. 
   }

   /*******************
   * SET TESTS
   *******************/
   void test_setMass()
   {
      // setup. 
      Projectile p;
      p.mass = 10.0;
      // exercise. 
      p.setMass(46.7);
      // verify. 
      assert(p.mass == 46.7);
      //teardown. 
   }
   void test_setRadius()
   {
      // setup. 
      Projectile p;
      p.radius = 20.0;
      // exercise. 
      p.setRadius(0.077445);
      // verify. 
      assert(p.radius == 0.077445);
      //teardown. 
   }
   void test_setFlying()
   {
      // setup.
      Projectile p;
      p.isFlying = true;
      // exercise. 
      p.setFlying(false);
      // verify. 
      assert(p.isFlying == false);
      //teardown. 
   }

   /*******************
   * LOOKUP TESTS
   *******************/
   void test_lookUpGravity_small()
   {
      // setup. 
      Projectile p;
      p.pos.y = 1000;
      // exercise. 
      double gravity = p.lookUpGravity();
      // verify. 
      assert(gravity == 9.804);
      //teardown. 
   }
   void test_lookUpGravity_quarter()
   {
      // setup. 
      Projectile p;
      p.pos.y = 1250;
      // exercise. 
      double gravity = p.lookUpGravity();
      // verify. 
      assert(gravity == 9.80325);
      //teardown. 
   }
   void test_lookUpGravity_half()
   {
      // setup. 
      Projectile p;
      p.pos.y = 1500;
      // exercise. 
      double gravity = p.lookUpGravity();
      // verify. 
      assert(gravity == 9.8025);
      //teardown. 
   }
   void test_lookUpGravity_large()
   {
      // setup. 
      Projectile p;
      p.pos.y = 2000;
      // exercise. 
      double gravity = p.lookUpGravity();
      // verify. 
      assert(gravity == 9.801);
      //teardown. 
   }
   void test_lookUpMach_small()
   {
      // setup. 
      Projectile p;
      p.v.dx = 300;
      p.v.dy = 300;
      p.pos.y = 1000;
      // exercise. 
      double mach = p.lookUpMach();
      // verify. 
      assert(1.2676 <= mach <= 1.2627);
      //teardown. 
   }
   void test_lookUpMach_quarter()
   {
      // setup.
      Projectile p;
      p.v.dx = 300;
      p.v.dy = 300;
      p.pos.y = 1250;
      // exercise. 
      double mach = p.lookUpMach();
      // verify. 
      assert(1.2676 <= mach <= 1.2627);
      //teardown. 
   }
   void test_lookUpMach_half()
   {
      // setup. 
      Projectile p;
      p.v.dx = 300;
      p.v.dy = 300;
      p.pos.y = 1500;
      // exercise. 
      double mach = p.lookUpMach();
      // verify. 
      assert(1.2702 <= mach <= 1.2703);
      //teardown. 
   }
   void test_lookUpMach_large()
   {
      // setup. 
      Projectile p;
      p.v.dx = 300;
      p.v.dy = 300;
      p.pos.y = 2000;
      // exercise. 
      double mach = p.lookUpMach();
      // verify. 
      assert(1.2779 <= mach <= 1.278);
      //teardown. 
   }
   void test_lookUpDensity_small()
   {
      // setup. 
      Projectile p;
      p.pos.y = 1000;
      // exercise. 
      double density = p.lookUpDensity();
      // verify. 
      assert(density == 1.112);
      //teardown. 
   }
   void test_lookUpDensity_quarter()
   {
      // setup. 
      Projectile p;
      p.pos.y = 1250;
      // exercise. 
      double density = p.lookUpDensity();
      // verify. 
      assert(density == 1.08575);
      //teardown. 
   }
   void test_lookUpDensity_half()
   {
      // setup. 
      Projectile p;
      p.pos.y = 1500;
      // exercise. 
      double density = p.lookUpDensity();
      // verify. 
      assert(1.0595 <= density <= 1.0596);
      //teardown. 
   }
   void test_lookUpDensity_large()
   {
      // setup. 
      Projectile p;
      p.pos.y = 2000;
      // exercise. 
      double density = p.lookUpDensity();
      // verify. 
      assert(density == 1.007);
      //teardown. 
   }
   void test_lookUpDragCo_small()
   {
      // setup. 
      Projectile p;
      // exercise. 
      double dragCo = p.lookUpDragCo(.5);
      // verify. 
      assert(dragCo == 0.1659);
      //teardown. 
   }
   void test_lookUpDragCo_quarter()
   {
      // setup. 
      Projectile p;
      // exercise. 
      double dragCo = p.lookUpDragCo(.55);
      // verify. 
      assert(dragCo == 0.1752);
      //teardown. 
   }
   void test_lookUpDragCo_half()
   {
      // setup. 
      Projectile p;
      // exercise. 
      double dragCo = p.lookUpDragCo(.6);
      // verify. 
      assert(dragCo == 0.1845);
      //teardown. 
   }
   void test_lookUpDragCo_large()
   {
      // setup. 
      Projectile p;
      // exercise. 
      double dragCo = p.lookUpDragCo(.7);
      // verify. 
      assert(dragCo == 0.2031);
      //teardown. 
   }
   /*******************
   * MORE MATHING
   *******************/
   void test_linearInterpolation()
   {
      // setup.
      Projectile p;
      const lookupTable testTable[] =
      {
         {1000.0, 10.0},
         {2000.0, 20.0}
      };
      // exercise.
      double linerI = p.linearInterpolation(testTable, 2, 1500);
      // verify.
      assert(linerI == 15);
      //teardown.
   }
   void test_dragForceEquation_small()
   {
      // setup.
      Projectile p;
      p.pos.y = 1000;
      p.v.dx = 200;
      p.v.dy = 200;
      // exercise.
      double dragForce = p.dragForceEquation(p.lookUpDragCo(p.lookUpMach()), p.lookUpDensity());
      // verify.
      assert(200.9340 <= dragForce <= 200.9341);
      //teardown.
   }
   void test_dragForceEquation_quarter()
   {
      // setup.
      Projectile p;
      p.pos.y = 1250;
      p.v.dx = 200;
      p.v.dy = 200;
      // exercise.
      double dragForce = p.dragForceEquation(p.lookUpDragCo(p.lookUpMach()), p.lookUpDensity());
      // verify.
      assert(196.722 <= dragForce <= 196.7221);
      //teardown.
   }
   void test_dragForceEquation_half()
   {
      // setup.
      Projectile p;
      p.pos.y = 1500;
      p.v.dx = 200;
      p.v.dy = 200;
      // exercise.
      double dragForce = p.dragForceEquation(p.lookUpDragCo(p.lookUpMach()), p.lookUpDensity());
      // verify.
      assert(192.488 <= dragForce <= 192.4881);
      //teardown.
   }
   void test_dragForceEquation_large()
   {
      // setup.
      Projectile p;
      p.pos.y = 2000;
      p.v.dx = 200;
      p.v.dy = 200;
      // exercise.
      double dragForce = p.dragForceEquation(p.lookUpDragCo(p.lookUpMach()), p.lookUpDensity());
      // verify.
      assert(183.95 <= dragForce <= 183.951);
      //teardown.
   }
};
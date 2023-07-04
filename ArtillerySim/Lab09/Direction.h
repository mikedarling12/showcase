/***********************************************************************
 * Source File:
 *    Direction : Things to do with angles.
 * Author:
 *    Andrew Olson, Michael Darling.
 * Summary:
 *    Everything we need to know about an angle.
 ************************************************************************/

#pragma once

#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.14159

class Direction
{
private:
   double radians = 0.0;

public:
   // Constructors.
   Direction() {};
   Direction(double rhs) { radians = rhs; };

   // Setters.
   void setRadians(double rhs_radians) { radians = rhs_radians; }
   void setDegrees(double rhs_degrees) { radians = rhs_degrees * PI / 180; }
   void setDown() { setDegrees(180.0); }
   void setUp() { setDegrees(0.0); }
   void setRight() { setDegrees(90.0); }
   void setLeft() { setDegrees(270.0); }
   void reverse() { radians = -radians; }
   void setAngleFromComponents(double dx, double dy) { radians = atan(dx / dy); }

   // Getters.
   double getRadians() { return radians; }
   double getDegrees() { return radians * 180 / PI; }
};
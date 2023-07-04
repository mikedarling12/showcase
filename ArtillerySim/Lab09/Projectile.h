/***********************************************************************
 * Source File:
 *    Projectile : The things to do with the shell.
 * Author:
 *    Andrew Olson, Michael Darling.
 * Summary:
 *    The projectile or shell, which includes 
 *    how it flies and wher it is located.
 ************************************************************************/

#pragma once

#include <iostream>
#include "Position.h"
#include "Direction.h"
#include "Velocity.h"
#include <list>
#include "uiDraw.h"

#define PI                          3.14159   // Pi
#define MASS                           46.7   // Mass in KG
#define DIAMETER                    0.15489   // Diameter in M
#define RADIUS                 DIAMETER / 2   // Radius in M
#define SURFACEAREA  PI * (RADIUS * RADIUS)   // Surface area in M^2

using namespace std;

struct lookupTable
{
   double key;
   double value;
};

class TestProjectile;

class Projectile
{
   friend TestProjectile;
private:
   double mass = MASS;
   double radius = RADIUS;
   Velocity v;
   Position pos;
   Direction dir;
   double flightTime = 0.0;
   double flightDistance = 0.0;
   bool isFlying = false;

public:
   // Constructor
   Projectile() {};
   Projectile(Velocity v, Position pos, Direction dir) : v(v), pos(pos), dir(dir) {};
   
   // Other
   void reset();
   void advance(double time);
   void draw(list<Position> projectilePath);

   // Getters.
   double getAltitude() { return pos.getMetersY(); }
   Position getPosition() { return pos; }
   double getFlightTime() { return flightTime; }
   double getFlightDistance() { return flightDistance; }
   double getSpeed() { return v.getSpeed(); }
   double getFlying() { return isFlying; }
   Direction getDirection() { return dir; }

   // Setters.
   void setMass(double mass) { this->mass = mass; }
   void setRadius(double radius) { this->radius = radius; }
   void setPosition(Position pos) { this->pos = pos; }
   void setDirection(Direction dir) { this->dir = dir; }
   void setVelocity(double v) { this->v = Velocity(v, dir.getRadians()); }
   void setFlying(bool newFlyingStatus) { isFlying = newFlyingStatus; }

   // Lookups
   double lookUpGravity();
   double lookUpMach();
   double lookUpDragCo(double mach);
   double lookUpDensity();

   //Math
   void updatePosition(double acceleration, double gravity, double time);
   double linearInterpolation(const lookupTable lookup[], int numLookupTable, double domain);
   double dragForceEquation(double dragCo, double density);
};
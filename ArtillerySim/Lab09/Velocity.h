/***********************************************************************
 * Source File:
 *    Velocity : Things to do with speed.
 * Author:
 *    Andrew Olson, Michael Darling.
 * Summary:
 *    Everything we need to know about speed.
 ************************************************************************/

#pragma once

#include <iostream>
#include <cmath>
#include "Direction.h"

using namespace std;

class TestVelocity;
class TestProjectile;

class Velocity
{
    friend TestVelocity;
    friend TestProjectile;
private:
    double dx = 0.0;
    double dy = 0.0;

public:

    // Constructors.
    Velocity() : dx(0.0), dy(0.0) {};
    Velocity(double speed, double angle) 
    {
       dx = computeHorizontalComponent(angle, speed);
       dy = computeVerticalComponent(angle, speed);
    }

    // Getters.
    double getDX() { return dx; }
    double getDY() { return dy; }
    double getSpeed();        // Total component
    Direction getDirection(); // angleFromComponents

    // Setters.
    void setDX(double dx) { this->dx = dx; }
    void setDY(double dy) { this->dy = dy; }
    void setDxDy(double dx, double dy)
    {
        this->dx = dx;
        this->dy = dy;
    }
    void setDirection(Direction direction);
    void setSpeed(double speed);

    // Modifiers.
    void addDX(double dx) { this->dx += dx; }
    void addDY(double dy) { this->dy += dy; }
    void addV(Velocity velocity)
    {
        dx += velocity.getDX();
        dy += velocity.getDY();
    }
    void addAccelerationToVelocity(double ddx, double ddy, double time)
    {
       dx += ddx * time;
       dy += ddy * time;
    }
    void reverse()
    {
        dx = -dx;
        dy = -dy;
    }
    double getAcceleration(double force, double mass) { return force / mass; }
    double computeHorizontalComponent(double angle, double speed);
    double computeVerticalComponent(double angle, double speed);
};
/***********************************************************************
 * Source File:
 *    Velocity.h : The things to do with the speed.
 * Author:
 *    Andrew Olson, Michael Darling.
 * Summary:
 *    Everything we need to know about speed.
 ************************************************************************/

#include "Velocity.h"

/**********************************************
* GET SPEED
* Gets the total component of dx and dy.
**********************************************/
double Velocity::getSpeed()
{
    return sqrt((dx * dx) + (dy * dy));
}

/**********************************************
* GET DIRECTION
* Gets the angle in radians based on dx and dy.
**********************************************/
Direction Velocity::getDirection()
{
    return atan(dx / dy);
}

/**************************************************
* SET DIRECTION
* Sets the direction in radians based on dx and dy
**************************************************/
void Velocity::setDirection(Direction direction)
{
    double currentSpeed = getSpeed();
    dx = computeHorizontalComponent(direction.getRadians(), currentSpeed);
    dy = computeVerticalComponent(direction.getRadians(), currentSpeed);
}

/******************************************************
* SET SPEED
* Sets the total component of speed, then sets dx and 
* dy based on horizontal and verticle components.
******************************************************/
void Velocity::setSpeed(double speed)
{
    double currentAngle = getDirection().getRadians();
    dx = computeHorizontalComponent(currentAngle, speed);
    dy = computeVerticalComponent(currentAngle, speed);
}

/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the vertical component of the total
***********************************************/
double Velocity::computeHorizontalComponent(double angle, double speed)
{
    return sin(angle) * speed;
}

/***********************************************
* COMPUTE VERTICAL COMPONENT
* Find the vertical component of a velocity or acceleration.
* The equation is:
*     cos(a) = y / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     y : the vertical component of the total
***********************************************/
double Velocity::computeVerticalComponent(double angle, double speed)
{
    return cos(angle) * speed;
}
/***********************************************************************
 * Source File:
 *    Howitzer.h : The things to do with the gun.
 * Author:
 *    Andrew Olson, Michael Darling.
 * Summary:
 *    The gun or artilary piece, which includes
 *    where it is locted and the way it is angled/pointed.
 ************************************************************************/

#include "Howitzer.h"

 /**********************************************
 * RAISE
 * Moves the Howiter by smaller incriments.
 **********************************************/
void Howitzer::raise(double radians)
{
   if (elevation.getRadians() >= 0)
      rotate(-radians);
   else
      rotate(radians);
}

/**********************************************
* DRAW
* Moves the Howiter by smaller incriments.
**********************************************/
void Howitzer::draw(double simTime)
{
   ogstream gout;

   gout.drawHowitzer(position, elevation.getRadians(), flightTime);

   flightTime += simTime;
}

/***********************************************************************
 * Source File:
 *    Projectile.h : The things to do with the shell.
 * Author:
 *    Andrew Olson, Michael Darling.
 * Summary:
 *    The projectile or shell, which includes 
 *    how it flies and wher it is located as well as lookup tables.
 ************************************************************************/

#include "Projectile.h"

 /***************************************************
 * RESET
 * Resets the values for the projectile so that it
 * is ready to be used again.
 ***************************************************/
void Projectile::reset()
{
   pos.setMetersX(0.0);
   pos.setMetersY(0.0);
   v.setDX(0.0);
   v.setDY(0.0);
   flightTime = 0.0;
   flightDistance = 0.0;
   isFlying = false;
}

/***************************************************
* ADVANCE
* Takes care of all the physics for the shell,
* and allows it to move.
***************************************************/
void Projectile::advance(double time)
{
   double dragCo = lookUpDragCo(lookUpMach());
   double density = lookUpDensity();
   double dragForce = dragForceEquation(dragCo, density);
   double acceleration = v.getAcceleration(dragForce, mass);
   double gravity = lookUpGravity();
   dir.setAngleFromComponents(v.getDX(), v.getDY());
   updatePosition(acceleration, gravity, time);
   flightTime += time;
}

/**********************************************
* DRAW
* Draws the projectile on the screen.
**********************************************/
void Projectile::draw(list<Position> projectilePath)
{
   ogstream gout;

   int itr = 0;
   for (Position pos : projectilePath)
      gout.drawProjectile(pos, 0.5 * (double)itr++);
}

/***************************************************
* LOOK UP GRAVITY
* Gets the gravity bassed on the altitude, does
* liner interpolation for the valies between.
***************************************************/
double Projectile::lookUpGravity()
{
   const lookupTable gravityMap[] =
   {  // altitude , gravity
      {  0.0,       9.807},
      {  1000.0,    9.804},
      {  2000.0,    9.801},
      {  3000.0,    9.797},
      {  4000.0,    9.794},
      {  5000.0,    9.791},
      {  6000.0,    9.788},
      {  7000.0,    9.785},
      {  8000.0,    9.782},
      {  9000.0,    9.779},
      {  10000.0,   9.776},
      {  15000.0,   9.761},
      {  20000.0,   9.745},
      {  25000.0,   9.730}
   };

   double altitude = pos.getMetersY();

   return linearInterpolation(gravityMap, sizeof(gravityMap) / 
      sizeof(gravityMap[0]), altitude);
}

/***************************************************
* LOOK UP MACH
* Gets the mach bassed on the altitude, does 
* liner interpolation for the valies between.
***************************************************/
double Projectile::lookUpMach()
{
   const lookupTable machMap[] =
   {  // altitude , speed of sound
      {  0,         340          },
      {  1000,      336          },
      {  2000,      332          },
      {  3000,      328          },
      {  4000,      324          },
      {  5000,      320          },
      {  6000,      316          },
      {  7000,      312          },
      {  8000,      308          },
      {  9000,      303          },
      {  10000,     299          },
      {  15000,     295          },
      {  20000,     295          },
      {  25000,     295          },
      {  30000,     305          },
      {  40000,     324          }
   };

   double altitude = pos.getMetersY();

   double speed_of_sound = linearInterpolation(machMap, sizeof(machMap) /
      sizeof(machMap[0]), altitude);

   return v.getSpeed() / speed_of_sound;
}

/***************************************************
* LOOK UP DRAG CO
* Gets the drag co bassed on the mach, does 
* liner interpolation for the valies between.
***************************************************/
double Projectile::lookUpDragCo(double mach)
{
   const lookupTable dragCoMap[] =
   {  // mach , Drag Co
      {  0.3,   0.1629 },
      {  0.5,   0.1659 },
      {  0.7,   0.2031 },
      {  0.919, 0.2597 },
      {  0.959, 0.3010 },
      {  0.979, 0.3287 },
      {  0.98,  0.4002 },
      {  1.0,   0.4258 },
      {  1.02,  0.4335 },
      {  1.06,  0.4483 },
      {  1.24,  0.4064 },
      {  1.53,  0.3663 },
      {  1.99,  0.2897 },
      {  2.87,  0.2297 },
      {  2.89,  0.2306 },
      {  5,     0.2656 }
   };

   return linearInterpolation(dragCoMap, sizeof(dragCoMap) /
      sizeof(dragCoMap[0]), mach);
}

/***************************************************
* LOOK UP DENSITY
* Gets the density bassed on the altitude, does 
* liner interpolation for the valies between.
***************************************************/
double Projectile::lookUpDensity()
{
   const lookupTable densityMap[] =
   {  // altitude , gravity
      {   0,        1.225     },
      {  1000,      1.112     },
      {  2000,      1.007     },
      {  3000,      0.9093    },
      {  4000,      0.8194    },
      {  5000,      0.7364    },
      {  6000,      0.6601    },
      {  7000,      0.59      },
      {  8000,      0.5258    },
      {  9000,      0.4671    },
      {  10000,     0.4135    },
      {  15000,     0.1948    },
      {  20000,     0.08891   },
      {  25000,     0.04008   },
      {  30000,     0.01841   },
      {  40000,     0.003996  },
      {  50000,     0.001027  },
      {  60000,     0.0003097 },
      {  70000,     0.0000828 },
      {  80000,     0.0000185 }
   };

   double altitude = pos.getMetersY();

   return linearInterpolation(densityMap, sizeof(densityMap) /
      sizeof(densityMap[0]), altitude);
}

/***************************************************
* UPDATE POSITION
* Split acceleration into ddx and ddy, then update
* the position of the projectile.
***************************************************/
void Projectile::updatePosition(double acceleration, 
                 double gravity, double time)
{
   double ddx = v.computeHorizontalComponent(dir.getRadians(), 
                                             acceleration);
   double ddy = v.computeVerticalComponent(dir.getRadians(), 
                                    acceleration) - gravity;
   double beforeMovingX = pos.getMetersX();
   pos.setMetersX(pos.getMetersX() + v.getDX() * time +
                            (0.5 * ddx * (time * time)));
   pos.setMetersY(pos.getMetersY() + v.getDY() * time + 
                            (0.5 * ddy * (time * time)));

   // Update how far the projectile has traveled.
   if (beforeMovingX > pos.getMetersX())
      flightDistance += beforeMovingX - pos.getMetersX();
   else
      flightDistance += pos.getMetersX() - beforeMovingX;

   v.addAccelerationToVelocity(ddx, ddy, time);
}

/***************************
* LINEAR INTERPOLATION
* d0,r0 = coordinates of one point
* d1,r1 = coordinates of a second point
* d,r = coordinates of a point in the middle
*
* Solve for r.
*
* (r - r0)     (r1 - r0)
* --------  =  ---------
* (d - d0)     (d1 - d0)
****************************/
double Projectile::linearInterpolation(const lookupTable lookup[], 
                                       int numLookupTable, double key)
{
   // If the key is lower than the lowest key, return the lowest key.
   if (key <= lookup[0].key)
      return lookup[0].value;

   // Otherwise, see if the key is between two keys.
   for (int i = 0; i < numLookupTable - 1; i++)
   {
      // If it is, then return the linear interpolation of the two keys.
      if (lookup[i + 0].key <= key && key <= lookup[i + 1].key)

         // ((r1 - r0) * (d - d0)) / (d1 - d0) + r0
         return ((lookup[i + 1].value - lookup[i].value) * (key - lookup[i].key))
         / (lookup[i + 1].key - lookup[i].key) + lookup[i].value;
   }

   return lookup[numLookupTable - 1].value;
}

/***************************************************
* DRAG FORCE EQUATION
* Computes the drag force bassed on the altitude.
***************************************************/
double Projectile::dragForceEquation(double dragCo, double density)
{
   return 0.5 * dragCo * density *
      (v.getSpeed() * v.getSpeed()) * SURFACEAREA;
}
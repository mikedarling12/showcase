/********************************************************
* 1. Name:
*     Andrew Olson, Michael Darling
* 2. Assignment Name:
*     W12 Lab: Artillery Code Complete 
* 3. Assignment Description:
*     Make the simulatior full functionable and usable.
* 4. What was the hardest part?.
*     Getting the display to work, getting the ground to
*     both appear and function, and finally implementing
*     the projectile path.
* 5. How long did it take?
*     9 hours.
********************************************************/

#include <iostream>
#include "Howitzer.h"
#include "Projectile.h"
#include "Velocity.h"
#include "uiInteract.h"
#include "Direction.h"
#include "Ground.h"
#include "TestVelocity.h"
#include "TestProjectile.h"
#include <vector>

class Simulation
{
private:
   double timeInterval;                   // the time interval
   Howitzer howitzer;                     // the howitzer
   Projectile projectile;                 // the projectile
   list<Position> projectilePath = {};    // the paths of the projectile
   Position  ptUpperRight;                // size of the screen
   Position ptDisplay;                    // the display of the text
   double simTime = 0.5;                  // the simulation time
   Ground ground;                         // the ground
   Interface pUI;                         // the interface

   void hitTarget();
   void getHeightMeters();

public:

   Simulation(Position ptUpperRight) : 
      ptUpperRight(ptUpperRight)
   {
      ground = Ground(ptUpperRight);
      ptDisplay.setPixelsX((ptUpperRight.getPixelsX() - 130));
      ptDisplay.setPixelsY((ptUpperRight.getPixelsY() - 20));

      Position newHozitzerPos(ptUpperRight.getMetersX() / 2, 0);
      howitzer.setPosition(newHozitzerPos);
      reset();
   }

   // Game Steps.

   /*****************************************************
   * RESET
   * Resets the game.
   *****************************************************/
   void reset()
   {
      Position ptHowitzer = howitzer.getPosition();
      ground.reset(ptHowitzer);
      howitzer.setPosition(ptHowitzer);
      projectile.reset();
      projectilePath.clear();
   }

   /*****************************************************
   * FIRE
   * Takes care of everyhting to do with firing the gun.
   *****************************************************/
   void fire(Position rhs)
   {
      projectile.reset();
      projectilePath.clear();
      projectile.setPosition(howitzer.getPosition());
      projectile.setDirection(howitzer.getDirection());
      projectile.setVelocity(howitzer.getMuzzleVelocity());
      projectile.setFlying(true);
   }

   /*****************************************************
    * DISPLAY
    * Takes care of drawing everything in the window.
    ****************************************************/
   void display()
   {
      //
      // draw everything
      //

      ogstream gout(Position(ptUpperRight.getPixelsX() - 10.0,
         ptUpperRight.getPixelsY() - 20.0));

      // draw the ground first
      ground.draw(gout);

      // draw the howitzer
      howitzer.draw(projectile.getFlightTime());



      // draw some text on the screen
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      gout.setPosition(ptDisplay);

      if (projectile.getFlying())
      {
         // Altitude
         gout << "altitude:    "
         << projectile.getAltitude() << "m\n"
         // Speed
         << "speed:    "
         << projectile.getSpeed() << "m/s\n"
         // Distance
         << "distance:    "
         << projectile.getFlightDistance() << "m\n"
         // Hangtime
         << "hang time: "
         << projectile.getFlightTime() << "s\n";

         // draw the projectile
         projectile.draw(projectilePath);
      }
      else
      {
         gout << "angle: "
            << howitzer.getDirection().getDegrees()
            << " degrees";
      }
   }

   /*****************************************************
   * ADVANCE
   * Takes care of all the game logic and math.
   ****************************************************/
   void advance()
   {
      // move a large amount
      if (pUI.isRight())
         howitzer.rotate(0.05);
      if (pUI.isLeft())
         howitzer.rotate(-0.05);

      // move by a little
      if (pUI.isUp())
         howitzer.raise(0.003);
      if (pUI.isDown())
         howitzer.raise(-0.003);

      // fire that gun.
      if (pUI.isSpace())
      {
         fire(howitzer.getPosition());
         addToPath(projectile.getPosition());
         howitzer.resetTime();
      }

      // If the projectile is flying, keep going.
      if (projectile.getFlying())
      {
         // Move the projectile and move the new position into the path.
         projectile.advance(simTime);
         addToPath(projectile.getPosition());

         // Check contact with ground.
         if (projectile.getPosition().getMetersY() - 
            ground.getElevationMeters(projectile.getPosition()) <= 0.0)
         {
            projectile.setFlying(false);

            // Check for the ground specifically.
            if (projectile.getPosition().getMetersX() >= 
               ground.getTarget().getMetersX() - 100 &&
               projectile.getPosition().getMetersX() <= 
               ground.getTarget().getMetersX() + 100)
            {
               reset();
            }
         }
      }
   }

   /***************************************************
   * ADD TO PATH
   * Adds each new projectile to the list of projectiles
   ***************************************************/
   void addToPath(Position newPos)
   {
      if (projectilePath.size() == 10)
      {
         projectilePath.pop_back();
         projectilePath.push_front(newPos);
      }
      else
      {
         projectilePath.push_front(newPos);
      }
   }
};

/******************************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 *****************************************************/
void callBack(const Interface* pUI, void* p)
{
   // The first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulation* pSim = (Simulation*)p;
   pSim->advance();
   pSim->display();
}

double Position::metersFromPixels = 40.0;

/************************************************
* Initialize the simulation and set it in motion
************************************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Cannon go pew-pew",   /* name on the window */
      ptUpperRight);
   
   // Initialize the simulation
   Simulation sim(ptUpperRight);

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}
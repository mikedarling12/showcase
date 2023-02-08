/*************************************************************
 * 1. Name:
 *      Michael Darling and Andrew Olson
 * 2. Assignment Name:
 *      Lab 04: Apollo 11 Visuals
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was making multiple stars and implementing
 *      a class-based solution for this.
 * 5. How long did it take for you to complete the assignment?
 *      5 hours.
 *****************************************************************/

#include "point.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include "ground.h"
#include "lander.h"
#include "star.h"
#include <vector>
#include <iostream>

using namespace std;


/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
	Demo(const Point& ptUpperRight) :
		angle(0.0),
		//ptStar(ptUpperRight.getX() - 20.0, ptUpperRight.getY() - 20.0),
		ptLM(ptUpperRight.getX() / 2.0, ptUpperRight.getY() / 2.0),
		ground(ptUpperRight), lander()
	{


		for (int i = 0; i < 50; i++)
		{

			Star newStar(ptUpperRight);
			stars.push_back(newStar);
		}
		phase = random(0, 255);
	}

	// this is just for test purposes.  Don't make member variables public!
	Point ptLM;           // location of the LM on the screen
	Point ptUpperRight;   // size of the screen
	double angle;         // angle the LM is pointing
	unsigned char phase;  // phase of the star's blinking
	Ground ground;        //
	vector<Star> stars;   //
	Lander lander;        //
};

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
double computeVerticalComponent(float angle, float speed)
{
	return cos(angle) * speed;
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
double computeHorizontalComponent(float angle, float speed)
{
	return sin(angle) * speed;
}

/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double computeTotalComponent(double horComp, double vertComp)
{
	return sqrt((horComp * horComp) + (vertComp * vertComp));
}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
	ogstream gout;

	// Sets a base value for the landers new trajectory
	double xChange = 0.0;
	double yChange = 0.0;

	// the first step is to cast the void pointer into a game object. This
	// is the first step of every single callback function in OpenGL. 
	Demo* pDemo = (Demo*)p;

	// Get fuel for lander display.
	pDemo->lander.getFuel();

	if (pDemo->lander.getFuel() > 0)
	{
		// Adjust the trajectory based on input.
		// If input is left or right, adjust angle and fuel.
		if (pUI->isRight())
		{
			pDemo->angle -= 0.1;
			pDemo->lander.updateFuel(1);
		}
		if (pUI->isLeft())
		{
			pDemo->angle += 0.1;
			pDemo->lander.updateFuel(1);
		}

		// If input is up or down, adjust velocity.
		if (pUI->isUp())
		{
			xChange = computeHorizontalComponent(pDemo->angle, 1.0);
			yChange = computeVerticalComponent(pDemo->angle, -1.0);
		}
		if (pUI->isDown())
		{
			xChange = computeHorizontalComponent(pDemo->angle, -1.0);
			yChange = computeVerticalComponent(pDemo->angle, 1.0);
			pDemo->lander.updateFuel(10);
		}

		// Move the lander using the new trajectory.
		pDemo->ptLM.addX(xChange);
		pDemo->ptLM.addY(yChange);
	}


	// Draw our little star.
	for (int i = 0; i < 50; i++)
	{
		gout.drawStar(pDemo->stars[i].getPoint(), pDemo->phase++);
	}

	// Draw the ground.
	pDemo->ground.draw(gout);

	// Draw the lander and its flames.
	gout.drawLander(pDemo->ptLM /*position*/, pDemo->angle /*angle*/);
	gout.drawLanderFlames(pDemo->ptLM, pDemo->angle, /*angle*/
		pUI->isDown(), pUI->isLeft(), pUI->isRight());

	// Put some text on the screen.
	gout.setPosition(Point(10.0, 380.0));
	gout << "Fuel:     " << pDemo->lander.getFuel() << " lbs" << endl;
	gout << "Altitude: " << (int)pDemo->ptLM.getY() << endl;
	gout << "Speed:   " << computeTotalComponent(xChange, yChange) << "m/s" << endl;
	// gout << "Demo (" << (int)pDemo->ptLM.getX() << ", " << (int)pDemo->ptLM.getY() << ")" << "\n";
}

/********************************************
 * Main is pretty sparse.  Just initialize
 * my Demo type and call the display engine.
 * That is all!
 *******************************************/
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
	Point ptUpperRight(400.0, 400.0);
	Interface ui(0, NULL,
		"Open GL Demo",
		ptUpperRight);

	// Initialize the game class
	Demo demo(ptUpperRight);

	// set everything into action
	ui.run(callBack, &demo);

	return 0;
}

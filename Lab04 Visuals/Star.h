#include <iostream>
#include "point.h"
#pragma once

class Star
{
public:
	Star(const Point& ptUpperRight)
	{
		phase = rand() % 256;
		pt.setX(rand() % (int)ptUpperRight.getX());
		pt.setY(rand() % (int)ptUpperRight.getY());
	}
	Point getPoint() {
		return this->pt;
	}

private:
	char phase;
	Point pt;
};
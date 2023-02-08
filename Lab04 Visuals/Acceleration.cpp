#include "Acceleration.h"

class Acceleration
{
private:
	float ddx;
	float ddy;

public:

	// Constructors 
	Acceleration();
	Acceleration(float ddx, float ddy);
	
	// Getters
	float getDDX() { return ddx; }
	float getDDY() { return ddy; }

	// Setters
	void setDDX(float ddx)
	{
		this->ddx = ddx;
	};
	void setDDY(float ddy)
	{
		this->ddy = ddy;
	};
};
#pragma once
class Lander
{
private:
	int fuel = 5000;

public:
	int getFuel() const
	{
		return fuel;
	}

	void updateFuel(int change)
	{
		this->fuel -= change;
	}
};


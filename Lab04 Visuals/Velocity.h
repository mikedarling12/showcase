class Velocity
{
private:
	float dx;
	float dy;
public:
	Velocity();
	Velocity(float dx, float dy);

	float getDX();
	float getDY();
	float getSpeed();
	void setDX(float dx);
	void setDY(float dy);
	void adjustVelocity(float acceleration, float time);
};
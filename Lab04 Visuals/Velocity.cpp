class Velocity
{
private:
	float dx;
	float dy;
public:
	Velocity();
	Velocity(float dx, float dy);

	float getDX() const { return dx; }
	float getDY() const { return dy; }
	float getSpeed();

	void setDX(float dx)
	{
		this->dx = dx;
	};
	void setDY(float dy)
	{
		this->dy = dy;
	};
	void adjustVelocity(float acceleration, float time)
	{
		
	}
};
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
	float getDDX();
	float getDDY();

	// Setters
	void setDDX(float ddx);
	void setDDY(float ddy);
};
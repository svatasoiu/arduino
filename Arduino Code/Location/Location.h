#ifndef Location_h
#define Location_h

#include "Arduino.h"

class Location
{
	public:
		Location(float x, float y, float theta);
		Location operator+ (Location other);
		Location operator* (float other);
                void setx(float x); void sety(float y); void settheta(float theta);
                float getx(); float gety();  float gettheta();
	private:
		float _x;
		float _y;
		float _theta;
};

#endif

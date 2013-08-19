#include "Arduino.h"
#include "Location.h"

Location::Location(float x, float y, float theta)
{
  setx(x);
  sety(y);
  settheta(theta);
}

void Location::setx(float x){_x = x;}
void Location::sety(float y){_y = y;}
void Location::settheta(float theta){_theta = theta;}

float Location::getx(){return _x;}
float Location::gety(){return _y;}
float Location::gettheta(){return _theta;}

Location Location::operator+ (Location other) {
	Location result(getx() + other.getx(), gety() + other.gety(), gettheta() + other.gettheta());

	return result;
}

Location Location::operator* (float other) {
	Location result(getx() * other, gety() * other, gettheta() * other);

	return result;
}

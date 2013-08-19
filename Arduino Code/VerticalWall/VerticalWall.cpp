#include "Arduino.h"
#include "VerticalWall.h"

VerticalWall::VerticalWall(){}

VerticalWall::VerticalWall(float x, float y1, float y2)
{
	_x1 = x; _y1 = y1; _y2 = y2;
	setLength(y2 - y1);
}


VerticalWall& VerticalWall::operator= (const VerticalWall &other)
{
	//if (*this == other) {return *this;}

	_x1 = other.getx1(); _y1 = other.gety1(); _y2 = other.gety2();
	setLength(_y2 - _y1);

	return *this;
}

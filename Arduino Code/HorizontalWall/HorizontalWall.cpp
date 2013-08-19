#include "Arduino.h"
#include "HorizontalWall.h"

int HorizontalWall::copyOperatorCount = 0;
int HorizontalWall::copyConstructorCount = 0;

HorizontalWall::HorizontalWall()
{}

HorizontalWall::HorizontalWall(float x1, float x2, float y)
{
	_x1 = x1; _x2 = x2; _y1 = y;
	setLength(x2 - x1);
}

HorizontalWall::HorizontalWall(const HorizontalWall &other)
{
    // do the copy
    _x1 = other.getx1(); _x2 = other.getx2();
	_y1 = other.gety1();
	setLength(other.getLength());

	copyConstructorCount++;
}


HorizontalWall& HorizontalWall::operator= (const HorizontalWall &other)
{
    // check for self-assignment by comparing the address of the
    // implicit object and the parameter
    if (this == &other)
        return *this;
 
    // do the copy
    _x1 = other.getx1(); _x2 = other.getx2();
	_y1 = other.gety1();
	setLength(other.getLength());
 
	copyOperatorCount++;
    // return the existing object
    return *this;
}

#ifndef Wall_h
#define Wall_h

#include "Arduino.h"

class Wall
{
public:
	Wall();
	float getLength() const;
	void setLength(float len);
	float getx1() const; float getx2() const; float gety1() const; float gety2() const;
protected:
	float _length;
	float _x1, _x2, _y1, _y2;
};

#endif
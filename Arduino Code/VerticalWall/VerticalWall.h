#ifndef VerticalWall_h
#define VerticalWall_h

#include "Arduino.h"
#include "Wall.h"

class VerticalWall : public Wall
{
public:
	VerticalWall();
	VerticalWall(float x, float y1, float y2);
	VerticalWall& operator= (const VerticalWall &other);
};

#endif
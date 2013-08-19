#ifndef HorizontalWall_h
#define HorizontalWall_h

#include "Arduino.h"
#include "Wall.h"

class HorizontalWall : public Wall
{
public:
	HorizontalWall();
	HorizontalWall(float x1, float x2, float y);
	HorizontalWall& operator= (const HorizontalWall &other);
	HorizontalWall(const HorizontalWall &other);
	
	static int copyOperatorCount;
	static int copyConstructorCount;
};

#endif

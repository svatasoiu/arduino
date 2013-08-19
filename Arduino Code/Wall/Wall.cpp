#include "Arduino.h"
#include "Wall.h"

Wall::Wall(){} //constructor

void Wall::setLength(float len){_length = len;}
float Wall::getLength() const {return _length;}
float Wall::getx1() const {return _x1;}
float Wall::getx2() const {return _x2;}
float Wall::gety1() const {return _y1;}
float Wall::gety2() const {return _y2;}


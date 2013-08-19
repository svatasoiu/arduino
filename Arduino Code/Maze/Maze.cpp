#include "Arduino.h"
#include "Maze.h"

//VerticalWall _vertWalls[7];
//HorizontalWall _horizWalls[7];

Maze::Maze(float width, float height)
	: _width(width), _height(height)
{
	VcurrentSize = 0;
	HcurrentSize = 0;
}

float Maze::getHeight() const {return _height;}
float Maze::getWidth() const {return _width;}
int Maze::getVCurrentSize() const {return VcurrentSize;}
int Maze::getHCurrentSize() const {return HcurrentSize;}

void Maze::setVCurrentSize(int currSize) { VcurrentSize = currSize;}
void Maze::setHCurrentSize(int currSize) { HcurrentSize = currSize;}

/*
VerticalWall* Maze::getVerticalWallAtIndex(int index)
{
	return &(_vertWalls[index]);
}

void Maze::addVerticalWall(VerticalWall const &vw)
{
	if (VcurrentSize == 0) { _vertWalls[0] = vw;}
	else if (VcurrentSize == 7) {return;}
	else {
		for (int i = 0; i < VcurrentSize; i++)
		{
			if (_vertWalls[i].getx1() > vw.getx1())
			{
				for (int k = VcurrentSize; k > i; k--)
				{
					_vertWalls[k] = _vertWalls[k-1];
				}
				_vertWalls[i] = vw;
				VcurrentSize++;
				return;
			}
		}
		_vertWalls[VcurrentSize] = vw;
	}
	VcurrentSize++;
	return;
}

void Maze::addHorizontalWall(HorizontalWall const &hw)
{
	if (HcurrentSize == 0) { _horizWalls[0] = hw;}
	else if (HcurrentSize == 7) {return;}
	else {
		for (int i = 0; i < HcurrentSize; i++)
		{
			if (_horizWalls[i].gety1() > hw.gety1())
			{
				for (int k = HcurrentSize; k > i; k--)
				{
					_horizWalls[k] = _horizWalls[k-1];
				}
				_horizWalls[i] = hw;
				HcurrentSize++;
				return;
			}
		}
		_horizWalls[HcurrentSize] = hw;
	}
	HcurrentSize++;
	return;
}
*/

int Maze::splitVerticalWallsOn(float xValue) const
{
	for (int i = 0; i < VcurrentSize; i ++)
	{
		if (_vertWalls[i].getx1() > xValue) {return i;}
	}
	return -1;
}

int Maze::splitHorizontalWallsOn(float yValue) const
{
	for (int i = 0; i < HcurrentSize; i ++)
	{
		if (_horizWalls[i].gety1() > yValue) {return i;}
	}
	
	return -1;
}

Maze::~Maze()
{
}
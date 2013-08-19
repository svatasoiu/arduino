#ifndef Maze_h
#define Maze_h

class VerticalWall;
class HorizontalWall;

#include "Arduino.h"
#include "HorizontalWall.h"
#include "VerticalWall.h"

class Maze
{
public:
	Maze(float height, float width);
	~Maze();
	float getHeight() const; float getWidth() const;
	int getHCurrentSize() const; int getVCurrentSize() const;
	void setHCurrentSize(int currSize); void setVCurrentSize(int currSize);
	//void addVerticalWall(VerticalWall const &vw);
	//void addHorizontalWall(HorizontalWall const &hw);
	int splitVerticalWallsOn(float xValue) const;
	int splitHorizontalWallsOn(float yValue) const;
	VerticalWall* _vertWalls;
	HorizontalWall* _horizWalls;
private:
	float _height, _width;
	int HcurrentSize, VcurrentSize;
};

#endif
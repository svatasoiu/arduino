#ifndef Particle_h
#define Particle_h

#include "Arduino.h"
#include "Maze.h"

class Particle
{
public:
	Particle();
	Particle(Maze const& maze, int seed);
	Particle(float x, float y, float theta);
	~Particle();
	float measurements[4];
	//float sensors[4][3]; 
	float getx() const; float gety() const; float gettheta() const;
	void setx(float x); void sety(float y); void settheta(float theta);
	void sense(Maze const &maze, int seed);
	float getDistanceToClosestWall(Maze const &maze, float offsetX, float offsetY, float offsetTheta); 
private:
	float _x, _y, _theta;
	bool checkHorizontalWall(HorizontalWall const &hw, float effX);
	bool checkVerticalWall(VerticalWall const &vw, float effY);
	static float gaussrand();
	static float angleMod(float angle);
};

#endif
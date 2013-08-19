#include "Particle.h"

const float M_Pi = 3.14159265358979f;
const float FORWARD_NOISE = 0.1;
const float TURN_NOISE =    0.05;
const float SENSE_NOISE =   0.5;
const int   NUM_MEASUREMENTS = 4;
static const float sensors[NUM_MEASUREMENTS][3] = 
				{{5.0,0.0,0.0},
                 {0.0,5.0,1.5},
                 {-5.0,0.0,3.1416},
                 {0.0,-5.0,-1.5}};

//float measurements[NUM_MEASUREMENTS];
//float sensors[NUM_MEASUREMENTS][3];

Particle::Particle() {}

Particle::Particle(Maze const& maze, int seed)
{
	srand(seed);
	_x = rand() % (int)maze.getWidth();
	_y = rand() % (int)maze.getHeight();
	_theta = (float) (rand() % 31416)/10000;
}

Particle::Particle(float x, float y, float theta)
	: _x(x), _y(y), _theta(theta) 
{}

Particle::~Particle(){}

float Particle::getx() const {return _x;}
float Particle::gety() const {return _y;}
float Particle::gettheta() const {return _theta;}
void Particle::setx(float x) {_x = x;}
void Particle::sety(float y) {_y = y;}
void Particle::settheta(float theta) {_theta = theta;}

void Particle::sense(Maze const &maze, int seed)
{
	srand(seed);
	for (int i = 0; i < NUM_MEASUREMENTS; i++)
	{
        measurements[i] = getDistanceToClosestWall(maze, sensors[i][0], sensors[i][1], sensors[i][2]) + gaussrand()*SENSE_NOISE;
	}
}

float Particle::getDistanceToClosestWall(Maze const &maze,  float offsetX, float offsetY, float offsetTheta)
{
	VerticalWall* verticalWalls = maze._vertWalls;
	HorizontalWall* horizontalWalls = maze._horizWalls;

	int i;
	float minDistance, delX, delY;
	float effectiveTheta = angleMod(_theta + offsetTheta);
	float effectiveX = _x + (cos(_theta)*offsetX - sin(_theta)*offsetY);
	float effectiveY = _y + (sin(_theta)*offsetX + cos(_theta)*offsetY);

	int verticalSplitIndex = maze.splitVerticalWallsOn(effectiveX); //all vertical walls with x>this are to the right of the particle and vice versa
	int horizontalSplitIndex = maze.splitHorizontalWallsOn(effectiveY); //all horizontal walls with y>this are above the particle and vice versa

	if (effectiveTheta >= 0 && effectiveTheta < M_Pi/2.0)
	{
		for (i = verticalSplitIndex; i < maze.getVCurrentSize(); i++) //1st quadrant
		{ 
			delX = verticalWalls[i].getx1()-effectiveX; delY = delX*tan(effectiveTheta);
			if (checkVerticalWall(verticalWalls[i], effectiveY+delY)) { minDistance = sqrt(delX*delX + delY*delY); break; }
		}
		for (i = horizontalSplitIndex; i < maze.getHCurrentSize(); i++)
		{
			delY = horizontalWalls[i].gety1()-effectiveY; delX = delY/tan(effectiveTheta); 
			if (checkHorizontalWall(horizontalWalls[i], effectiveX+delX)) { minDistance = fmin(minDistance, sqrt(delX*delX + delY*delY)); break; }
		}
	}

	else if (effectiveTheta >=  M_Pi/2.0 && effectiveTheta < M_Pi) //2nd quadrant
	{
		for (i = verticalSplitIndex - 1; i >= 0; i--)
		{ 
			delX = verticalWalls[i].getx1()-effectiveX; delY = delX*tan(effectiveTheta);
			if (checkVerticalWall(verticalWalls[i], effectiveY+delY)) { minDistance = sqrt(delX*delX + delY*delY); break; }
		}

		for (i = horizontalSplitIndex; i < maze.getHCurrentSize(); i++)
		{
			delY = horizontalWalls[i].gety1()-effectiveY; delX = delY/tan(effectiveTheta); 
			if (checkHorizontalWall(horizontalWalls[i], effectiveX+delX)) { minDistance = fmin(minDistance, sqrt(delX*delX + delY*delY)); break; }
		}
	}

	else if (effectiveTheta >= M_Pi && effectiveTheta < 3*M_Pi/2.0) //3rd quadrant
	{
		for (i = verticalSplitIndex - 1; i >= 0; i--)
		{
			delX = verticalWalls[i].getx1()-effectiveX; delY = delX*tan(effectiveTheta);
			if (checkVerticalWall(verticalWalls[i], effectiveY+delY)) { minDistance = sqrt(delX*delX + delY*delY); break; }
		}

		for (i = horizontalSplitIndex - 1; i >= 0; i--)
		{
			delY = horizontalWalls[i].gety1()-effectiveY; delX = delY/tan(effectiveTheta); 
			if (checkHorizontalWall(horizontalWalls[i], effectiveX+delX)) { minDistance = fmin(minDistance, sqrt(delX*delX + delY*delY)); break; }
		}
	}

	else //4th quadrant
	{
		for (i = verticalSplitIndex; i < maze.getVCurrentSize(); i++) //1st quadrant
		{ 
			delX = verticalWalls[i].getx1()-effectiveX; delY = delX*tan(effectiveTheta);
			if (checkVerticalWall(verticalWalls[i], effectiveY+delY)) { minDistance = sqrt(delX*delX + delY*delY); break; }
		}	
		for (i = horizontalSplitIndex - 1; i >= 0; i--)
		{
			delY = horizontalWalls[i].gety1()-effectiveY; delX = delY/tan(effectiveTheta); 
			if (checkHorizontalWall(horizontalWalls[i], effectiveX+delX)) { minDistance = fmin(minDistance, sqrt(delX*delX + delY*delY)); break; }
		}
	}

	return minDistance;
}

bool Particle::checkHorizontalWall(HorizontalWall const &hw , float effX)
{
	return (effX >= hw.getx1() && effX <= hw.getx2()) ? true : false;
}

bool Particle::checkVerticalWall(VerticalWall const &vw, float effY)
{
	return (effY >= vw.gety1() && effY <= vw.gety2()) ? true : false;
}

float Particle::angleMod(float angle)
{
	if (angle >= 0 && angle < 2*M_Pi) {return angle;}
	else if (angle >= 2*M_Pi) {angle -= 2*M_Pi; return angleMod(angle);}
	else {angle += 2*M_Pi; return angleMod(angle);}
}

float Particle::gaussrand()
{
	static float V1, V2, S;
	static int phase = 0;
	float X;

	if(phase == 0) {
		do {
			float U1 = (float)rand() / RAND_MAX;
			float U2 = (float)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
			} while(S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	} else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X;
}
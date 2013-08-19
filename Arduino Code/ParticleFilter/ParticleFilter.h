#ifndef ParticleFilter_h
#define ParticleFilter_h

#include "Arduino.h"
#include "Particle.h"

class ParticleFilter
{
public:
	ParticleFilter();
	float measurementProb(Particle const &particle, float (&measurements)[4]);
	float gaussian(float mu, float sigma, float measure);
	static float getMaxOfArray(float arr[], int size);
	void getWeightings(Particle* const &particles, float (&measurements)[4]);
	float weightings[];
	Particle GetMode(Particle* const &daArray, int iSize);
	void resample(Particle particles[], int size);
	Particle* moveParticles(Particle* particles, float turn, float forward, int size);
	//Particle particles[100];
private:
	static float gaussrand();
	static float angleMod(float angle);
};

#endif
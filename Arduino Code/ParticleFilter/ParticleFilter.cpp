#include "ParticleFilter.h"

const float M_Pi = 3.14159265358979f;
const float FORWARD_NOISE = 0.1;
const float TURN_NOISE =    0.05;
const float SENSE_NOISE =   0.5;
const int   NUM_MEASUREMENTS = 4;
const int NUMBER_OF_PARTICLES = 10;

float weightings[NUMBER_OF_PARTICLES];

ParticleFilter::ParticleFilter() {}

void ParticleFilter::resample(Particle particles[], int size) 
{
	Particle parts[size];
	float beta = 0.0;
	int index = rand() % size;
	float mw = getMaxOfArray(weightings, size);
	for (int i = 0; i < size-1; i++)
	{
		//Serial.print((float) (rand() / RAND_MAX));
		beta += ((float) rand()) / (float)RAND_MAX * 2.0 * mw;
		do {
			beta -= weightings[index];
			index = (index+1) % size;
		} while (weightings[index] < beta);
		parts[i] = particles[index];
	}   
	for (int j = size - 1; j < size; j ++)
	{
		parts[j] = Particle((float)(rand() % 244), (float)(rand() % 244), (float) (rand() % 31416)/10000);
	}
	//particles = parts;
	for (int k = 0; k < size; ++k)
	{
		particles[k] = parts[k];
	}
}
Particle ParticleFilter::GetMode(Particle* const &daArray, int iSize) {
    // Allocate an int array of the same size to hold the
    // repetition count
    int* ipRepetition[iSize];
    for (int i = 0; i < iSize; ++i) {
        ipRepetition[i] = 0;
        int j = 0;
        bool bFound = false;
        while ((j < i) && (daArray[i].getx() != daArray[j].getx())) {
            if (daArray[i].getx() != daArray[j].getx()) {
                ++j;
            }
        }
        ++(ipRepetition[j]);
    }
    int iMaxRepeat = 0;
    for (int i = 1; i < iSize; ++i) {
        if (ipRepetition[i] > ipRepetition[iMaxRepeat]) {
            iMaxRepeat = i;
        }
    }
    return daArray[iMaxRepeat];
}
Particle* ParticleFilter::moveParticles(Particle* particles, float turn, float forward, int size)
{
	for (int i = 0; i < size; i++)
	{
		float dist = forward + gaussrand() * FORWARD_NOISE;
		float newOrientation = angleMod(particles[i].gettheta() + gaussrand() * TURN_NOISE);
		particles[i].settheta(newOrientation);
		particles[i].setx(particles[i].getx() + cos(newOrientation) * dist);
        particles[i].sety(particles[i].getx() + sin(newOrientation) * dist);
	}
}

float ParticleFilter::getMaxOfArray(float arr[], int size)
{
	float max;
	max = arr[0];
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > max) {max = arr[i];}
	}
	return max;
}

float ParticleFilter::measurementProb(Particle const &particle, float (&measurements)[4])
{
	float prob = 1.0;
    for (int i = 0; i < NUM_MEASUREMENTS; i++)
	{
        prob *= gaussian(particle.measurements[i], SENSE_NOISE, measurements[i]);
	}
    return prob;
}

float ParticleFilter::gaussian(float mu, float sigma, float measure)
{
	return exp(-((mu-measure)*(mu-measure))/(sigma*sigma)/2.0) / sqrt(2.0*M_Pi*(sigma*sigma));
}

void ParticleFilter::getWeightings(Particle* const &particles, float (&measurements)[4])
{
	for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		weightings[i] = measurementProb(particles[i], measurements);
	}
}


float ParticleFilter::angleMod(float angle)
{
	if (angle >= 0 && angle < 2*M_Pi) {return angle;}
	else if (angle >= 2*M_Pi) {angle -= 2*M_Pi; return angleMod(angle);}
	else {angle += 2*M_Pi; return angleMod(angle);}
}

float ParticleFilter::gaussrand()
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
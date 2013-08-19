//SharpIR.cpp made by Sorin Vatasoiu Jr., January 9, 2013

#include "Arduino.h"
#include "SharpIR.h"

SharpIR::SharpIR(int pin, int sensorType)
{
   //pinMode(pin, INPUT);
   _pin = pin;
   _sensorType = sensorType;
}

int SharpIR::Reading()
{
	return analogRead(_pin);
}

float SharpIR::Range()
{
  int reading = Reading();
  if (reading < 3)
    return -1; // invalid value

  if (_sensorType) {return (2914.0 /((float)reading + 5.0)) - 1.0; }//gp2d120
  else {return (6787.0 /((float)reading - 3.0)) - 4.0; } //gp2d12
}

float SharpIR::averageRange(int readings)
{
	float total = 0.0;

	for (int i = 0; i < readings; i++)
	{
		total += Range();
	}

	return total/(float)readings;
}
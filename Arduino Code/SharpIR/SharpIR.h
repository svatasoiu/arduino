//SharpIR.h by Sorin Vatasoiu Jr., January 9, 2013

#ifndef SharpIR_h
#define SharpIR_h

#include "Arduino.h"

#define GP2D120 1
#define GP2D12 0

class SharpIR
{
  public:
    SharpIR(int pin, int sensorType);
	int Reading();
	float Range();
	float averageRange(int readings);
	
    int _pin, _sensorType;

   private:
    float distance_cm;
    
};

#endif
/*
  SharpIRDistance.h - Library for measuring distance with the Sharp IR distance sensor.
  Created by Oliver Hofkens, December 22, 2014.

  This code released into public domain.
*/
#ifndef SharpIRDistance_h
#define SharpIRDistance_h

#include "Arduino.h"

//See SharpIRDistance.cpp for comments on all functions.
class SharpIRDistance
{
  public:
	SharpIRDistance(int pin);
    int getDistance();
    bool isCloser(int dist);
  private:
    int _pin;
};
#endif

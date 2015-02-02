/*
  SharpIRDistance.h - Library for measuring distance with the Sharp IR distance sensor.
  Created by Oliver Hofkens, December 22, 2014.

  This code released into public domain.
  CHECK FILTER LIBRARIES FOR LICENSE INFO!
*/
#ifndef SharpIRDistance_h
#define SharpIRDistance_h

#include "Arduino.h"
#include "Filter.h"
#include "MedianFilter.h"

//See SharpIRDistance.cpp for comments on all functions.
class SharpIRDistance
{
  public:
	SharpIRDistance();
    void begin(int pin);
    int getDistance();
    bool isCloser(int dist);
  private:
    int _pin;
    MedianFilter _filter;
};
#endif

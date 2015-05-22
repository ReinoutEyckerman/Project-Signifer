/*
  SharpIRDistance.h - Library for measuring distance with the Sharp IR distance sensor.
  Created by Oliver Hofkens, December 22, 2014.

  This code released into public domain.
*/

#include "Arduino.h"
#include "SharpIRDistance.h"

SharpIRDistance::SharpIRDistance(int pin)
{
	_pin = pin;
}

//Lees analoge waarde van sensor, bereken hieruit afstand.
int SharpIRDistance::getDistance()
{
  int analogDistance = analogRead(_pin);
  int distanceCentimeters = 1/(0.0004*analogDistance-0.0081);
  
  return Filter(distanceCentimeters);
}

int SharpIRDistance::Filter(int distance){
		if(distance > 30 || distance < 0){
			return 30;
			}
		else return distance;
	}

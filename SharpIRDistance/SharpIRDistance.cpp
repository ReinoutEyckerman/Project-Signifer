/*
  SharpIRDistance.h - Library for measuring distance with the Sharp IR distance sensor.
  Created by Oliver Hofkens, December 22, 2014.

  This code released into public domain.
  CHECK AVERAGE & FILTER LIBRARIES FOR LICENSE INFO!
*/

#include "Arduino.h"
#include "Filter.h"
#include "MedianFilter.h"
#include "SharpIRDistance.h"

SharpIRDistance::SharpIRDistance()
{}

//Begin, zet _pin variabele en start de filter.
void SharpIRDistance::begin(int pin)
{
  _pin = pin;
  _filter.begin();
}

//Lees analoge waarde van sensor, bereken hieruit afstand (zie vorige labo voor details),
//filter deze waarde adhv de firFilter, en push deze dan in onze rollingAverage circular buffers.
int SharpIRDistance::getDistance()
{
  int analogDistance = analogRead(_pin);
  int distanceCentimeters = 1/(0.0004*analogDistance-0.0081);

  int filteredValue = _filter.run(distanceCentimeters);
  
  return filteredValue;
}

//Indien laatste meting kleiner is dan gegeven parameter, return true.
bool SharpIRDistance::isCloser(int dist)
{
	return (getDistance() < dist);
}

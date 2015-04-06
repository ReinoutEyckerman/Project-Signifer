/*
SensorController.cpp - Library for controlling all IR sensors on our robot.
Created by Oliver Hofkens, March 30, 2014.

This code released into public domain.
*/

#include "Arduino.h"
#include "SensorController.h"

int SensorController::GetCrossDistance1(){
	return _sensor1.getDistance();
}

int SensorController::GetCrossDistance2(){
	return _sensor2.getDistance();
}

int SensorController::GetCrossDistance(){
	int dist1 = _sensor1.getDistance();
	int dist2 = _sensor2.getDistance();
	if (dist1 < dist2)
		return dist1;
	else return dist2;
}

int SensorController::GetTopDistance(){
	return _sensorTop.getDistance();
}
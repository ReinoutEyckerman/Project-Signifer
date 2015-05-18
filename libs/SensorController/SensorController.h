/*
SensorController.h - Library for controlling all IR sensors on our robot.
Created by Oliver Hofkens, March 30, 2014.

This code released into public domain.
*/
#ifndef SensorController_h
#define SensorController_h

#include "Arduino.h"
#include "SharpIRDistance.h"
#include "Servo.h"
//See SensorController.cpp for comments on all functions.
class SensorController
{
public:
	SensorController(int pinSensor1, int pinSensor2, int pinSensorTop, Servo myservo ) : _sensor1(pinSensor1), _sensor2(pinSensor2), _sensorTop(pinSensorTop){
	 _myservo=myservo;
	};
	int GetDiagDistance1();
	int GetDiagDistance2();
	int GetDiagDistanceMin();
	int GetDistance1();
	int GetDistance2();
	int GetDistanceMin();
	int GetAngle();
	void LookRight();
	void LookLeft();
	void LookStraight();
	int GetTopDistance();
private:
	int pos;
        SharpIRDistance _sensor1;
	SharpIRDistance _sensor2;
	SharpIRDistance _sensorTop;
        Servo _myservo;	
	int DiagToStraight(int diagDist);
};
#endif

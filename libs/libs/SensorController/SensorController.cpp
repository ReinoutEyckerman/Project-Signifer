/*
SensorController.cpp - Library for controlling all IR sensors on our robot.
Created by Oliver Hofkens, March 30, 2014.

This code released into public domain.
*/

#include "Arduino.h"
#include "SensorController.h"
#include "Servo.h"

SensorController::SensorController(int pinSensor1, int pinSensor2, int pinSensorTop, int pinServo): _sensor1(pinSensor1), _sensor2(pinSensor2), _sensorTop(pinSensorTop{
	myservo.attach(pinServo);
	myservo.write(pos);
}

		 
int SensorController::GetDiagDistance1(){
	return _sensor1.getDistance();
}

int SensorController::GetDiagDistance2(){
	return _sensor2.getDistance();
}

int SensorController::GetDiagDistanceMin(){
	int dist1 = _sensor1.getDistance();
	int dist2 = _sensor2.getDistance();
	if (dist1 < dist2)
		return dist1;
	else return dist2;
}

int SensorController::GetDistance1(){
	return DiagToStraight(GetDiagDistance1());	
}

int SensorController::GetDistance2(){
	return DiagToStraight(GetDiagDistance2());	
}

int SensorController::GetDistanceMin(){
	return DiagToStraight(GetDiagDistanceMin());	
}

int SensorController::GetTopDistance(){
	return _sensorTop.getDistance()+2;
}

int SensorController::DiagToStraight(int diagDist){
	return (Cos(3.1415/6)*diagDist);
}

int SensorController::GetAngle(){
	LookStraight();
	return (Tan(6/GetTopDistance()));
}
void SensorController::LookLeft(){
	myservo.write(0);		
	delay(15);
}
void SensorController::LookRight(){
	myservo.write(180);
	delay(15);
}
void SensorController::LookStraight()
{
	myservo.write(90);
}

/*
SensorController.cpp - Library for controlling all IR sensors on our robot.
Created by Oliver Hofkens, March 30, 2014.

This code released into public domain.
*/

#include "Arduino.h"
#include "SensorController.h"
#include "Servo.h"

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
	return _sensorTop.getDistance();
}

int SensorController::DiagToStraight(int diagDist){
	return (cos(3.1415/6)*diagDist);
}

int SensorController::GetAngle(){
	LookStraight();
	return (tan(6/GetTopDistance()));
}
void SensorController::LookLeft(){
 for(pos;pos>=0;pos--){
	_myservo.write(pos);
	delay(2);
}}
void SensorController::LookRight(){
   for(pos;pos<180;pos++){
	_myservo.write(pos);
	delay(2);
}}
void SensorController::LookStraight()
{
	TurnServo(90);
}

void SensorController::TurnServo(int degrees){
	if(pos>degrees)
	{
		for(pos; pos >= degrees; pos--)  // goes from 0 degrees to 180 degrees
		{                                  // in steps of 1 degree
			_myservo.write(pos);              // tell servo to go to position in variable 'pos'
			delay(2);                       // waits x ms for the servo to reach the position
		}
	}
  else
  {
		for(pos; pos <= degrees; pos++)
		{
			_myservo.write(pos);
			delay(2);
		}
	}
	}

int SensorController::GetTopAtAngle(int degrees){
		TurnServo(degrees);
		return GetTopDistance();
}

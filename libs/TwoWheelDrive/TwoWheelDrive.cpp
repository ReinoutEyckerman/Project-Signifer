/*
TwoWheelDrive.h - Library for driving the car using 2 motors.
Created by Oliver Hofkens, February 2015.
Released into the public domain.
*/
#include "Arduino.h"
#include "TwoWheelDrive.h"
#include "Motor.h"

void TwoWheelDrive::Forward(byte power){
	_leftMotor.DriveForward(power);
	_rightMotor.DriveForward(power);
}

void TwoWheelDrive::Forward(){
	Forward(255);
}

void TwoWheelDrive::Backward(byte power){
	_leftMotor.DriveBackward(power);
	_rightMotor.DriveBackward(power);
}

void TwoWheelDrive::Backward(){
	Backward(255);
}

void TwoWheelDrive::RotateLeft(byte powerBack, byte powerForward){
	_leftMotor.DriveBackward(powerBack);
	_rightMotor.DriveForward(powerForward);
}

void TwoWheelDrive::RotateLeft(){
	RotateLeft(255, 255);
}

void TwoWheelDrive::RotateRight(byte powerBack, byte powerForward){
	_leftMotor.DriveForward(powerForward);
	_rightMotor.DriveBackward(powerBack);
}

void TwoWheelDrive::RotateRight(){
	RotateRight(255, 255);
}

void TwoWheelDrive::PivotLeft(byte power){
	RotateLeft(0,power);
}

void TwoWheelDrive::PivotLeft(){
	PivotLeft(255);
}

void TwoWheelDrive::PivotRight(byte power){
	RotateRight(0, power);
}

void TwoWheelDrive::PivotRight(){
	PivotRight(255);
}

void TwoWheelDrive::Stop(){
	_leftMotor.Stop();
	_rightMotor.Stop();
}
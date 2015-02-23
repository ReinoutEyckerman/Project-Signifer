/*
TwoWheelDrive.h - Library for driving the car using 2 motors.
Created by Oliver Hofkens, February 2015.
Released into the public domain.
*/
#include "Arduino.h"
#include "Motor.h"
#include "TwoWheelDrive.h"

TwoWheelDrive::TwoWheelDrive(Motor motorLeft, Motor motorRight){
	_leftMotor = motorLeft;
	_rightMotor = motorRight;
}

void TwoWheelDrive::TwoWheelDrive(int leftForward, int leftBackward, int rightForward, int rightBackward){
	_leftMotor(leftForward, leftBackward);
	_rightMotor(rightForward, rightBackward);
}


void TwoWheelDrive::Forward(byte power = 255){
	_leftMotor.DriveForward(power);
	_rightMotor.DriveForward(power);
}

void TwoWheelDrive::Backward(byte power = 255){
	_leftMotor.DriveBackward(power);
	_rightMotor.DriveBackward(power);
}

void TwoWheelDrive::RotateLeft(byte powerBack = 255, byte powerForward = 255){
	_leftMotor.DriveBackward(powerBack);
	_rightMotor.DriveForward(powerForward);
}

void TwoWheelDrive::RotateRight(byte powerBack = 255, byte powerForward = 255){
	_leftMotor.DriveForward(powerForward);
	_rightMotor.DriveBackward(powerBack);
}

void TwoWheelDrive::Stop(){
	_leftMotor.Stop();
	_rightMotor.Stop();
}
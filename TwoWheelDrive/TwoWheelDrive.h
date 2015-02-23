/*
TwoWheelDrive.h - Library for driving the car using 2 motors.
Created by Oliver Hofkens, February 2015.
Released into the public domain.
*/
#ifndef TwoWheelDrive_h
#define TwoWheelDrive_h

#include "Arduino.h"
#include "Motor.h"

//See .cpp file for comments on the functions.
class TwoWheelDrive
{
public:
	//Constructor: Takes 2 motor objects as arguments.
	TwoWheelDrive(Motor motorLeft, Motor motorRight);

	//Constructor: Takes 4 H-bridge pins as arguments.
	TwoWheelDrive(int leftForward, int leftBackward, int rightForward, int rightBackward);

	//Drive forward with optional parameter for the power.
	void Forward(byte power = 255);

	//Drive backward with optional parameter for the power.
	void Backward(byte power = 255);

	//Turn left by giving a forward speed and a backward speed as arguments.
	void RotateLeft(byte powerBack = 255, byte powerForward = 255);

	//Turn right by giving a forward speed and a backward speed as arguments.
	void RotateRight(byte powerBack = 255, byte powerForward = 255);

	//Full stop.
	void Stop();

private:
	Motor _leftMotor;
	Motor _rightMotor;
};

#endif
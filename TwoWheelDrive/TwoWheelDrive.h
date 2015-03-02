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
	//Constructor: Takes 4 H-bridge pins as arguments.
	TwoWheelDrive(int leftForward, int leftBackward, int rightForward, int rightBackward) :_leftMotor(leftForward, leftBackward), _rightMotor(rightForward, rightBackward){};

	//Drive forward with optional parameter for the power.
	void Forward(byte power);

	//Arduino doesn't support default arguments.
	void Forward();

	//Drive backward with optional parameter for the power.
	void Backward(byte power);

	//Arduino doesn't support default arguments.
	void Backward();

	//Turn left by giving a forward speed and a backward speed as arguments.
	void RotateLeft(byte powerBack, byte powerForward);

	//Arduino doesn't support default arguments.
	void RotateLeft();

	//Turn right by giving a forward speed and a backward speed as arguments.
	void RotateRight(byte powerBack, byte powerForward);

	//Arduino doesn't support default arguments.
	void RotateRight();

	//Turn left by stopping the left wheel.
	void PivotLeft(byte power);

	//Arduino doesn't support default arguments.
	void PivotLeft();

	//Turn right by stopping the right wheel.
	void PivotRight(byte power);

	//Arduino doesn't support default arguments.
	void PivotRight();

	//Full stop.
	void Stop();

private:
	Motor _leftMotor;
	Motor _rightMotor;
};

#endif
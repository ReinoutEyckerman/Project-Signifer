/*
Motor.h - Library for controlling a motor through the L293D IC.
Created by Oliver Hofkens, November 2014.
Released into the public domain.
*/
#include "Arduino.h"
#include "Motor.h"

//Constructor: Takes the 2 pins of the H-bridge.
Motor::Motor(int pinForward, int pinBackward)
{
  _pinForward = pinForward;
  _pinBackward = pinBackward;
  pinMode(pinForward, OUTPUT);
  pinMode(pinBackward, OUTPUT);
}

//Drive forward with the PWM power given as argument (0-255).
void Motor::DriveForward(unsigned int power)
{
  analogWrite(_pinBackward,0);
  analogWrite(_pinForward,power);
}

//Drive forward at max power.
void Motor::DriveForward(){
	Motor::DriveForward(255);
}

//Drive backward with the PWM power given as argument (0-255).
void Motor::DriveBackward(unsigned int power)
{
  analogWrite(_pinForward,0);
  analogWrite(_pinBackward,power);
}

//Drive backward at max power.
void Motor::DriveBackward(){
	Motor::DriveBackward(255);
}

//"Fast Motor Stop" function of the L293D IC.
void Motor::Stop()
{
  analogWrite(_pinForward,0);
  analogWrite(_pinBackward,0);
}

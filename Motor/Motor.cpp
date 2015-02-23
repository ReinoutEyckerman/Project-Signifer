/*
Motor.h - Library for controlling a motor through the L293D IC.
Created by Oliver Hofkens, November 2014.
Released into the public domain.
*/
#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pinForward, int pinBackward)
{
  _pinForward = pinForward;
  _pinBackward = pinBackward;
  pinMode(pinForward, OUTPUT);
  pinMode(pinBackward, OUTPUT);
}

void Motor::DriveForward(byte power = 255)
{
  analogWrite(_pinBackward,0);
  analogWrite(_pinForward,power);
}

void Motor::DriveBackward(byte power = 255)
{
  analogWrite(_pinForward,0);
  analogWrite(_pinBackward,power);
}

void Motor::Stop()
{
  analogWrite(_pinForward,0);
  analogWrite(_pinBackward,0);
}

/*
  Motor.cpp - By Oliver
  Stelt één enkele motor voor die door middel van een H-brug voor-en achteruit kan gestuurd worden.
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

void Motor::DriveForward(unsigned int power)
{
  analogWrite(_pinBackward,0);
  analogWrite(_pinForward,power);
}

void Motor::DriveBackward(unsigned int power)
{
  analogWrite(_pinForward,0);
  analogWrite(_pinBackward,power);
}

void Motor::Stop()
{
  analogWrite(_pinForward,0);
  analogWrite(_pinBackward,0);
}

/*
Motor.h - Library for controlling a motor through the L293D IC.
Created by Oliver Hofkens, November 2014.
Released into the public domain.
*/
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
  public:
	//Constructor: Takes the 2 pins of the H-bridge.
    Motor(int pinForward, int pinBackward);

	//Drive forward with the PWM power given as argument (0-255).
    void DriveForward(byte power = 255);

	//Drive backward with the PWM power given as argument (0-255).
    void DriveBackward(byte power = 255);

	//"Fast Motor Stop" function of the L293D IC.
    void Stop();   

  private:
	//Pin number for H-bridge forward.
   int _pinForward;

   //Pin number for H-bridge backward.
   int _pinBackward; 
};

#endif

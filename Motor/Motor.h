/*
Motor.h - Library for controlling a motor through the L293D IC.
Created by Oliver Hofkens, November 2014.
Released into the public domain.
*/
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

//See .cpp file for comments on the functions.
class Motor
{
  public:
    Motor(int pinForward, int pinBackward);
    void DriveForward(unsigned int power);
	void DriveForward();
    void DriveBackward(unsigned int power);
	void DriveBackward();
    void Stop();   
  private:
   int _pinForward;
   int _pinBackward; 
};

#endif

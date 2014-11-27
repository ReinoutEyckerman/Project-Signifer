#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
  public:
    Motor(int pinForward, int pinBackward);
    void DriveForward(unsigned int power);
    void DriveBackward(unsigned int power);
    void Stop();   
  private:
   int _pinForward;
   int _pinBackward; 
};

#endif

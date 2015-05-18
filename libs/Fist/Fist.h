#ifndef Fist_h
#define Fist_h

#include "Arduino.h"

class Fist
{
  public:
	void Run();  
  private:
    void ByteArrayCopy(int a[], int b[], int array_size);
	void Measurements();
    void CheckGestures();
	boolean ByteArrayCompare(int a[],int b[],int array_size);
	void SerialDebug();
	int AccelleroConverter(int c);
	int temp[];
	int current[];
};
#endif
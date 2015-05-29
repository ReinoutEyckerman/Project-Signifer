#ifndef Fist_h
#define Fist_h

#include "Arduino.h"

class Fist
{
  public:
	void Run();  
 	void SerialDebug();
  private:
    void ByteArrayCopy(int a[], int b[], int array_size);
	void Measurements();
    void CheckGestures();
	boolean ByteArrayCompare(int a[],int b[],int array_size);
	int AccelleroConverter(int c);
	int temp[];
	int current[];
	int Flat[];
	int Vertical[];
	int Take[];
	int Stop[];
	int RStop[];
	int RVertical[];
	int Verticlap[];
	int Vertispand[];
	int Horiclap[];
	int Horispand[];
	int Hai[];
	int Heil[];
};
#endif

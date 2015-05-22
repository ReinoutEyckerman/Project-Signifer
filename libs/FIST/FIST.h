#ifndef FIST_h
#define FIST_h
#include "Arduino.h"

class FIST{
public:
	FIST(int PalmX, int PalmY, int PalmZ, int KnuckleX,int KnuckleY, int KnuckleZ, char hand, int ButtonPin);
	void SerialDebug();
	void Run();
private:
	void Measurements();
	int AcceleroConverter(int c);
	void CheckGestures();
	bool ByteArrayCompare(int a[], int b[], int array_size);
	void ByteArrayCopy(int a[], int b[], int array_size);
	int ButtonPin;
	int PalmX;
	int PalmY;
	int PalmZ;
	int KnuckleX;
	int KnuckleY;
	int KnuckleZ;
	char Hand;
	String previous;
};
#endif

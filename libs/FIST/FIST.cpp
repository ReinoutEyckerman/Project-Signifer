#include "Arduino.h"
#include "FIST.h"
//Arrays containing values of certain gestures.

int Flat[] = {0, 0, 1, 0, 0, 1};
int Bump[] = {0, 0, 1, 0, 1, 0};

int Stop[] = {0, -1, 0, 0, -1, 0};
int Revolution[] = {0, -1, 0, 0, 0, 1};

int Down[] = { 0, 0, 1, 0, 1, 1};
int Clench[] = {0, 1, 0, 0, 0, -1};

int Beg[] = {0, 0, -1, 0 , 0, -1};
int Flex[] = {0, 0, -1, 0, -1, 0};

int Push[6];
int Take[6];

//Variables for comparing the gestures to the input

int temp[] = {0, 0, 0, 0, 0, 0};
int current[] = {0, 0, 0, 0, 0, 0};
String previous;

FIST::FIST(int PalmX, int PalmY, int PalmZ, int KnuckleX, int KnuckleY, int KnuckleZ, char Hand, int ButtonPin)
{
	this->PalmX=PalmX;
	this->PalmY=PalmY;
	this->PalmZ=PalmZ;
	this->KnuckleX=KnuckleX;
	this->KnuckleY=KnuckleY;
	this->KnuckleZ=KnuckleZ;
	this->Hand=Hand;
	this->ButtonPin=ButtonPin;
	int x[]={1,0,0,1,0,0};
	int y[]={-1,0,0,-1,0,0};
	if(Hand=='l')
	{
		ByteArrayCopy(Push,x ,6);
		ByteArrayCopy(Take,y,6);
	}
	else
	{
		ByteArrayCopy(Take, x, 6);
		ByteArrayCopy(Push, y,6);
	}
}


//Loop
void FIST::Run() {
  Measurements();
  CheckGestures();
}

//Loop
void FIST::Measurements() {
  current[0] = AcceleroConverter(analogRead(PalmX));
  current[1] = AcceleroConverter(analogRead(PalmY));
  current[2] = AcceleroConverter(analogRead(PalmZ));
  current[3] = AcceleroConverter(analogRead(KnuckleX));
  current[4] = AcceleroConverter(analogRead(KnuckleY));
  current[5] = AcceleroConverter(analogRead(KnuckleZ));
}

//Filters Sensordata to data program can easily process
int FIST::AcceleroConverter(int c)
{
  //325-340 stable, 385-410 ud, 255-285 min  240 max 430
  if (c < 290)
    return -1;
  if (c < 380)
    return 0;
  return 1;
}

//Compares input to gestures
void FIST::CheckGestures() {
  String x;
  if (!ByteArrayCompare(current, temp, 6))
  {
    ByteArrayCopy(temp, current, 6);
    if (ByteArrayCompare(current, Flat, 6) )
      x = "Flat";
    else if (ByteArrayCompare(current, Bump, 6))
      x = "Bump";
    else if (ByteArrayCompare(current, Take, 6) )
      x = "Take";
    else if (ByteArrayCompare(current, Push, 6))
      x = "Push";
    else if (ByteArrayCompare(current, Stop, 6))
      x = "Stop";
    else if (ByteArrayCompare(current, Revolution, 6))
      x = "Revolution";
    else if (ByteArrayCompare(current, Down, 6))
      x = "Down";
    else if (ByteArrayCompare(current, Clench, 6))
      x = "Clench";
    else if (ByteArrayCompare(current, Beg, 6))
      x = "Beg";
    else if (ByteArrayCompare(current, Flex, 6))
      x = "Flex";   
    if (x != previous)
    {
      previous = x;
      String y= Hand+x; 
      Serial.println(y);
    }
  }
}

//Compares if 2 arrays are equal
bool FIST::ByteArrayCompare(int a[], int b[], int array_size)
{
  for (int i = 0; i < array_size; ++i)
    if (a[i] != b[i])
      return (false);
  return (true);
}

//Copies the contents of an array to another one
void FIST::ByteArrayCopy(int a[], int b[], int array_size) {
  for (int i = 0; i < array_size; ++i)
    a[i] = b[i];
}

//Debugging Output
//Recommendend using this when directly connected to a computer.
void FIST::SerialDebug() {
  Serial.println("Incoming");
  Serial.print(" X: "); Serial.print(current[0]);
  Serial.print(" Y: "); Serial.print(current[1]);
  Serial.print(" Z: "); Serial.println(current[2]);
  Serial.print(" X: "); Serial.print(current[3]);
  Serial.print(" Y: "); Serial.print(current[4]);
  Serial.print(" Z: "); Serial.println(current[5]);
  Serial.println((analogRead(PalmX)));
  Serial.println((analogRead(PalmY)));
  Serial.println((analogRead(PalmZ)));
  Serial.println((analogRead(KnuckleX)));
  Serial.println((analogRead(KnuckleY)));
  Serial.println((analogRead(KnuckleZ)));
  Serial.println("---");
}

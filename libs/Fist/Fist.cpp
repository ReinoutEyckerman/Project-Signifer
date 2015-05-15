#include "Arduino.h"
#include "Fist.h"

const int pinBtn = 2;
const int pinFlex = A0;
const int pinTouch = A1;
const int PalmX = A2;
const int PalmY = A3;
const int PalmZ = A4;
const int KnuckleX = A5;
const int KnuckleY = A6;
const int KnuckleZ = A7;
const int Flat[]={0,0,1};
const int Vertical[]={1,0,0};
const int Take[]={0,0,-1};
const int Stop[]={0,1,0};
const int RStop[]={0,-1,0};
const int RVertical[]={-1,0,0};
const int Verticlap[]={0,0,2};
const int Vertispand[]={0,0,-2};
const int Horiclap[]={1,0,-2};
const int Horispand[]={1,0,2};
const int Hai[]={1,0,2};
const int Heil[]={-2,-2,0};
int temp[]={0,0,0,0,0,0};
int current[]={0,0,0,0,0,0};

void Fist::Run(){
	Measurements();
	CheckGestures();
}
void Fist::Measurements(){
  current[0] = AccelleroConverter(analogRead(PalmX));
  current[1] = AccelleroConverter(analogRead(PalmY));
  current[2] = AccelleroConverter(analogRead(PalmZ));
  current[3] = AccelleroConverter(analogRead(KnuckleX));
  current[4] = AccelleroConverter(analogRead(KnuckleY));
  current[5] = AccelleroConverter(analogRead(KnuckleZ));
}

int Fist::AccelleroConverter(int c)
{
   //325-340 stable, 385-410 ud, 255-285 min  240 max 430
  if(c<240)
    return -2;
  else if(c<285)
    return -1;
  else if(c>285&&c<385)
    return 0;
  else if(c>385&&c<410)
    return 1;
  else 
    return 2;
}
void Fist::CheckGestures(){

  if(!ByteArrayCompare(current, temp, 6))
  { 
   	ByteArrayCopy(temp,current,6);
      // Serial.println("Flat");
 // SerialDebug();
 if(ByteArrayCompare(current, Flat, 6) )
Serial.println("Flat");
else if(ByteArrayCompare(current, Vertical, 6))
   Serial.println("Vertical");
 else if(ByteArrayCompare(current, Take, 6) )
      Serial.println("Take");
 else if(ByteArrayCompare(current, Stop, 6) )
    Serial.println("Stop");
else if(ByteArrayCompare(current, Verticlap, 6) )
    Serial.println("Verticlap");
    else if(ByteArrayCompare(current, Vertispand, 6))
    Serial.println("Vertispand");
else if(ByteArrayCompare(current, Horiclap, 6) )
   Serial.println("Horiclap");
 else if(ByteArrayCompare(current, Horispand, 6))
    Serial.println("Horispand");
 else if(ByteArrayCompare(current, Hai, 6))
    Serial.println("Hai");
 else if(ByteArrayCompare(current, Heil, 6))
     Serial.println("Heil");
 else if(ByteArrayCompare(current, RVertical, 6))
     Serial.println("RVertical");
 else if(ByteArrayCompare(current, RStop, 6))
   Serial.println("RStop");
  }
}
boolean Fist::ByteArrayCompare(int a[],int b[],int array_size)
{
   for (int i = 0; i < array_size; ++i)
     if (a[i] != b[i])
       return(false);
   return(true);
}
void Fist::ByteArrayCopy(int a[], int b[], int array_size){
	for (int i = 0; i < array_size; ++i)
		a[i]=b[i];
}
void Fist::SerialDebug(){
  Serial.println("Incoming");
  Serial.print(" X: "); Serial.print(current[0]);
  Serial.print(" Y: "); Serial.print(current[1]);
  Serial.print(" Z: "); Serial.println(current[2]);
  Serial.print(" X: "); Serial.print(current[3]);
  Serial.print(" Y: "); Serial.print(current[4]);
  Serial.print(" Z: "); Serial.println(current[5]);
  Serial.println("Debug");
  Serial.print(" X: "); Serial.print(temp[0]);
  Serial.print(" Y: "); Serial.print(temp[1]);
  Serial.print(" Z: "); Serial.println(temp[2]);
  Serial.print(" X: "); Serial.print(temp[3]);
  Serial.print(" Y: "); Serial.print(temp[4]);
  Serial.print(" Z: "); Serial.println(temp[5]);
}

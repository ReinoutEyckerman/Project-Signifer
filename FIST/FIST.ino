const bool debugMode = true;

//const int KnuckleFlat[]= {
//PINS
const int pinBtn = 2;
const int pinFlex = A0;
const int pinTouch = A1;
const int PalmX = A2;
const int PalmY = A3;
const int PalmZ = A4;
const int KnuckleX = A5;
const int KnuckleY = A6;
const int KnuckleZ = A7;
int Knuckle[] = {0,0,0};
int Palm[] = {0,0,0};


void setup() {
  Serial.begin(9600);
}


void loop() {
    Measurements();
    CheckGestures();
    delay(100);
}

void Measurements(){
  Palm[0] = AccelleroConverter(analogRead(PalmX), 0);
  Palm[1] = AccelleroConverter(analogRead(PalmY), 1);
  Palm[2] = AccelleroConverter(analogRead(PalmZ), 2);
  Knuckle[0] = AccelleroConverter(analogRead(KnuckleX), 3);
  Knuckle[1] = AccelleroConverter(analogRead(KnuckleY), 4);
  Knuckle[2] = AccelleroConverter(analogRead(KnuckleZ), 5);
}
int AccelleroConverter(int c, int type)
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
  else if(c>430)
    return 2;
  else 
  {
    if(type>2)
      return Knuckle[type-3];
      else
      return Palm[type];
  }
}
int Flat[]={0,0,1};
int Vertical[]={1,0,0};
int Take[]={0,0,-1};
int Stop[]={0,1,0};
int Verticlap[]={0,0,2};
int Vertispand[]={0,0,-2};
int Horiclap[]={1,0,-2};
int Horispand[]={1,0,2};
int Hai[]={1,0,2};
int Heil[]={-2,-2,0};
int temp[]={0,0,0};

void CheckGestures(){
  if(!ByteArrayCompare(Palm, temp, 3))
  {
    temp[0]=Palm[0];
    temp[1]=Palm[1];
    temp[2]=Palm[2];
      // Serial.println("Flat");
 // SerialDebug();
 if(ByteArrayCompare(Palm, Flat, 3) )
   Serial.println("Flat");
 else if(ByteArrayCompare(Palm, Vertical, 3))
   Serial.println("Vertical");
 else if(ByteArrayCompare(Palm, Take, 3) )
      Serial.println("Take");
 else if(ByteArrayCompare(Palm, Stop, 3) )
    Serial.println("Stop");
else if(ByteArrayCompare(Palm, Verticlap, 3) )
    Serial.println("Verticlap");
    else if(ByteArrayCompare(Palm, Vertispand, 3))
    Serial.println("Vertispand");
else if(ByteArrayCompare(Palm, Horiclap, 3) )
   Serial.println("Horiclap");
 else if(ByteArrayCompare(Palm, Horispand, 3))
    Serial.println("Horispand");
 else if(ByteArrayCompare(Palm, Hai, 3) )
    Serial.println("Hai");
 else if(ByteArrayCompare(Palm, Heil, 3))
     Serial.println("Heil");
  }
}
boolean ByteArrayCompare(int a[],int b[],int array_size)
{
   for (int i = 0; i < array_size; ++i)
     if (a[i] != b[i])
       return(false);
   return(true);
}
void SerialDebug(){

  Serial.print(" X: "); Serial.print(Palm[0]);
  Serial.print(" Y: "); Serial.print(Palm[1]);
  Serial.print(" Z: "); Serial.println(Palm[2]);
    Serial.print(" X: "); Serial.print(temp[0]);
  Serial.print(" Y: "); Serial.print(temp[1]);
  Serial.print(" Z: "); Serial.println(temp[2]);
}

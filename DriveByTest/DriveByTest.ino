#include <Motor.h>
#include <Servo.h>
const int Motor1Pin1 = 3;
const int Motor1Pin2 = 5;
const int Motor2Pin1 = 9;
const int Motor2Pin2 = 10;
const int CommunicatorPin=2;
const int MaxMotorPower = 255;
const int BridgePin=12;
int index = 0;

Motor LinkseMotor(Motor1Pin1,Motor1Pin2);
Motor RechtseMotor(Motor2Pin1,Motor2Pin2);
Servo myservo;
int pos = 0;  

void setup() {
  Serial.begin(9600);
  pinMode(CommunicatorPin, OUTPUT);
  pinMode(BridgePin, OUTPUT);
  myservo.attach(6);
}
int time;

void loop() {
  Vooruit();
  time=millis();
//  if(time>2000)
    digitalWrite(CommunicatorPin, HIGH);
  //digitalWrite(BridgePin, HIGH);
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  Serial.println("t");
}
void Vooruit()
{
     LinkseMotor.DriveForward(150);
     RechtseMotor.DriveForward(150);
}

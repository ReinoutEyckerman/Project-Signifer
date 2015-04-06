#include <Motor.h>
#include <TwoWheelDrive.h>
#include <SharpIRDistance.h>
#include <SensorController.h>

const int LeftDriverForward = 6;
const int LeftDriverBackward = 5;
const int RightDriverForward = 9;
const int RightDriverBackward = 10;
int test=0;
const int LowerSensor1 = A0;
const int LowerSensor2 = A1;
const int TopSensor = A2;

const int BridgeRaise = 10;
const int BridgeLower = 11;

TwoWheelDrive Driver(LeftDriverForward,LeftDriverBackward,RightDriverForward,RightDriverBackward);
SensorController SensorControl(LowerSensor1,LowerSensor2,TopSensor);
Motor BridgeMotor = Motor(BridgeRaise,BridgeLower);
int index = 0;
const int awakePin=3;
const int sleepPin=2;
char val=3;
void setup() {
  Serial.begin(9600);
 pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
 digitalWrite(2,LOW); 
 digitalWrite(3,LOW); 
}
void loop() {

   if( Serial.available() )       // if data is available to read
  {
      val = Serial.read(); 
  int d2 = SensorControl.GetTopDistance();
  Serial.println(val);
  digitalWrite(awakePin,LOW); 
  digitalWrite(sleepPin,LOW); 
  switch(val)
  {
    case '0':
        Driver.Forward();
    break;
    case '1':
        Driver.RotateLeft();
    break;
    case '2':
        Driver.RotateRight();
    break;
    case '3':
        Driver.Stop();
    break;
    case '4':
      ToggleMusic();
    break;
    case '5':
      Serial.println(5);
            Driver.PivotRight();
    break;
  index++;
  delay(1000);
}
const int BridgeRaise = 10;
const int BridgeLower = 11;
Motor BridgeMotor = Motor(BridgeRaise,BridgeLower);
bool bridgeGoingUp = false;

void ToggleBridge(){
   if(bridgeGoingUp)
    BridgeMotor.DriveForward(230);
  else BridgeMotor.DriveBackward(230);
  bridgeGoingUp = !bridgeGoingUp;

  }
int music=0;
void ToggleMusic(){
  if(music==0)
  {
    music=1;
    Awake();
  }  
    music=0;
    Sleep();
}
void Awake(){
 digitalWrite(awakePin,HIGH); 
}
void Sleep(){  
  delay(100);
  digitalWrite(sleepPin, HIGH);
  }

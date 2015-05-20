#include <Servo.h>
#include <Motor.h>
#include <TwoWheelDrive.h>
#include <SharpIRDistance.h>
#include <SensorController.h>
#include <Arduino.h>

const int LeftDriverForward = 10;
const int LeftDriverBackward = 9;
const int RightDriverForward = 5;
const int RightDriverBackward = 6;

const int LowerSensor1 = A0;
const int LowerSensor2 = A1;
const int TopSensor = A2;
const int Servopin = 2;

const int BridgeRaise = 10;
const int BridgeLower = 11;

Servo myser;

bool bridgeGoingUp = false;

TwoWheelDrive Driver(LeftDriverForward, LeftDriverBackward, RightDriverForward, RightDriverBackward);
Motor BridgeMotor = Motor(BridgeRaise, BridgeLower);
SensorController SensorControl(LowerSensor1, LowerSensor2, TopSensor, myser);

String val = "Auto";

//Keep track of every turn we have made so far, right is positive, left is negative. 
int deflection = 0;

int distRightDiag = 0;
int distLeftDiag = 0;
int distBottom = 0;
int distTop = 0;

const int SHOULDREACT = 14;
const int DANGERCLOSE = 7;
const int BRIDGEDIFF = 8;

void setup() {
  myser.attach(Servopin);
  SensorControl.LookStraight();
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  digitalWrite(13, LOW);
  if ( Serial.available() )      // if data is available to read
  {
    val = Serial.readString();
    Serial.println(val);
    digitalWrite(13, HIGH);
  }
  if (val == "Stop")
    Driver.Stop();
  else if (val == "Auto")
    Check();
  else if (val == "Forward")
    Driver.Forward();
  else if (val == "Left")
    Driver.RotateLeft();
  else if (val == "Right")
    Driver.RotateRight();
  else if (val == "Back")
    Driver.Backward();
  else if (val == "Bridge")
    ToggleBridge();
  else Driver.Stop();
  delay(200);
}

void ToggleBridge() {
  if (bridgeGoingUp)
    BridgeMotor.DriveForward(230);
  else BridgeMotor.DriveBackward(230);
  bridgeGoingUp = !bridgeGoingUp;

}

void Check() {
  Measurements();  
  
  //Closer than SHOUDLREACT?
  if(distBottom < SHOULDREACT){
    
    //Is it a bridge?
    if(CheckIsBridge()){
      //Serial.println("Bridge!");
      
      StraightenPerpendicular();
      //Serial.println("Straightened, so forward.");
      
      Driver.Forward();
      return;
    }
    
    //No Bridge, just obstacle.
    else{
      //Serial.println("Obstacle!");
      Driver.Stop();
      return;
    }
    
  }
  else{
    //Serial.println("NOTHING");
    Driver.Forward();
  }
  
/*if (WithinExtremes(SensorControl.GetDistance1(), 15))
    {
      Driver.RotateRight();
      Serial.println("TwitchRight");
      delay(100);
    }
     if (WithinExtremes(SensorControl.GetDistance2(), 15)) {
      Driver.RotateLeft();
      Serial.println("TwitchLeft");
      delay(100);
    }
  if ( !WithinExtremes(distmin, 20)) {
    Driver.Forward();
    Serial.print("Forward at angle: ");
    Serial.println(SensorControl.GetAngle());
    
  } 
  else if(!WithinExtremes(disttop, 30) > !WithinExtremes(7 + distmin, 30))
  {
        Driver.Forward();
    Serial.print("Forward at angle: ");
    Serial.println(SensorControl.GetAngle());
   
  }
 else {
    //  if (WithinExtremes(distmin, 10)) {
    Driver.Stop();
    Serial.println("Stopped");
    if (!Rotate()) {
      while (WithinExtremes(GetLeftDistance(), 15) && WithinExtremes(GetRightDistance(), 15) /* && BACKDISTANCE > 6 ) {
   /*     Driver.Backward();
        Serial.println("Reverse");
        delay(1000);
      }

      if (!WithinExtremes(GetLeftDistance(), 15))
      {
        Driver.RotateLeft();
        delay(2000);
        Serial.println("BackLeft");
      }
      else {
        Driver.RotateRight();
        delay(2000);
        Serial.println("BackRight");
      }
    }
  }*/
}


/*
bool Rotate() {

  if (left) {
    if (!WithinExtremes(GetRightDistance(), 15))
    {
      left = false;
      Driver.RotateRight();
      delay(750);
      Serial.println("Right");
      return true;
    }
    else if (!WithinExtremes(GetLeftDistance(), 15)) {
      left = true;
      Driver.RotateLeft();
      delay(750);
      Serial.println("Left");
      return true;
    }
  }
  else {
    if (!WithinExtremes(GetLeftDistance(), 15))
    {
      left = true;
      Driver.RotateLeft();
      delay(750);
      Serial.println("Left");
      return true;
    }
    else if (!WithinExtremes(GetRightDistance(), 15)) {
      left = false;
      Driver.RotateRight();
      delay(750);
      Serial.println("Right");
      return true;
    }
  }
  return false;
}*/

int GetLeftDistance() {
  SensorControl.LookLeft();
  Serial.print("LookyLeft: ");
  Serial.println(SensorControl.GetTopDistance());
  SensorControl.LookStraight();
  return SensorControl.GetTopDistance();
}

int GetRightDistance() {
  SensorControl.LookRight();
  Serial.print("LookyRight: ");
  Serial.println(SensorControl.GetTopDistance());
  SensorControl.LookStraight();
  return SensorControl.GetTopDistance();

}

void Measurements(){
  distBottom = SensorControl.GetDistanceMin();
  distLeftDiag = SensorControl.GetDiagDistance1();
  distRightDiag = SensorControl.GetDiagDistance2();
  distTop = SensorControl.GetTopDistance();
  
  /*
    Serial.print("LEFT: ");
    Serial.print(distLeftDiag);
    Serial.print(" | RIGHT: ");
    Serial.print(distRightDiag);
    Serial.print(" | TOP: ");
    Serial.println(distTop);
   */
}

bool CheckIsBridge(){
  SensorControl.LookStraight();
  Measurements();
  
  if( distTop > distBottom + BRIDGEDIFF )
    return true;
  else return false;
}

//Sraighten the robot so it's perpendicular to a wall or a bridge.
void StraightenPerpendicular(){
  const int TOLERANCECM = 2;
  
  while(true){
    Measurements();
  
    if(distLeftDiag + TOLERANCECM >= distRightDiag && distLeftDiag - TOLERANCECM <= distRightDiag){
      return;
    }
    else{
      if(distLeftDiag > distRightDiag){
        Driver.RotateLeft();
        Serial.println("Straightening LEFT");
        delay(100);
      }
      else{
        Driver.RotateRight();
        Serial.println("Straightening RIGHT");
        delay(100);
      }
  }
  
  }  
}
  

#include <Servo.h>
#include <Motor.h>
#include <TwoWheelDrive.h>
#include <SharpIRDistance.h>
#include <SensorController.h>
#include <Arduino.h>

const int LeftDriverForward = 5;
const int LeftDriverBackward = 6;
const int RightDriverForward = 10;
const int RightDriverBackward = 9;

const int LowerSensor1 = A0;
const int LowerSensor2 = A1;
const int TopSensor = A2;
const int Servopin = 2;

const int BridgeRaise = 10;
const int BridgeLower = 11;

Servo myser;

bool left;
bool bridgeGoingUp = false;

TwoWheelDrive Driver(LeftDriverForward, LeftDriverBackward, RightDriverForward, RightDriverBackward);
Motor BridgeMotor = Motor(BridgeRaise, BridgeLower);
SensorController SensorControl(LowerSensor1, LowerSensor2, TopSensor, myser);

String val = "None";

void setup() {
  myser.attach(Servopin);
  SensorControl.LookStraight();
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {

  if ( Serial.available() )      // if data is available to read
  {
    val = Serial.readString();
  }
  if (val == "None")
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
  delay(200);
}

void ToggleBridge() {
  if (bridgeGoingUp)
    BridgeMotor.DriveForward(230);
  else BridgeMotor.DriveBackward(230);
  bridgeGoingUp = !bridgeGoingUp;

}

void Check() {

  int distmin = SensorControl.GetDistanceMin();
  Serial.println(distmin);
  Serial.println(SensorControl.GetTopDistance());
  if ( !WithinExtremes(SensorControl.GetTopDistance(), 20) /*&& SensorControl.GetAngle() < 48*/) {
    Driver.Forward();
    Serial.print("Forward at angle: ");
    Serial.println(SensorControl.GetAngle());
  } else {

    //  if (WithinExtremes(distmin, 10)) {
    Driver.Stop();
    Serial.println("Stopped");
    if (!Rotate()) {
      while (WithinExtremes(GetLeftDistance(), 10) && WithinExtremes(GetRightDistance(), 10) /* && BACKDISTANCE > 6 */) {
        Driver.Backward();
        Serial.println("Reverse");
        delay(1000);
      }

      if (!WithinExtremes(GetLeftDistance(), 10))
      {
        Driver.RotateLeft();
        delay(2000);
        Serial.println("BackLeft");
      }
      else {
        Driver.RotateRight();
        delay(2000);
        Serial.println("BackRight");
        //    }
      }
    }
  }
}


bool Rotate() {
  /*if (!WithinExtremes(SensorControl.GetDistance1(), 5))
  {
    Driver.RotateRight();
    delay(100);
  }
  else if (!WithinExtremes(SensorControl.GetDistance2(), 5)) {
    Driver.RotateLeft();
    delay(100);
  }*/
  if (left) {
    if (!WithinExtremes(GetRightDistance(), 10))
    {
      left = false;
      Driver.RotateRight();
      delay(750);
      Serial.println("Right");
      return true;
    }
    else if (!WithinExtremes(GetLeftDistance(), 10)) {
      left = true;
      Driver.RotateLeft();
      delay(750);
      Serial.println("Left");
      return true;
    }
  }
  else {
    if (!WithinExtremes(GetLeftDistance(), 10))
    {
      left = true;
      Driver.RotateLeft();
      delay(750);
      Serial.println("Left");
      return true;
    }
    else if (!WithinExtremes(GetRightDistance(), 10)) {
      left = false;
      Driver.RotateRight();
      delay(750);
      Serial.println("Right");
      return true;
    }
  }
  return false;
}

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

bool WithinExtremes(int value, int extreme) {
  if (value > 0 && value <= extreme)
    return true;
  return false;
}

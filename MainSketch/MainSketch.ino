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
bool left = false;

//Keep track of every turn we have made so far, right is positive, left is negative.
int deflection = 0;

int distRight = 0;
int distLeft = 0;
int distRightDiag = 0;
int distLeftDiag = 0;
int distBottom = 0;
int distTop = 0;
int distAt0 = 0;
int distAt180 = 0;

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
  if (distBottom < SHOULDREACT) {

    //Is it a bridge?
    if (CheckIsBridge()) {
      //Serial.println("Bridge!");

      StraightenPerpendicular();
      //Serial.println("Straightened, so forward.");

      Driver.Forward();
      return;
    }

    //No Bridge, just obstacle.
    else {
      //Serial.println("Obstacle!");

      RotateForObstacle();
    }
  }
  else {
    Driver.Forward();
  }
}

void Measurements() {
  distBottom = SensorControl.GetDistanceMin();
  distLeft = SensorControl.GetDistance1();
  distRight = SensorControl.GetDistance2();
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

void SideMeasurements() {
  distAt0 = SensorControl.GetTopAtAngle(0);
  distAt180 = SensorControl.GetTopAtAngle(180);
  SensorControl.LookStraight();
}

bool CheckIsBridge() {
  SensorControl.LookStraight();
  Measurements();

  if ( distTop > distBottom + BRIDGEDIFF )
    return true;
  else return false;
}

//Sraighten the robot so it's perpendicular to a wall or a bridge.
void StraightenPerpendicular() {
  const int TOLERANCECM = 2;

  while (true) {
    Measurements();

    if (distLeft + TOLERANCECM >= distRight && distLeft - TOLERANCECM <= distRight) {
      return;
    }
    else {
      if (distLeft > distRight) {
        Driver.RotateLeft();
        Serial.println("Straightening LEFT");
        delay(100);
      }
      else {
        Driver.RotateRight();
        Serial.println("Straightening RIGHT");
        delay(100);
      }
    }

  }
}

void RotateForObstacle() {
  while (distBottom < SHOULDREACT) {
    Driver.Stop();
    SideMeasurements();

    if (distAt0 < DANGERCLOSE && distAt180 < DANGERCLOSE) {
      Serial.println("LOCKDOWN");
      while (true) {};
    }
    //NO SPACE ON LEFT, but space on right.
    else if (distAt0 < DANGERCLOSE && distAt180 > DANGERCLOSE) {
      Driver.RotateRight();
      deflection += 1;
      delay(500);
    }
    //NO SPACE ON RIGHT but space on left.
    else if (distAt180 < DANGERCLOSE && distAt0 > DANGERCLOSE) {
      Driver.RotateLeft();
      deflection -= 1;
      delay(500);
    }
    //More space on Right than on left.
    else if (distAt180 > distAt0) {
      Driver.RotateRight();
      deflection += 1;
      delay(500);
    }
    else if (distAt0 > distAt180) {
      Driver.RotateLeft();
      deflection -= 1;
      delay(500);
    }

    //Re-check for forward space.
    Measurements();
  }
}


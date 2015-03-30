#include <Motor.h>
#include <TwoWheelDrive.h>
#include <SharpIRDistance.h>
#include <SensorController.h>

const int LeftDriverForward = 6;
const int LeftDriverBackward = 5;
const int RightDriverForward = 9;
const int RightDriverBackward = 10;

const int LowerSensor1 = A0;
const int LowerSensor2 = A1;
const int TopSensor = A2;

const int BridgeRaise = 10;
const int BridgeLower = 11;

TwoWheelDrive Driver(LeftDriverForward,LeftDriverBackward,RightDriverForward,RightDriverBackward);
SensorController SensorControl(LowerSensor1,LowerSensor2,TopSensor);
Motor BridgeMotor = Motor(BridgeRaise,BridgeLower);

int index = 0;
bool bridgeGoingUp = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Drive
  Driver.Forward();
  
  //Sensors
  int d1 = SensorControl.GetCrossDistance();
  int d2 = SensorControl.GetTopDistance();
  
  Serial.print("Lower Sensor:");
  Serial.print(d1);
  Serial.print("| Upper Sensor:");
  Serial.println(d2);
  
  //Bridge
  if(bridgeGoingUp)
    BridgeMotor.DriveForward(230);
  else BridgeMotor.DriveBackward(230);
  
  bridgeGoingUp = !bridgeGoingUp;
  
  delay(1500);
}

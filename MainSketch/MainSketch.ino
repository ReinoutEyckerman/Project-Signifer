#include <Motor.h>
#include <TwoWheelDrive.h>
#include <SharpIRDistance.h>
#include <SensorController.h>

const int LeftDriverForward = 5;
const int LeftDriverBackward = 6;
const int RightDriverForward = 9;
const int RightDriverBackward = 10;

const int LowerSensor1 = A0;
const int LowerSensor2 = A1;
const int TopSensor = A2;

TwoWheelDrive Driver(LeftDriverForward,LeftDriverBackward,RightDriverForward,RightDriverBackward);
SensorController SensorControl(LowerSensor1,LowerSensor2,TopSensor);

int index = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Driver.Forward();
  int d1 = SensorControl.GetCrossDistance();
  int d2 = SensorControl.GetTopDistance();
  
  Serial.print("Lower Sensor:");
  Serial.print(d1);
  Serial.print("| Upper Sensor:");
  Serial.println(d2);
  
  if (index % 5 == 0) {
    //Driver.Forward();
  }
  else if (index % 5 == 1) {
    //Driver.PivotLeft();
  }
  else if (index % 5 == 2) {
    //Driver.RotateLeft();
  }
  else if(index %5 == 3){
    //Driver.Stop();
  }
  else if (index % 5 == 4){
    //Driver.RotateRight();
  }
  else{
    //Driver.PivotRight();
  }
  //index++;
  //delay(3000);
}

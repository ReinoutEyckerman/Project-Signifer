#include <Motor.h>
#include <TwoWheelDrive.h>

const int LeftDriverForward = 3;
const int LeftDriverBackward = 5;
const int RightDriverForward = 9;
const int RightDriverBackward = 10;

TwoWheelDrive Driver(LeftDriverForward,LeftDriverBackward,RightDriverForward,RightDriverBackward);

int index = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if (index % 5 == 0) {
    Driver.Forward();
  }
  else if (index % 5 == 1) {
    Driver.PivotLeft();
  }
  else if (index % 5 == 2) {
    Driver.RotateLeft();
  }
  else if(index %5 == 3){
    Driver.Stop();
  }
  else if (index % 5 == 4){
    Driver.RotateRight();
  }
  else{
    Driver.PivotRight();
  }
  index++;
  delay(3000);
}

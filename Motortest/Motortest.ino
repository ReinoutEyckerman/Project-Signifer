#include <Motor.h>
 
const int Motor1Pin1 = 3;
const int Motor1Pin2 = 5;
const int Motor2Pin1 = 9;
const int Motor2Pin2 = 10;

const int MaxMotorPower = 255;

int index = 0;

Motor LinkseMotor(Motor1Pin1,Motor1Pin2);
Motor RechtseMotor(Motor2Pin1,Motor2Pin2);
void setup() {
  Serial.begin(9600); //Voor debugging
}


void loop() {
  if (index % 5 == 0) {
     LinkseMotor.DriveForward(150);
     RechtseMotor.DriveForward(150);
    Serial.println("VOORUIT");
  }
  else if (index % 5 == 1) {
   LinkseMotor.DriveForward(150);
   RechtseMotor.Stop();
    Serial.println("LINKS VOORUIT");
  }
  else if (index % 5 == 2) {
    LinkseMotor.Stop();
    RechtseMotor.DriveBackward(150);
    Serial.println("RECHTS ACHTERUIT");
  }
  else if(index %5 == 3){
    LinkseMotor.DriveBackward(150);
    RechtseMotor.Stop();
    Serial.println("LINKSE ACHTERUIT");
  }
  else if (index % 5 == 4){
    LinkseMotor.Stop();
    RechtseMotor.DriveForward(150);
    Serial.println("RECHTS VOORUIT");
  }
  else{
    LinkseMotor.Stop();
    Serial.println("FULL STOP");
  }
  index++;
  delay(3000);
}

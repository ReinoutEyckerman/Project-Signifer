//De Servo code zordt momenteel niet gebruikt
#include <Motor.h>  //De Library definiëringen
const int Motor1Pin1 = 3; // Motorpinaanduidingen
const int Motor1Pin2 = 5;
const int Motor2Pin1 = 9;
const int Motor2Pin2 = 10;
const int MaxMotorPower = 255; //Maximale motorkracht

Motor LinkseMotor(Motor1Pin1,Motor1Pin2); //De motordefinëring
Motor RechtseMotor(Motor2Pin1,Motor2Pin2);

void setup() {
}

void loop() {
     LinkseMotor.DriveForward(250); //Het rijden zelf
     RechtseMotor.DriveForward(250); 
}


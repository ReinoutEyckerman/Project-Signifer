#include <Motor.h>
#include <TwoWheelDrive.h>

const int LeftDriverForward = 5;
const int LeftDriverBackward = 6;
const int RightDriverForward = 9;
const int RightDriverBackward = 10;
int test=0;

TwoWheelDrive Driver(LeftDriverForward,LeftDriverBackward,RightDriverForward,RightDriverBackward);

int index = 0;
const int awakePin=3;
const int sleepPin=2;
void setup() {
  Serial.begin(9600);
 pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
 digitalWrite(2,LOW); 
 digitalWrite(3,LOW); 

}

void loop() {
//  for(;;){
 // if (Serial.available())
  //  Serial.write(3);
 // }
  digitalWrite(awakePin,LOW); 
 digitalWrite(sleepPin,LOW); 

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
  delay(10000);
  if(test==0)
  {
    test=1;
    Serial.println("test");
    Awake();
    }
   else{
   test=0;
       Serial.println("test1");
   Sleep();
   }
}
void Awake(){
 digitalWrite(awakePin,HIGH); 
}
void Sleep(){  
  delay(100);
  digitalWrite(sleepPin, HIGH);
  }

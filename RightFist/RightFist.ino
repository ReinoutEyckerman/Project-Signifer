#include <FIST.h>
//setup
void setup() {
  Serial.begin(9600);
}

//Define fist
FIST fist(A2, A0, A1, A3, A4, A5, 'r', 13);
//loop
void loop() {
  fist.Run();
  //fist.SerialDebug();
  delay(200);
}  

#include <FIST.h>
//setup
void setup() {
  Serial.begin(9600);
}
//Define Fist
FIST fist(A0, A1, A2, A3, A4, A5, 'l', -1);
//loop
void loop() {
  fist.Run();
  
  //fist.SerialDebug();
  delay(500);
}  

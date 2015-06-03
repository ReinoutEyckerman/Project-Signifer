#include <FIST.h>
//setup
void setup() {
  Serial.begin(9600);
}
//Define Fist
FIST fist( A3, A4, A5,A0, A1, A2, 'l', -1);
//loop
void loop() {
  fist.Run();
  
  //fist.SerialDebug();
  delay(200);
}  

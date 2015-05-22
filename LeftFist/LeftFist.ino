#include <FIST.h>
void setup() {
  Serial.begin(9600);
}
FIST fist(A0, A1, A2, A3, A4, A5, 'l', -1);
void loop() {
  fist.Run();
  //fist.SerialDebug();
  delay(2000);
}  

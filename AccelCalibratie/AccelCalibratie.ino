//Pinbindings, aanpassen na test.

int X1 = A0;
int Y1 = A1;
int Z1 = A2;
int X2 = A3;
int Y2 = A4;
int Z2 = A5;

//RESULTS 18-05-2015:
// 

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  int m1 = analogRead(X1);
  int m2 = analogRead(Y1);
  int m3 = analogRead(Z1);
  int m4 = analogRead(X2);
  int m5 = analogRead(Y2);
  int m6 = analogRead(Z2);
  
  Serial.print("1:");
  Serial.print(" X: ");
  Serial.print(m1);
  Serial.print(" Y: ");
  Serial.print(m2);
  Serial.print(" Z: ");
  Serial.print(m3);
  
  Serial.print(" | 2: ");
  Serial.print(" X: ");
  Serial.print(m4);
  Serial.print(" Y: ");
  Serial.print(m5);
  Serial.print(" Z: ");
  Serial.println(m6);
  
  delay(1000);

}

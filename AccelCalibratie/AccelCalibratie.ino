//Pinbindings, aanpassen na test.

int X1 = A0;
int Y1 = A1;
int Z1 = A2;
int X2 = A3;
int Y2 = A4;
int Z2 = A5;

//RESULTS 18-05-2015 RECHTSE HAND
// PLAT:           1 0 0 1 0 0   
// KANTEL RECHTS:  0 0 0 0 0 0  
// ONDERSTEBOVEN:  0 1 1 0 0 1
// OMHOOG:         0 -1 1 -1 -1 -1
// BENEDEN:        0 0 1 0 1 1

// FIST PLAT:           1 0 0 0 1 1
// FIST KANTEL RECHTS:  0 0 0 0 0 0
// FIST ONDERSTEBOVEN:  0 0 1 0 0 1
// FIST OMHOOG:         0 -1 0 1 0 0
// FIST BENEDEN:        0 1 1 0 1 1

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

  int c1 = AcceleroConvert(m1);
  int c2 = AcceleroConvert(m2);
  int c3 = AcceleroConvert(m3);
  int c4 = AcceleroConvert(m4);
  int c5 = AcceleroConvert(m5);
  int c6 = AcceleroConvert(m6);

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
  Serial.print(m6);





  Serial.print(" | C1:");
  Serial.print(" X: ");
  Serial.print(c1);
  Serial.print(" Y: ");
  Serial.print(c2);
  Serial.print(" Z: ");
  Serial.print(c3);

  Serial.print(" | C2: ");
  Serial.print(" X: ");
  Serial.print(c4);
  Serial.print(" Y: ");
  Serial.print(c5);
  Serial.print(" Z: ");
  Serial.println(c6);

  delay(1000);

}

int AcceleroConvert(int c) {
  if (c < 285)
    return -1;
  else if (c > 285 && c < 385)
    return 0;
  else if (c > 385)
    return 1;
  else return 2;
}


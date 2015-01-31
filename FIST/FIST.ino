const bool debugMode = true;

//PINS
const int pinBtn = 2;
const int pinFlex = A0;
const int pinTouch = A1;
const int pinAccX = A2;
const int pinAccY = A3;
const int pinAccZ = A4;

//MEASUREMENTS
int msFlex;    //670-680 straight, 720-730 45°, 810-820 90°, Max 900
int msTouch;   //650-660 unpressed, 900-1000 pressed on pin side, 480-490 pressed mid, near zero pressed end.
int msAccX;    //330-340 flat, 260/400 static tilted to X side.
int msAccY;    //330-340 flat, 260/400 static tilted to Y side.
int msAccZ;    //330 when tilted 90°,400 when flat on board, 260 upside down.
bool msButton; //0 when pressed, 1 when not pressed.

//STATES
volatile bool stAuto = false;

void setup() {
  Serial.begin(9600);
  pinMode(pinBtn,INPUT_PULLUP);
  attachInterrupt(0, buttonPress, FALLING);
}

void buttonPress(){
  Serial.println("M"); //Mode
  stAuto = !stAuto;
}

void loop() {
  if(!stAuto){
    Measurements();
    SerialCommands();
  }
  
  if(debugMode){
    SerialDebug();
    delay(1000);
  }
}

void Measurements(){
  msButton = digitalRead(pinBtn);
  msFlex = analogRead(pinFlex);
  msTouch = analogRead(pinTouch);
  msAccX = analogRead(pinAccX);
  msAccY = analogRead(pinAccY);
  msAccZ = analogRead(pinAccZ);
}

void SerialDebug(){
  Serial.print("Btn: "); Serial.print(msButton);
  Serial.print(" | Flex: "); Serial.print(msFlex);
  Serial.print(" | Touch: "); Serial.print(msTouch);
  Serial.print(" | X: "); Serial.print(msAccX);
  Serial.print(" Y: "); Serial.print(msAccY);
  Serial.print(" Z: "); Serial.println(msAccZ);
}

void SerialCommands(){
  if(msFlex > 700){
    Serial.print("S");Serial.println(msFlex);} //Speed x
    
  if(msTouch < 400){
    Serial.println("BL");} //Bridge Lower
  else if(msTouch > 800){
    Serial.println("BR");} //Bridge Raise
}

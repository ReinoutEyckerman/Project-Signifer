/*




        INPUT:
        OUTPUT:

	Created 12/11/14
	By Oliver Hofkens
*/

const int greenLed = 2;
const int yellowLed = 3;
const int redLed = 4;
const int button = 5;

const int infraRedDist = 0;

const int MaxDistance = 30;
const int MinDistance = 6;

bool backwards;
int distanceCentimeters;
bool greenLedState;
bool redLedState;

bool yellowLedState;
int yellowLedMilliDelay;
bool yellowLedBlinkEvent;
bool yellowLedBlinkState;

int previousTime = 0;
int blinkTimer = 0;
int debugTimer = 0;

int previousButtonState;

void setup() {
  Serial.begin(9600); //Seriele communicatie voor debugging.
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  CheckTiming();
  CheckButton();

  if (backwards) {
    ReadDistanceSensorCentimeter();
    HandleLedStates();
  }
}

void CheckTiming() {
  int currentTime = millis();
  int passedTime = currentTime - previousTime;
  previousTime = currentTime;

  blinkTimer += passedTime;
  debugTimer += passedTime;

  if (debugTimer > 100) {
    WriteSerialDebug();
    debugTimer = 0;
  }

  if (yellowLedState && blinkTimer > yellowLedMilliDelay) {
    yellowLedBlinkEvent = true;
    blinkTimer = 0;
  }
  else {
    yellowLedBlinkEvent = false;
  }
}

void ReadDistanceSensorCentimeter()
{
  int analogDistance = analogRead(infraRedDist);
  distanceCentimeters = 2076 / (analogDistance - 11);
}

void CheckButton() {
  int buttonState = digitalRead(button);
  if (buttonState == HIGH && previousButtonState == LOW) {
    backwards = !backwards;
  }
  previousButtonState = buttonState;
}

void WriteSerialDebug() {
  if (backwards) {
    Serial.print("dist: ");
    Serial.print(distanceCentimeters);
    Serial.print("| green: ");
    Serial.print(greenLedState);
    Serial.print("| yellow: ");
    Serial.print(yellowLedState);
    Serial.print(" with period of ");
    Serial.print(yellowLedMilliDelay);
    Serial.print("| red: ");
    Serial.println(redLedState);
  }
  else {
    Serial.println("Going forward");
  }
}

void HandleLedStates() {
  if (distanceCentimeters <= MinDistance) {
    ToggleLedState(redLed);
  }
  else if (distanceCentimeters > MinDistance && distanceCentimeters < MaxDistance) {
    ToggleLedState(yellowLed);
  }
  else {
    ToggleLedState(greenLed);
  }
}

void ToggleLedState(int ledPin) {
  StateReset();

  switch (ledPin) {
    case greenLed:
      greenLedState = true;
      break;
    case yellowLed:
      yellowLedState = true;
      break;
    case redLed:
      redLedState = true;
      break;
  }
  
  digitalWrite(greenLed, greenLedState);
  digitalWrite(redLed, redLedState);
  HandleYellowLed();
}

void StateReset() {
  greenLedState = false;
  yellowLedState = false;
  redLedState = false;
}

void HandleYellowLed() {
  if (yellowLedState) {
    yellowLedMilliDelay = distanceCentimeters * 10;

    if (yellowLedBlinkEvent) {
      yellowLedBlinkState = !yellowLedBlinkState;
      digitalWrite(yellowLed, yellowLedBlinkState);
    }
  }
  else(digitalWrite(yellowLed, LOW));
}

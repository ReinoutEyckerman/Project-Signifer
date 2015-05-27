#include <Servo.h>
#include <Motor.h>
#include <TwoWheelDrive.h>
#include <SharpIRDistance.h>
#include <SensorController.h>
#include <Arduino.h>

/***************
 *  PINS
 ***************/
const int LeftDriverForward = 10;
const int LeftDriverBackward = 9;
const int RightDriverForward = 5;
const int RightDriverBackward = 6;

const int LowerSensor1 = A0;
const int LowerSensor2 = A1;
const int TopSensor = A2;
const int Servopin = 2;

const int BridgeRaise = 10;
const int BridgeLower = 11;

/***************
 *  OBJECTS
 ***************/
Servo myser;
TwoWheelDrive Driver(LeftDriverForward, LeftDriverBackward, RightDriverForward, RightDriverBackward);
Motor BridgeMotor = Motor(BridgeRaise, BridgeLower);
SensorController SensorControl(LowerSensor1, LowerSensor2, TopSensor, myser);

/**************
 *  SETTINGS
 **************/
 
//dit is het commando dat de F.I.S.T. doorgeeft aan de arduino.
String val = "Auto";

//Instelbare afstanden voor het algoritme
const int SHOULDREACT = 14;
const int DANGERCLOSE = 7;
const int BRIDGEDIFF = 8;

/*************
 *  GLOBALS
 *************/

bool bridgeGoingUp = false;

int deflection = 0;       // Keep track of every turn made. in 100ms steps. positive is right, negative is left.
int localDeflection = 0;  // Local deflection so we can commit to 1 direction, instead of twitching.

int distRight = 0;        //BOTTOM RIGHT CALC
int distLeft = 0;         //BOTTOM LEFT CALC
int distBottom = 0;       //BOTTOM SHORTEST
int distTop = 0;          //TOP DISTANCE
int distAt0 = 0;          //TOP DISTANCE RIGHT SIDE
int distAt45 = 0;         //TOP DSISTANCE RIGHT 45
int distAt135 = 0;        //TOP DISTANCE LEFT 45
int distAt180 = 0;        //TOP DISTANCE LEFT SIDE

/*******************
 *  SETUP & LOOP
 *******************/

void setup() {
  myser.attach(Servopin);
  SensorControl.LookStraight();
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  digitalWrite(13, LOW);
  if ( Serial.available() )      // if data is available to read
  {
    val = Serial.readString();
    Serial.println(val);
  }
  if (val == "Stop")
    Driver.Stop();
  else if (val == "Auto")
    AutonomousMove();
  else if (val == "Forward")
    Driver.Forward();
  else if (val == "Left"){
    Driver.RotateLeft();
    delay(300);
    val="Stop";
  }
  else if (val == "Right"){
    Driver.RotateRight();
    delay(300);
    val="Stop";
  }
    
  else if (val == "Back")
    Driver.Backward();
  else if (val == "Bridge")
    ToggleBridge();
  else Driver.Stop();
  delay(200);
}

/***********************
 *  MOVEMENT ALGORITHM
 ***********************/

void AutonomousMove() {
  Measurements();

  // Closer than SHOUDLREACT?
  if (distBottom < SHOULDREACT || distTop < SHOULDREACT) {

    // In case of bridge
    if (CheckIsBridge()) {
      StraightenPerpendicular();
      Driver.Forward();
      return;
    }

    //No Bridge, so obstacle
    else {
      AvoidObstacle();
    }
  }
  
  //Further than SHOULDREACT
  else {
    Driver.Forward();
  }
}


//Recursive obstacle avoidance algorithm by Oliver
void AvoidObstacle() {
  
  localDeflection = 0; // Reset local deflection, so we can commit to a certain direction.
  Serial.println("Reset preference");
  
  // While the obstacle is in front of us.
  while (distBottom < SHOULDREACT) {
    Driver.Stop();
    SideMeasurements();

    // Walls very close on both sides.
    if (distAt180 < DANGERCLOSE && distAt0 < DANGERCLOSE) {
      Serial.println("LOCKDOWN");
      Driver.Backward();
      delay(500);
    }
    
    // No space on left side, but space on right side.
    else if ((distAt180 < DANGERCLOSE || distAt135 < DANGERCLOSE) && distAt0 > DANGERCLOSE) {
      GoRight(5);
      Serial.println("DANGER LEFT");
    }
    
    // No space on right side, but space on left side.
    else if ((distAt0 < DANGERCLOSE || distAt45 < DANGERCLOSE) && distAt180 > DANGERCLOSE) {
      GoLeft(5);
      Serial.println("DANGER RIGHT");
    }
    
    // More space on right side than on left side.
    else if (distAt0 > distAt180 || distAt0 > distAt135) {
      
      // We've been going right already, so continue.
      if(localDeflection > 0){
        GoRight(5);
        Serial.println("Continue right");
      }
      
      // Overall, we've made more left turns already, so chances are we need to go right now.
      else if(deflection <= 0){
        GoRight(5);
        Serial.println("Guess right");
      }
      
      else{
        GoRight(3);
        Serial.println("Right because space");
      }
    }
    
    // More space on left side than on right side.
    else if (distAt180 > distAt0 || distAt180 > distAt45) {
      
      // We've been going left already, so continue.
      if(localDeflection < 0){
        GoLeft(5);
        Serial.println("Continue left");
      }
      
      // Overall, we've made more right turns already, so chances are we need to go left now.
      else if(deflection >= 0){
        GoLeft(5);
        Serial.println("Guess left");
      }
      
      else {
        GoLeft(3);
        Serial.println("Left because space");
      }
    }
    
    // Both sides have the same amount of space. 
    else{
      
      // We've been going left already, so continue.
      if(localDeflection < 0){
          GoLeft(5);
          Serial.println("Continue Left");
      }
      
      // We've been going right already, so continue. 
      else if (localDeflection > 0){
        GoRight(5);
        Serial.println("Continue Right");
      }
      
      //Overall more left turns made, or completely equal, so we guess for a right turn now.
      else if(deflection <= 0){
        GoRight(5);
        Serial.println("Guess Right");
      }
      
      //Overall more right turns made, so we guess for a left turn now.
      else if(deflection > 0){
        GoLeft(5);
        Serial.println("Guess Left");
      }
    }

    //Re-check for forward space.
    Measurements();
  }
}

void Measurements() {
  distBottom = SensorControl.GetDistanceMin();
  distLeft = SensorControl.GetDistance1();
  distRight = SensorControl.GetDistance2();
  distTop = SensorControl.GetTopDistance();

 /*
    Serial.print("LEFT: ");
    Serial.print(distLeft);
    Serial.print(" | RIGHT: ");
    Serial.print(distRight);
    Serial.print(" | TOP: ");
    Serial.println(distTop);
   */
}

void SideMeasurements() {
  distAt0 = SensorControl.GetTopAtAngle(0);
  distAt45 = SensorControl.GetTopAtAngle(45);
  distAt135 = SensorControl.GetTopAtAngle(135);
  distAt180 = SensorControl.GetTopAtAngle(180);
  SensorControl.LookStraight();
  
  
  Serial.print("LEFT:");
  Serial.print(distAt0);
  Serial.print(" | RIGHT:");
  Serial.println(distAt180);
  
}

bool CheckIsBridge() {
  SensorControl.LookStraight();
  Measurements();

  if ( distTop > distBottom + BRIDGEDIFF )
    return true;
  else return false;
}

//Sraighten the robot so it's perpendicular to a wall or a bridge.
void StraightenPerpendicular() {
  const int TOLERANCECM = 2;

  while (true) {
    Measurements();

    if (distLeft + TOLERANCECM >= distRight && distLeft - TOLERANCECM <= distRight) {
      return;
    }
    else {
      if (distLeft > distRight) {
        GoLeft(1);
      }
      else {
        GoRight(1);
      }
    }

  }
}

void GoRight(int steps) {
  Driver.RotateRight();
  delay(100 * steps);

  deflection += steps;
  localDeflection += steps;
}

void GoLeft(int steps) {
  Driver.RotateLeft();
  delay(100 * steps);

  deflection -= steps;
  localDeflection -= steps;
}

/**********************
 * VARIOUS FUNCTIONS
 **********************/

void ToggleBridge() {
  if (bridgeGoingUp)
    BridgeMotor.DriveForward(230);
  else BridgeMotor.DriveBackward(230);
  bridgeGoingUp = !bridgeGoingUp;
}


//*** The purpose of this code is test basic funcitions that will be used later
//***   in more complicated applications. We will be writing basic move 
//***   funtions and functions that will hold each arm in a given position.
//***   We will also define maximum position constants for each arm/pot.
//***
//*** For potentiometer conventions, each will be set up left to right as 
//***   high, out, low from the orientation where the pot's prongs are
//***   straight up and we are looking at it's smooth face. 
//***
//*** There are 0.293 degrees per point of potentiometer output.

#include <Servo.h>
#include "ServoFunc.h"
#include "Arm1.h"

//*** Constants ***

const int posDelta = 50;

const int Pot1Max = 907 - posDelta;
const int Pot1Min = 132 + posDelta;
const int Pot2Max = 900 - posDelta;
const int Pot2Min = 125 + posDelta;
const int Pot3Max = 1023 - posDelta;
const int Pot3Min = 102 + posDelta;


//*** Variables ***

int ControlPotPin = A0;
int Pot1Pin = A1;
//int Pot2Pin = A2;
int Pot3Pin = A3;

int ControlPotPos = analogRead(ControlPotPin);

int Servo1Pin = 2;
int Servo2Pin = 3;
int Servo3Pin = 4;

Servo Servo1;
Servo Servo2;
Servo Servo3;

//*** Servo Class Instantiations ***

CServo cServo1 = { Servo1, Pot1Max, Pot1Min, Pot1Pin, true };
CServo cServo2 = { Servo2, Pot1Max, Pot1Min, Pot1Pin, false };
CServo cServo3 = { Servo3, Pot3Max, Pot3Min, Pot3Pin, false };


void setup() {

//*** Beginning Serial Communication Through USB ***

  Serial.begin(9600);

//*** Attaching Servos ***

Servo1.attach(Servo1Pin);
Servo2.attach(Servo2Pin);
Servo3.attach(Servo3Pin);

delay(3000);

}

void loop() {

  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  // delay(500);

 // cServo1.MoveServoWithPot( ControlPotPin);
 //cServo2.MoveServoWithPot( ControlPotPin);
// cServo3.MoveServoWithPot( ControlPotPin);

while(!cServo2.MoveToPos( 450 ));

Serial.println("DELAY 1");
//delay(5000);
Serial.println("Thing1!");

while(!cServo2.MoveToPos( 650 ));

//delay(5000);
Serial.println("Thing2!");
 
}



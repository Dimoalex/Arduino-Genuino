#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define MAX_SPEED 150 // 
#define MOTORS_CALIBRATION_OFFSET 3

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

String motorSet = "";
int speedSet = 0;

Adafruit_DCMotor *leftMotor= AFMS.getMotor(1); 
Adafruit_DCMotor *rightMotor= AFMS.getMotor(2); 

void setup() {
  Serial.begin(9600);
  motorSet = "FORWARD";  
  moveForward();
   AFMS.begin();

}

void loop() {
 
rcTank();


}


void moveStop() {
  leftMotor->run(RELEASE); rightMotor->run(RELEASE);
  }

void moveForward() {
    motorSet = "FORWARD";
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2){
    leftMotor->setSpeed(speedSet+MOTORS_CALIBRATION_OFFSET);
    rightMotor->setSpeed(speedSet);
    delay(5);
  }
}

void moveBackward() {
    motorSet = "BACKWARD";
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2){
    leftMotor->setSpeed(speedSet+MOTORS_CALIBRATION_OFFSET);
    rightMotor->setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motorSet = "RIGHT";
  leftMotor->run(FORWARD);
  rightMotor->run(BACKWARD);
  delay(400);
  motorSet = "FORWARD";
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);      
}  

void turnLeft() {
  motorSet = "LEFT";
  leftMotor->run(BACKWARD);
  rightMotor->run(FORWARD);
  delay(400);
  motorSet = "FORWARD";
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}  

void rcTank(){

  if (Serial.available()){

    int data = Serial.read();
    switch (data) {
      case 'f': 
      moveForward();
//      Serial.println("Forward");
      
      break;
      case 'b' : 
      moveBackward();
//      Serial.println("Backward");
      
      break;
      case 'l' :
      turnLeft();
//      Serial.println("Left");

      break;
      case 'r' : 
      turnRight();
//      Serial.println("Right");
 
      break;
      case 's':
      moveStop();
     
//      Serial.println("Stop");
      default : break;


     }
   }
 }

/* Sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
*/
#include <Wire.h>
#include <Adafruit_MotorShield.h>
int trigPin = 3;// Ultrasonic Module HC-SR04 on Pin 3

int echoPin = 2; //Ultrasonic Module HC-SR04 on Pin 2



Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *motor1= AFMS.getMotor(1); 
Adafruit_DCMotor *motor2= AFMS.getMotor(2);  

void setup()
{
  Serial.begin (9600);
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  AFMS.begin();
  
  // Defines motors speed
  motor1->setSpeed(255); 
  motor2->setSpeed(255); 
  
  // Turn off the motors
  motor1->run(RELEASE); 
  motor2->run(RELEASE);
  delay(300);
}
 
void loop(){

  staticSensor();
  
 }


void staticSensor(){
    int duration, distance; // Duration used to calculate distance
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, HIGH); 
 delayMicroseconds(10); 

 digitalWrite(trigPin, LOW);
  
 duration = pulseIn(echoPin, HIGH);
 
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = (duration/2)/29.1;
 
 
 /*Serial.println(distance);
 Serial.println( " cm");*/
  
  // Turn the motor 1 and 2 clockwise
  motor1->run(FORWARD); 
  motor2->run(FORWARD);
  
 if(distance<26){
  //Turn off the motors
  motor1->run(RELEASE); 
  motor2->run(RELEASE);   
  delay(500);   
  motor1->run(BACKWARD);
  motor2->run(BACKWARD); 
    // Wait 5 seconds
  delay(500);
  //Turn off the motors
  motor1->run(RELEASE); 
  motor2->run(RELEASE); 
  delay(100);
  // Turn the motor 2 clockwise
  motor2->run(BACKWARD);
  // Turn the motor 1 clockwise
  motor1->run(FORWARD); 
  // Wait 5 seconds
  delay(500); 
  //Turn off the motors
  motor1->run(RELEASE); 
  motor2->run(RELEASE); 
  delay(100);
  }
 
  
  
}

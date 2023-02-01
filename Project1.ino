#include <Servo.h>          
#include <NewPing.h>       

//#define trig A1 
//#define echo A2 
const int trig = 13;
const int echo = 12;

const int LeftMotorForward = 9;
const int LeftMotorBackward = 8;
const int RightMotorForward = 7;
const int RightMotorBackward = 6;

//int distance = 100;
float distance = 100.10;
float max_distance = 300.0;

NewPing sonar(trig, echo, distance); //sensor function
Servo servo_motor; //our servo name


void setup(){
  Serial.begin(9600);

  DDRD |= (1 << DD3); // Set LED 1 (PIN 3) as Output
  DDRD |= (1 << DD4); // Set LED 2 (PIN 4) as Output
  DDRD |= (1 << DD5); // Set LED 3 (PIN 5) as Output
  
  
  servo_motor.attach(11); //servo 
  servo_motor.write(90);
  delay(1000);

  servo_motor.write(90);  // Set Default Position at Center
  _delay_ms(1000);
}

void servo_right(){  
  servo_motor.write(0);
  delay(50);
}

void servo_left(){
  servo_motor.write(180);
  delay(50);
}

void servo_center(){
  servo_motor.write(90);
  delay(50);
}

void servo_45(){
  servo_motor.write(30);
}

float measure_distance(){
    float duration = sonar.ping();
    float distance_cm = sonar.convert_cm(duration);
    distance = distance_cm / 2.54;
    return distance;

}

void moveStop(){
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, HIGH);
  delay(200);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward(){
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  delay(1000);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
}

void turnLeftH(){
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  _delay_ms(500);

  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
}

void turnRightH(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  _delay_ms(500);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void turnLeftL(){
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  _delay_ms(125);

  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
}

void turnRightL(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  _delay_ms(125);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void loop(){

  float center_measure, right_measure;
  
  servo_right();
  delay(200);
  right_measure = measure_distance();
  Serial.print("Right: ");
  Serial.print(right_measure);
  Serial.println(" in");
  delay(50);

  servo_center();
  delay(200);
  center_measure = measure_distance();
  Serial.print("Center: ");
  Serial.print(center_measure);
  Serial.println(" in");
  delay(50);

  if((right_measure > 0 && right_measure <= 10) && (center_measure > 5 || center_measure == 0)){
    if(right_measure > 0 && right_measure <= 4){
      turnLeftL();
      delay(50);
    }

    if(right_measure >= 6){
      turnRightL();
      delay(50);
    }
    
    moveForward();
  } else if(center_measure != 0 && right_measure > 0 && right_measure <= 10 && center_measure < 5 ){
    turnLeftH();
    delay(100);
    
  } else if((center_measure == 0 || center_measure > 5) && (right_measure == 0 || right_measure > 10)){
    moveForward();
    moveForward();
    moveForward();
    delay(100);
    turnRightH();
    delay(100);
    while(right_measure == 0 || right_measure > 10){
      servo_right();
      moveForward();
      delay(100);
      
      right_measure = measure_distance();
      delay(100);
    }
    delay(100);
  }



}


#include "SR04.h"

long Front_Distance = 0;//储存前面距离变量
long Left_Distance = 0;//储存左面距离变量
long Right_Distance = 0;//储存右面距离变量

//UltraSonicDistanceSensor distanceSensor(13, 12);

#define TRIGGER_PIN_Front 2
#define ECHO_PIN_Front 3
#define TRIGGER_PIN_Right 4
#define ECHO_PIN_Right 5
#define TRIGGER_PIN_Left 12
#define ECHO_PIN_Left A1

int left_defined_distance = 20;
int front_defined_distance = 15;
int right_defined_distance = 15;

int tooclose_defined_distance = 1;

SR04 sr04_left = SR04(ECHO_PIN_Left,TRIGGER_PIN_Left);
SR04 sr04_front = SR04(ECHO_PIN_Front,TRIGGER_PIN_Front);
SR04 sr04_right = SR04(ECHO_PIN_Right,TRIGGER_PIN_Right);

//Motor Setup
#define motorLeft_in2 6
#define motorLeft_in1 9
#define motorRight_in1 10
#define motorRight_in2 11

int defined_speed = 100; // For bluetooth control
int turn_defined_speed = 50;
int forward_defined_speed = 100;
int left_defined_speed = 35;
int right_defined_speed = 50;
int backward_defined_speed = 100;

///////////////////////Movement of Robot///////////////////////
void brake() {
  analogWrite(motorRight_in1, 0);
  analogWrite(motorRight_in2, 0);
  analogWrite(motorLeft_in2, 0);
  analogWrite(motorLeft_in1, 0);
}

// the connection of the motors is not well set uo and may need further re-soldering
void moveForward(int speed) {
  analogWrite(motorRight_in1, speed/2);
  analogWrite(motorRight_in2, 0);
  analogWrite(motorLeft_in2, speed);
  analogWrite(motorLeft_in1, 0);
  delay(50);
}

void turnLeft(int speed) {
  analogWrite(motorRight_in1, 0);
  analogWrite(motorRight_in2, speed);
  analogWrite(motorLeft_in2, speed);
  analogWrite(motorLeft_in1, 0);
  delay(50);
}

void turnRight(int speed) {
  analogWrite(motorRight_in1, speed);
  analogWrite(motorRight_in2, 0);
  analogWrite(motorLeft_in2, 0);
  analogWrite(motorLeft_in1, speed);
  delay(50);
}

void moveBackward(int speed) {
  analogWrite(motorRight_in1, 0);
  analogWrite(motorRight_in2, speed);
  analogWrite(motorLeft_in2, 0);
  analogWrite(motorLeft_in1, speed);
  delay(50);
}

void deviation_to_right(int speed){
  analogWrite(motorRight_in1, speed*0.9);
  analogWrite(motorRight_in2, 0);
  analogWrite(motorLeft_in2, speed);
  analogWrite(motorLeft_in1, 0);
  delay(50);
}

void deviation_to_left(int speed){
  analogWrite(motorRight_in1, speed);
  analogWrite(motorRight_in2, 0);
  analogWrite(motorLeft_in2, speed*0.9);
  analogWrite(motorLeft_in1, 0);
  delay(50);
}
///////////////////////Movement of Robot///////////////////////


long getDistance(long distance, int direct){
  int back = 0;
  while(distance > 200 && distance < 0){
    if(back > 10){
      moveBackward(100);
    }
    
    switch(direct){
    case 1:
      back++;
      distance = sr04_left.Distance();//读取超声波距离
      break;
    case 2:
      back++;
      distance = sr04_front.Distance();//读取超声波距离
      break;
    case 3:
      back++;
      distance = sr04_right.Distance();//读取超声波距离
      break;
    }
  }
  
  return distance;
}

void check_distance(int direct){
  switch(direct){
    case 1:
      Left_Distance = getDistance(sr04_left.Distance(), 1);//读取超声波距离
      break;
    case 2:
      Front_Distance = getDistance(sr04_front.Distance(), 2);//读取超声波距离
      break;
    case 3:
      Right_Distance = getDistance(sr04_right.Distance(), 3);//读取超声波距离
      break;
  }
}

void movement(){
  check_distance(2);
  if (Front_Distance < front_defined_distance){
    brake();
    check_distance(1);
    if(Left_Distance < left_defined_distance){
      turnRight(55);
    }else{
      turnLeft(55);
    }
  }else{
    check_distance(1);
    check_distance(3);
    if((Right_Distance - Left_Distance) > tooclose_defined_distance){
      deviation_to_left(100);
    }else if((Left_Distance - Right_Distance) > tooclose_defined_distance){
      deviation_to_right(100);
    }else{
      moveForward(150);
    }
  }
}


void setup () {
  Serial.begin(9600);
  // pinMode of ultrasonic sensors are defined in NewPing library itself
  pinMode(motorRight_in1, OUTPUT);
  pinMode(motorRight_in2, OUTPUT);
  pinMode(motorLeft_in2, OUTPUT);
  pinMode(motorLeft_in1, OUTPUT);
}

void loop () {
  //deviation_to_left(40);
  //delay(1150);
  //deviation_to_right(40);
  //delay(1150);
  movement();
  
  
//Serial.println(distanceSensor.measureDistanceCm());
    //delay(500);
/*
Front_Distance = sr04_front.Distance();//读取超声波距离
Left_Distance = sr04_left.Distance();//读取超声波距离
Right_Distance = sr04_right.Distance();//读取超声波距离
Serial.print("Left ");
Serial.print(Left_Distance);
Serial.print("Front ");
Serial.print(Front_Distance);
Serial.print(" I ");
Serial.print("Right ");
Serial.print(Right_Distance);
Serial.println();
delay(50);
*/
}

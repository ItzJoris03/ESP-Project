#include <Arduino.h>
#include <analogWrite.h>

  int RB = 16;
  int RF = 17;
  int LF = 5;
  int LB = 18;
  int ldrLeft = 34;
  int ldrRight = 39;
  
void setup(){
  Serial.begin(9600);
  
  pinMode(LF,OUTPUT);
  pinMode(LB,OUTPUT);
  pinMode(RF,OUTPUT);
  pinMode(RB,OUTPUT);
  pinMode(ldrLeft, INPUT);
  pinMode(ldrRight, INPUT);

}

void activate(int LF, int LB, int RF, int RB) {
  analogWrite(5, LF);
  analogWrite(18, LB);
  analogWrite(17, RF);
  analogWrite(16, RB);
}

void driveForward(){
  activate(0, 215, 0, 230);
}

void driveBackwards(){
  activate(200, 0, 200, 0);
}

void turnLeft() {
  activate(190, 0, 0, 190);
}

void turnRight() {
  activate(0, 190, 190, 0);
}

void stopDriving(){
  activate(0, 0, 0, 0);
}

void loop(){
  int valueLdrLeft = analogRead(ldrLeft);
  int valueLdrRight = analogRead(ldrRight);
  
  Serial.println(valueLdrRight);
  Serial.println(valueLdrLeft);
  
  if(valueLdrRight > 150 && valueLdrLeft > 150){
    Serial.println("stop");

    stopDriving();
  }else{

  if(valueLdrLeft < 150 && valueLdrRight < 150){
    Serial.println("Driving forward");
    driveForward();
    }
  }
}

#include "Move.h"
#include "Sensor.h"
#include "Display.h" 

int _sync = 20;
int _speed = 120;

bool _forward = false;
bool _left = false;
bool _right = false;
bool _stop = false;

int _avgLeft = 0;
int _avgRight = 0;

Detect sensor;

void setup() {
  Move::setup();
  Display().drawText("Starting...", 1, 0, 0);

  Serial.begin(9600);
  delay(2000);

  for(int i = 0; i != 5; i++) {
    Display().drawText("Initialize in: " + String((5 - i)), 1, 0, 0);
    delay(1000);
  }
  sensor = Detect();
  delay(1000);

  Display().drawText("Moving forward", 1, 0, 0);
  Move::forward(120, _sync);
  delay(100);
  Move::forward(_speed, _sync);
}

void followTheLine() {
  // while left sensor detects black
  while(true) {
     if(sensor.checkBlackLeft()) {
      if(!_left) {
        _left = true;
        _right = false;
        _forward = false;
        _stop = false;

        Move::stop();
        Move::left(_speed + 30);
        Display().drawText("Moving left", 1, 0, 0);
      }
    }
    // while right sensor detects black
    else if(sensor.checkBlackRight()) {
      if(!_right) {
        _left = false;
        _right = true;
        _forward = false;
        _stop = false;

        Move::stop();
        Move::right(_speed + 30);
        Display().drawText("Moving right", 1, 0, 0);
      }
    }
  }
}

void loop() {
  followTheLine();
}

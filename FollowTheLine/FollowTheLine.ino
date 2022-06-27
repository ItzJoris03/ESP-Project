
#include "Move.h"
#include "Sensor.h"
#include "Display.h" 

int _time = 0;
int _sync = 20;
int _speed = 75;

bool _forward = true;
bool _backward = false;
bool _left = false;
bool _right = false;
bool _stop = false;

void setup() {
  Move::setup();

  Serial.begin(9600);
}

void followTheLine(bool hardMode = false) {
  /*
   * 
   * Follow the Line Thin Tapes
   * 
   */
  if(hardMode) {
    // Check values
    // while left sensor detects black but right white
    if(Detect::checkBlackLeft() && !Detect::checkBlackRight()) {
      _time = 0;
      
      if(!_left) {
        Move::left(_speed);
        Display().drawText("Left", 1, 0, 0);
  
        _time = 0;
        _left = true;
        
        _forward = false;
        _right = false;
        _stop = false; 
        _backward = false;
      }
    }
    
    // while no sensor detects white
    else if(Detect::checkBlackLeft() && Detect::checkBlackRight()) {
      if(_time <= 200) {
        if(!_backward) {
          Move::backward(_speed, _sync);
          Display().drawText("Backwards", 1, 0, 0);
          
          _backward = true;
          
          _left = false; 
          _forward = false;  
          _right = false;
          _stop = false;
        }
        _time++;
      } else {
        if(!_stop) {
          Move::stop();
          Display().drawText("Stop", 1, 0, 0);
          
          _stop = true;
          _backward = true;
          
          _left = false;
          _forward = false;
          _right = false;
        }
      }
    }
  
    // While left sensor detect white but right black
    else if(!Detect::checkBlackLeft() && Detect::checkBlackRight()) {
      _time = 0;
      
      if(!_right) {
        Move::right(_speed);
        Display().drawText("Right", 1, 0, 0);
  
        _right = true;
        
        _left = false; 
        _forward = false;
        _stop = false;
        _backward = false;
      }
    }
  
    // If all conditions are good
    else {
      _time = 0;
      
      if(!_forward) {
        Move::forward(_speed, _sync);
        Display().drawText("Forward", 1, 0, 0);
  
        _forward = true;
        
        _left = false;
        _right = false;
        _stop = false;
        _backward = false;
      }
    }
  /*
   * 
   * Follow the Line thick Tapes
   * 
   */
  } else {
    // Check values
    // while left sensor detects white but right black
    if(!Detect::checkBlackLeft() && Detect::checkBlackRight()) {
      _time = 0;
      
      if(!_left) {
        Move::left(_speed);
        Display().drawText("Left", 1, 0, 0);
  
        _left = true;
        
        _forward = false;
        _right = false;
        _stop = false; 
        _backward = false;
      }
    }
    
    // while no sensor detects black
    else if(!Detect::checkBlackLeft() && !Detect::checkBlackRight()) {
      if(_time <= 200) {
        if(!_backward) {
          Move::backward(_speed, _sync);
          Display().drawText("Backwards", 1, 0, 0);
          
          _backward = true;
          
          _left = false; 
          _forward = false;  
          _right = false;
          _stop = false;
        }
        _time++;
      } else {
        if(!_stop) {
          Move::stop();
          Display().drawText("Stop", 1, 0, 0);
          
          _stop = true;
          _backward = true;
          
          _left = false;
          _forward = false;
          _right = false;
        }
      }
    }
  
    // While left sensor detect black but right white
    else if(Detect::checkBlackLeft() && !Detect::checkBlackRight()) {
      _time = 0;
      
      if(!_right) {
        Move::right(_speed);
        Display().drawText("Right", 1, 0, 0);
  
        _right = true;
        
        _left = false; 
        _forward = false;
        _stop = false;
        _backward = false;
      }
    }
  
    // If all conditions are good
    else {
      _time = 0;
      
      if(!_forward) {
        Move::forward(_speed, _sync);
        Display().drawText("Forward", 1, 0, 0);
  
        _forward = true;
        
        _left = false;
        _right = false;
        _stop = false;
        _backward = false;
      }
    }
  }
}

void loop() {
  /*Serial.print("left: ");
  Serial.print(Detect::getLeft());
  Serial.print(", right: ");
  Serial.print(Detect::getRight());
  Serial.println();*/

  followTheLine();
  Serial.println("Time: " + String(_time));
}

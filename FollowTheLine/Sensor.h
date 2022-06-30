#include <analogWrite.h>

class Detect {
private:
  static const int sensorRight = 34;
  static const int sensorLeft = 39;
  int avgLeft = 0; 
  int avgRight = 0; 

public:
  Detect() {
    avgRight = Detect::getRight() + 300;
    avgLeft = Detect::getLeft() + 300;
  }

  static int getLeft() {
    return analogRead(Detect::sensorLeft);
  }

  static int getRight() {
    return analogRead(Detect::sensorRight);
  }

  bool checkBlackLeft() {
    return avgLeft < Detect::getLeft();
  }

  bool checkBlackRight() {
    return avgRight < Detect::getRight();
  }
};

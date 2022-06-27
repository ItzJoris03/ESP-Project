#include <analogWrite.h>

class Detect {
private:
  static const int sensorRight = 34;
  static const int sensorLeft = 39;

public:
  static int getLeft() {
    return analogRead(Detect::sensorLeft);
  }

  static int getRight() {
    return analogRead(Detect::sensorRight);
  }

  static bool checkBlackLeft(){
    return Detect::getLeft() > 1000;
  }

  static bool checkBlackRight(){
    return Detect::getRight() > 3300;
  }
};

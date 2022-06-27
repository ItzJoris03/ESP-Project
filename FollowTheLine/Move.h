#include <analogWrite.h>

class Move {
private:
  static const int motorRB = 5; // Right Wheel Backwards
  static const int motorLF = 16; // Left Wheen Forwards
  static const int motorLB = 17; // Left Wheel Backwards
  static const int motorRF = 18; // Right Wheel Forwards

public:
  static void forward(int speed, int sync) {
    analogWrite(Move::motorRF, speed+sync);
    analogWrite(Move::motorLF, speed);
    analogWrite(Move::motorRB, 0);
    analogWrite(Move::motorLB, 0);
  }
  static void backward(int speed, int sync) {
    analogWrite(Move::motorRF, 0);
    analogWrite(Move::motorLF, 0);
    analogWrite(Move::motorRB, speed+sync);
    analogWrite(Move::motorLB, speed);
  }

  static void left(int speed) {
    analogWrite(Move::motorRF, speed);
    analogWrite(Move::motorLF, 0);
    analogWrite(Move::motorRB, 0);
    analogWrite(Move::motorLB, 0);
  }

  static void right(int speed) {
    analogWrite(Move::motorRF, 0);
    analogWrite(Move::motorLF, speed);
    analogWrite(Move::motorRB, 0);
    analogWrite(Move::motorLB, 0);
  }
  static void stop() {
    analogWrite(Move::motorRF, 0);
    analogWrite(Move::motorLF, 0);
    analogWrite(Move::motorRB, 0);
    analogWrite(Move::motorLB, 0);
  }

  static void setup() { Move::stop(); }
};

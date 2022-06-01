#include <analogWrite.h>

void setup() {
  // put your setup code here, to run once:
  int motorRB = 5; // Right Wheel Backwards
  int motorLF = 16; // Left Wheen Forwards
  int motorLB = 17; // Left Wheel Backwards
  int motorRF = 18; // Right Wheel Forwards

  analogWrite(motorRB, 0);
  analogWrite(motorLF, 0);
  analogWrite(motorLB, 0);
  analogWrite(motorRF, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

}

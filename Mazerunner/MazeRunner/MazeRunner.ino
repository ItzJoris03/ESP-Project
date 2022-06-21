  //This code makes the robot drive over thin lines. 
 // On the display the values that the LDR picks up will be shown. These values are used to see if the robot follows the line. 

 #include <Arduino.h>
 #include <analogWrite.h>
 #include <Adafruit_SSD1306.h>
 #include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

 
 #define SOUND_SPEED 0.034
 #define CM_TO_INCH 0.393701

 int ldrLeft = 34;
 int ldrRight = 39;
 int forwardLeft = 18;
 int forwardRight = 16;
 int reverseLeft = 5;
 int reverseRight = 17;
 const int trigPin = 25;
 const int echoPin = 26;
 // defines variables
 long duration;
 int distance;
 
 void setup() {

   
  
   Serial.begin(9600);


   // Show initial display buffer contents on the screen --
   // the library initializes this with an Adafruit splash screen.

   pinMode(forwardLeft, OUTPUT);
   pinMode(forwardRight, OUTPUT);
   pinMode(reverseLeft, OUTPUT);
   pinMode(reverseRight, OUTPUT);
   pinMode(ldrLeft, INPUT);
   pinMode(ldrRight, INPUT);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input

   // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 

 }

 void loop() {
   int valueLdrLeft = analogRead(ldrLeft);
   int valueLdrRight = analogRead(ldrRight);

//Zijkant ultrasonic sensor
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  delay(1000);

// Voorkant afstand sensor
VL53L0X_RangingMeasurementData_t measure;
    
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Voorkant (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    


//Drive code
//als voorkant ver weg is en links dichtbij is
if(measure.RangeMilliMeter > 100 && distance < 15) {
  moveForward();
  //bijsturen als links dichtbij komt
  if(distance < 5) {
    correctRight();
  }
}
//als voorkant dichtbij is en links ver weg is
else if(measure.RangeMilliMeter < 100 && distance > 20) {
  turnLeft();
}

//als voorkant dichtbij is en links dichtbij is
else if(measure.RangeMilliMeter < 200 && distance < 20) {
  turnRight();
}
  
  
  

   
  
//  //als voorkant ver weg is en links ver weg is
//  if(measure.RangeMilliMeter > 200 && distance > 20) {
//    moveBackwards();
//    turnLeft();
//  }
  




//if(measure.RangeMilliMeter < 200 ) {
//  moveBackwards();
//  turnRight();
//}else if(distance > 20 && measure.RangeMilliMeter < 200){
//  turnLeft();
//}else{
//  moveForward();
//}

//if(distance > 20) {
//  moveBackwards();
//  turnLeft();
//}
//else if(measure.RangeMilliMeter < 200) {
//  
//}
//
//else{
//  moveForward();
//}


}




 // These are the functions that are used in the code above.

void drive(int fL, int fR, int rL, int rR){
  analogWrite(forwardLeft, fL);
  analogWrite(forwardRight, fR);
  analogWrite(reverseLeft, rL);
  analogWrite(reverseRight, rR);
}

 void moveForward() {
  drive(180, 180, LOW, LOW);
  delay(50);
  drive(120, 120, LOW, LOW);
}

 void moveBackwards() {
   drive(LOW, LOW, 180, 180);
   delay(50);
   drive(LOW, LOW, 120, 120);
 }

 void turnRight() {
   drive(LOW, 160, 120, LOW);
 }

 void turnLeft() {
   drive(160, LOW, LOW, 120);
 }

 void stopVehicle() {
   drive(LOW, LOW, LOW, LOW);
 }

 void correctRight() {
   drive(180, 180, LOW, LOW);
  delay(50);
  drive(80, 120, LOW, LOW);
 }

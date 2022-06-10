  //This code makes the robot drive over thin lines. 
 // On the display the values that the LDR picks up will be shown. These values are used to see if the robot follows the line. 

 #include <Arduino.h>
 #include <analogWrite.h>
 #include <Adafruit_SSD1306.h>
 #include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
 
 #define SCREEN_WIDTH 128
 #define SCREEN_HEIGHT 32
 #define OLED_RESET     4
 #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

 Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

 #define LOGO_HEIGHT   16
 #define LOGO_WIDTH    16
 #define SOUND_SPEED 0.034
 #define CM_TO_INCH 0.393701

 int ldrLeft = 34;
 int ldrRight = 39;
 int forwardLeft = 18;
 int forwardRight = 16;
 int reverseLeft = 5;
 int reverseRight = 17;
 int trigPin = 5;
 int echoPin = 18;
 long duration;
 float distanceCm;
 
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

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  
  // Prints the distance in the Serial Monitor
  Serial.print("Zijkant (cm): ");
  Serial.println(distanceCm);
  
  delay(1000);

//   if(valueLdrLeft < 120 && valueLdrRight < 120 ) {
//      moveForward();
//   } 
//
//   if(valueLdrLeft < 120 && valueLdrRight > 120) {
//     turnRight();
//   } 
//
//   if(valueLdrLeft > 120 && valueLdrRight < 120) {
//     turnLeft();   
//   } 
//
//   if (valueLdrLeft > 120 && valueLdrRight > 120){ 
//     moveBackwards();
//   }
//
//   if(valueLdrLeft == 0 && valueLdrRight == 0){
//     stopVehicle();
//   }

VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Voorkant (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(100);

if(measure.RangeMilliMeter < 200 ) {
  stopVehicle();
  turnRight();
}else if(distanceCm > 20){
  turnLeft();
}else{
}
  moveForward();
}


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
  delay(100);
  drive(100, 100, LOW, LOW);
}

 void moveBackwards() {
   drive(LOW, LOW, 200, 200);
 }

 void turnRight() {
   drive(LOW, 180, LOW, LOW);
 }

 void turnLeft() {
   drive(180, LOW, LOW, 180);
   delay(100);
   drive(100, LOW, LOW, 100);
 }

 void stopVehicle() {
   drive(LOW, LOW, LOW, LOW);
 }

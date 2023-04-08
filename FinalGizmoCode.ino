// ring1
//sensor1
//11cm max sensing range
const int trigPin = 6;
const int echoPin = 13;
//sensor2
const int trigPin1 = 11;
const int echoPin1 = 15;
// setting the maximum sensing range for the ultrasonic sensor to match the constraints of our product
const int maxHeight = 30;
//led
const int LED = 14;
// the second led is powered through the speaker circuit
//motor1 pins
const int motorConnnectionPin1 = 8;
const int motorConnnectionPin2 = 9;
const int motorConnnectionPin3 = 10;
const int motorConnnectionPin4 = 12;
//motor2 pins
const int motorConnnection1Pin1 = 16;
const int motorConnnection1Pin2 = 17;
const int motorConnnection1Pin3 = 18;
const int motorConnnection1Pin4 = 19;
// sensor variables
long duration; // variable for the duration of sound wave travel for sesnsor 1
int distance; // variable for the distance measurement for sensor 1
long duration1; // variable for the duration of sound wave travel for sesnsor 2
int distance1; // variable for the distance measurement for sensor 2
const int setheight = 5; // minimum height between user's hand and sensor 
//number of steps involved in rotating motor
int Steps = 0; //motor 1
int Steps1 =0; //motor 2
//setting clockwise/anticlockwise direction of rotation
boolean Direction = true; //motor 1
boolean Direction1 = true; // motor 2
// digipot ( digital potentiometer library and pin declaration)
#include<DigiPotX9Cxxx.h>
// first two values access pins on arduino board and pin 7 is a common ground
DigiPot pot(2, 3, 7); // controls the volume of the first speaker (controls stereo volume)
DigiPot pot1(4,5,7); // controls the volume of the second speaker (controls mono volume)

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  // motor 1 outputs
  pinMode(motorConnnectionPin1, OUTPUT);
  pinMode(motorConnnectionPin2, OUTPUT);
  pinMode(motorConnnectionPin3, OUTPUT);
  pinMode(motorConnnectionPin4, OUTPUT);
  // motor 2 outputs
  pinMode(motorConnnection1Pin1, OUTPUT);
  pinMode(motorConnnection1Pin2, OUTPUT);
  pinMode(motorConnnection1Pin3, OUTPUT);
  pinMode(motorConnnection1Pin4, OUTPUT);
  pinMode(LED, OUTPUT); // Declare the LED as an output
  // increasing the positon of the digital potentiometer till it reaches max value
  // speaker 1
  for(int j=0; j<100; j++)
  {
    pot.increase(1);
    }
  // speaker 2
   for(int j=0; j<100; j++)
  {
    pot1.increase(1);
    }

}
// running the whole system (combined function mapping the rotation of motor and speaker volume with respect to the sensor readings)
void loop() {
  motorcontrol(); //calling motor function controlling both motors
  digitalWrite(LED, HIGH); // Turn the LED on
}
//function to control both motors with respect to sensor distance
void motorcontrol(){
  // first motor and sesnsor combined code
  // calling sensor 1 outputs
  // Clearing the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
   // Calculating the distance
  distance = (duration) * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // setting the inital condition of sensing range of the sensor to limit it to the maximum movement of the rings
  if (distance < maxHeight){
    if (distance > 5) {
      // moves clockwise
      for(int i=0; i<4096/10; i++){
        stepperforward();
        pot.increase(11);
        
        delayMicroseconds(600);
        }
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      } else {
        //moves anti-clockwise
        for(int i=0; i<4096/10; i++){
          stepperbackward();
          pot.decrease(11);
          delayMicroseconds(600);
          }
      // for referring to sensor readings in the serial monitor to debug code
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(distance);
      Serial.println(" cm");
    }
  }
  // second motor and sesnor combined code
  //calling sesnor 2 outputs
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
   // Calculating the distance
  distance1 = (duration1) * 0.034 / 2; // Speed of sound wave divided by 2 (transmitter and receiver signal)
  if (distance1 < maxHeight) {
    if (distance1 > 5) {
      // moves clockwise
      for(int i=0; i<4096/10; i++){
        stepperbackward1();
        pot1.increase(1);
        delayMicroseconds(800);
        }
      Serial.print("Distance: ");
      Serial.print(distance1);
      Serial.println(" cm");
      } else {
        // moves anti-clockwise
      for(int i=0; i<4096/10; i++){
        stepperforward1();
        pot1.decrease(1);
        delayMicroseconds(800);
        }
      Serial.print("Distance: ");
      Serial.print(distance1);
      Serial.println(" cm");
    }
  }
  
}
//motor 1 functions

//function to facilitate forward motion in motor 1
void stepperforward() {
  switch (Steps) {
    case 0:
      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, HIGH);

      break;

    case 1:
      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, HIGH);
      digitalWrite(motorConnnectionPin4, HIGH);
      break;

    case 2:

      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, HIGH);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 3:
      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, HIGH);
      digitalWrite(motorConnnectionPin3, HIGH);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 4:
      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, HIGH);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 5:

      digitalWrite(motorConnnectionPin1, HIGH);
      digitalWrite(motorConnnectionPin2, HIGH);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 6:
      digitalWrite(motorConnnectionPin1, HIGH);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 7:
      digitalWrite(motorConnnectionPin1, HIGH);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, HIGH);
      break;

    default:

      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, LOW);
      break;
      }
    ForwardDirection();
    Direction = !Direction;

}
//function to facilitate backward motion in motor 2
void stepperbackward() {
  switch (Steps) {
    case 0:
      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, HIGH);

      break;

    case 1:
      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, HIGH);
      digitalWrite(motorConnnectionPin4, HIGH);
      break;

    case 2:

      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, HIGH);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 3:
      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, HIGH);
      digitalWrite(motorConnnectionPin3, HIGH);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 4:
      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, HIGH);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 5:

      digitalWrite(motorConnnectionPin1, HIGH);
      digitalWrite(motorConnnectionPin2, HIGH);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 6:
      digitalWrite(motorConnnectionPin1, HIGH);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, LOW);
      break;

    case 7:
      digitalWrite(motorConnnectionPin1, HIGH);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, HIGH);
      break;

    default:

      digitalWrite(motorConnnectionPin1, LOW);
      digitalWrite(motorConnnectionPin2, LOW);
      digitalWrite(motorConnnectionPin3, LOW);
      digitalWrite(motorConnnectionPin4, LOW);
      break;
      }
    
    BackwardDirection();
    Direction = !Direction;

}
//motor 1 direction functions ( clockwise and anticlockwise)
// clockwise motion
void ForwardDirection() {
  if (Direction == 1) {
    Steps++;
  }
  if (Steps > 7) {
    Steps = 0;
  }
}
// anti-clockwise motion
void BackwardDirection() {
   if (Direction == 0) {
        Steps--;
    }
    if (Steps < 0) {
        Steps = 7;
    }
}
//second motor functions

//function to facilitate forward motion in motor 2
void stepperforward1() { 
  switch (Steps1) {
    case 0:
      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, HIGH);

      break;

    case 1:
      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, HIGH);
      digitalWrite(motorConnnection1Pin4, HIGH);
      break;

    case 2:

      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, HIGH);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 3:
      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, HIGH);
      digitalWrite(motorConnnection1Pin3, HIGH);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 4:
      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, HIGH);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 5:

      digitalWrite(motorConnnection1Pin1, HIGH);
      digitalWrite(motorConnnection1Pin2, HIGH);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 6:
      digitalWrite(motorConnnection1Pin1, HIGH);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 7:
      digitalWrite(motorConnnection1Pin1, HIGH);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, HIGH);
      break;

    default:

      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;
      }
    ForwardDirection1();
    Direction1 = !Direction1;

}
//function to facilitate backward motion in motor 2
void stepperbackward1() {
  switch (Steps1) {
    case 0:
      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, HIGH);

      break;

    case 1:
      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, HIGH);
      digitalWrite(motorConnnection1Pin4, HIGH);
      break;

    case 2:

      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, HIGH);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 3:
      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, HIGH);
      digitalWrite(motorConnnection1Pin3, HIGH);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 4:
      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, HIGH);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 5:

      digitalWrite(motorConnnection1Pin1, HIGH);
      digitalWrite(motorConnnection1Pin2, HIGH);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 6:
      digitalWrite(motorConnnection1Pin1, HIGH);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;

    case 7:
      digitalWrite(motorConnnection1Pin1, HIGH);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, HIGH);
      break;

    default:

      digitalWrite(motorConnnection1Pin1, LOW);
      digitalWrite(motorConnnection1Pin2, LOW);
      digitalWrite(motorConnnection1Pin3, LOW);
      digitalWrite(motorConnnection1Pin4, LOW);
      break;
      }
    
    BackwardDirection1();
    Direction1 = !Direction1;

}
//motor 2 direction functions ( clockwise and anticlockwise)
// clockwise motion 
void ForwardDirection1() {
  if (Direction1 == 1) {
    Steps1++;
  }
  if (Steps1 > 7) {
    Steps1 = 0;
  }
}
// anti-clockwise direction
void BackwardDirection1() {
   if (Direction1 == 0) {
        Steps1--;
    }
    if (Steps1 < 0) {
        Steps1 = 7;
    }
}

// credits
// links of websites for code reference
// https://wiki.52pi.com/index.php?title=D-0011
// https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
// https://www.instructables.com/Automatic-Distance-Based-Volume-Control/
// https://docs.rs-online.com/c0f4/0900766b814bf8a8.pdf
// https://www.youtube.com/watch?v=q_IWdun2yUY
// https://github.com/wzandler/mac-volume-control

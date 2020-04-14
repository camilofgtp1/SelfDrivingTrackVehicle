/*
  https://www.arduino.cc/en/Reference/RobotMotorsWrite
  Robot.motorsWrite(speedLeft, speedRight) to replace cumbersome functions to controlling the movement

  TODO: Arduino can connect to laptop using wirless network to send sensor data and recieve manual control instructions
  TODO: Arduino can connecto to RC Controller
  TODO: Arduino is powered by battery
  TODO: The turning can be made by giving an angle in degrees
  TODO: The processing sketch maps the sensor data at scale and can be zoomed in and out
  TODO: QLearning algorithm gives actions that move the vehicle for the amount of time specified
  TODO: Mobile app shows room, vehicle finds the best way to a selected spot
  TODO: Easy Mode: QLearning outputs one of 4 actions corresponding to the direction it should drive to
        Hard Mode: QLearning ouputs outputs speed and direction of the spinning of the motors
*/
#include "Vehicle.h"
#include "Q.h"

Vehicle v;
Q q;

int steps = 20;
float measurements[20];
float leftMotor[20];
float rightMotor[20];
float turningTimes[20];
float turningSpeeds[20];

void setup() {
  Serial.begin(9600);
  q.randomMeasurements(measurements, steps);
  q.randomMotor(leftMotor, steps);
  q.randomMotor(rightMotor, steps);
  q.randomSpeeds(turningSpeeds, steps);
  q.randomTimes(turningTimes, steps);

  //Serial.println("measurements");
  //q.printArr(measurements, steps);
  
  Serial.println("right motor: ");
  q.printArr(rightMotor, steps);
  
  Serial.println("left motor: ");
  q.printArr(leftMotor, steps);

  Serial.println("turning times: ");
  q.printArr(turningTimes, steps);

  Serial.println("turning speeds");
  q.printArr(turningSpeeds, steps);

}

void loop() {

  for (int i = 0; i < steps; i++) {
    if (leftMotor[i] == 1.00 && rightMotor[i] == 0.00) {
      Serial.println("left: ");
      Serial.print("speed: ");
      Serial.println(turningSpeeds[i]);
      Serial.print("time: ");
      Serial.println(turningTimes[i]);
      v.left(turningTimes[i], turningSpeeds[i]);
    }

    if (leftMotor[i] == 0.00 && rightMotor[i] == 1.00) {
      Serial.println("right: ");
      Serial.print("speed: ");
      Serial.println(turningSpeeds[i]);
      Serial.print("time: ");
      Serial.println(turningTimes[i]);
      v.right(turningTimes[i], turningSpeeds[i]);
    }
    if (rightMotor[steps] == 1.00 && leftMotor[i] == 1.00) {
      Serial.println("both");
      Serial.print("speed: ");
      Serial.println(turningSpeeds[i]);
      Serial.print("time: ");
      Serial.println(turningTimes[i]);
      v.left(turningTimes[i], turningSpeeds[i]);
      v.right(turningTimes[i], turningSpeeds[i]);
    }
    Serial.println(i);
  }

}

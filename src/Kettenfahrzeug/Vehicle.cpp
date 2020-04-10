//#include <Drive.h>  TODO: Appy library

#include "Vehicle.h"
#include <NewPing.h>

#define MOTOR_RIGHT_ENABLE 6
#define MOTOR_RIGHT_INPUT1 7
#define MOTOR_RIGHT_INPUT2 8

#define MOTOR_LEFT_ENABLE 11
#define MOTOR_LEFT_INPUT1 12
#define MOTOR_LEFT_INPUT2 13

#define TRIGGER_LEFT 10
#define ECHO_LEFT 9
#define MAX_DISTANCE 200

#define TRIGGER_MID 5
#define ECHO_MID 4

#define TRIGGER_RIGHT 3
#define ECHO_RIGHT 2
#define VEHICLE_SPEED 125

//todo: adapt constructor to use initialization list.
//see: https://en.cppreference.com/w/cpp/language/initializer_list

Vehicle::Vehicle() :
  sLeft(TRIGGER_LEFT, ECHO_LEFT, MAX_DISTANCE),
  sMid(TRIGGER_MID, ECHO_MID, MAX_DISTANCE),
  sRight(TRIGGER_RIGHT, ECHO_RIGHT, MAX_DISTANCE)
{
  /*
    pinMode(MOTOR_LEFT_ENABLE, OUTPUT);
    pinMode(MOTOR_LEFT_INPUT1, OUTPUT);
    pinMode(MOTOR_LEFT_INPUT2, OUTPUT);

    pinMode(MOTOR_RIGHT_ENABLE, OUTPUT);
    pinMode(MOTOR_RIGHT_INPUT1, OUTPUT);
    pinMode(MOTOR_RIGHT_INPUT2, OUTPUT);
  */
}


void Vehicle::readSensors()
{
  // Clears the trigPin
  //Serial.print("Sonar left: ");
  //float measurements= [];
/*
  Serial.print(sLeft.ping_cm());
  Serial.print("\n");

  //Serial.print("Sonar mid: ");
  Serial.print(sMid.ping_cm());
  Serial.print("\n");

  //Serial.print("Sonar right: ");
  Serial.print(sRight.ping_cm());
  Serial.print("\n");

  delay(500);

  */
  Serial.print(sLeft.ping_cm());
  Serial.print(":");
  Serial.print(sMid.ping_cm());
  Serial.print(":");
  Serial.print(sRight.ping_cm());
  Serial.print("\n");
  
}

void Vehicle::forwards() {

  digitalWrite(MOTOR_LEFT_INPUT1, LOW);
  digitalWrite(MOTOR_LEFT_INPUT2, HIGH);

  digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
  digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);

  analogWrite(MOTOR_LEFT_ENABLE, VEHICLE_SPEED);
  analogWrite(MOTOR_RIGHT_ENABLE, VEHICLE_SPEED);
}

void Vehicle::reverse() {

  digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
  digitalWrite(MOTOR_LEFT_INPUT2, LOW);

  digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
  digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

  analogWrite(MOTOR_LEFT_ENABLE, VEHICLE_SPEED);
  analogWrite(MOTOR_RIGHT_ENABLE, VEHICLE_SPEED);
}

//TODO: make this so it turn only 10 degrees at constant speed or a given angle


void Vehicle::turnLeft(int turningTime, int turnSpeed) {

  digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
  digitalWrite(MOTOR_LEFT_INPUT2, LOW);

  digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
  digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);

  analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
  analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
  delay(turningTime);
  fullStop();
}

//TODO: turn 10 degrees
void Vehicle::turnRight(int turningTime, int turnSpeed) {
  digitalWrite(MOTOR_LEFT_INPUT1, LOW);
  digitalWrite(MOTOR_LEFT_INPUT2, HIGH);

  digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
  digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

  analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
  analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
  delay(turningTime);
  fullStop();
}

void Vehicle::fullStop() {

  digitalWrite(MOTOR_LEFT_INPUT1, LOW);
  digitalWrite(MOTOR_LEFT_INPUT2, LOW);

  digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
  digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

  analogWrite(MOTOR_LEFT_ENABLE, 0);
  analogWrite(MOTOR_RIGHT_ENABLE, 0 );
}


/*
  //try different turning speeds
  void Vehicle::testTurningRight() {

  for (int i = 0; i < 10; i++) {
  digitalWrite(MOTOR_LEFT_INPUT1, LOW);
  digitalWrite(MOTOR_LEFT_INPUT2, HIGH);

  digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
  digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

  analogWrite(MOTOR_LEFT_ENABLE, VEHICLE_SPEED);
  analogWrite(MOTOR_RIGHT_ENABLE, VEHICLE_SPEED);
  }
  }

  void Vehicle::demoMotors() {

  //HIGH or Low sets the direction

  for (int i = 130; i < 2550; i++) {

  if (i % 2 == 0) {
  delay(6000);
  Serial.print("left  \n");
  analogWrite(MOTOR_LEFT_ENABLE, i);
  analogWrite(MOTOR_RIGHT_ENABLE, 0);
  } else {
  delay(6000);
  Serial.print("right \n");
  analogWrite(MOTOR_LEFT_ENABLE, 0);
  analogWrite(MOTOR_RIGHT_ENABLE, i);
  }
  }
  }

  void Vehicle::setSpeed(int newSpeed) {
  VEHICLE_SPEED = newSpeed;
  }


  An action [0, 0, 0, 0] -> forwards, backwards, left, right
  the action is executed if the value is 1, then it returns a reward



  int Vehicle::perform(int *action) {
  int reward;

  if (action[0] == 1) {
  forwards();
  }
  if (action[1] == 1) {
  reverse();
  }
  if (action[2] == 1) {
  turnLeft();
  }
  if (action[3] == 1) {
  turnRight();
  }

  return reward;

  }

  int Vehicle::getObservation() {

  int obs[3] = {sLeft.ping_cm(), sMid.ping_cm(), sRight.ping_cm()};

  return obs;
  }

*/

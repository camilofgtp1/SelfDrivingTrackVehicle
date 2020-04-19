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

//uses the serial port to send sensors measurements to mapper in processing
void Vehicle::sendToMapper()
{
  Serial.print(sLeft.ping_cm());
  Serial.print(":");
  Serial.print(sMid.ping_cm());
  Serial.print(":");
  Serial.print(sRight.ping_cm());
  Serial.print("\n");
  delay(500);
}

float Vehicle::getLeftDistance(){
    return float(sMid.ping_cm());
}

float Vehicle::getMidDistance(){
    return float(sMid.ping_cm());
}

float Vehicle::getRightDistance(){
    return float(sMid.ping_cm());
}


void Vehicle::forwards(int turningTime, int turnSpeed) {

  digitalWrite(MOTOR_LEFT_INPUT1, LOW);
  digitalWrite(MOTOR_LEFT_INPUT2, HIGH);

  digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
  digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);

  analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
  analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
  delay(turningTime);
  fullStop();
}

void Vehicle::reverse(int turningTime, int turnSpeed) {

  digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
  digitalWrite(MOTOR_LEFT_INPUT2, LOW);

  digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
  digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

  analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
  analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
  delay(turningTime);
  fullStop();
}

void Vehicle::left(int turningTime, int turnSpeed) {

    digitalWrite(MOTOR_LEFT_INPUT1, LOW);
    digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
    analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();
}
void Vehicle::right(int turningTime, int turnSpeed) {

    digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
    digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
    analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();
}
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

//TODO: angle control. not possible without compass!
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

//TODO: Implement performAction, which returns the reward
float Vehicle::performAction() {

}

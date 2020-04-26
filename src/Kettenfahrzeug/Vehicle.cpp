#include "Vehicle.h"
#include "Action.h"
#include <NewPing.h>
#include <Servo.h>

#define MOTOR_RIGHT_ENABLE 6
#define MOTOR_RIGHT_INPUT1 7
#define MOTOR_RIGHT_INPUT2 8

#define MOTOR_LEFT_ENABLE 11
#define MOTOR_LEFT_INPUT1 12
#define MOTOR_LEFT_INPUT2 13

#define MAX_DISTANCE 200
#define TRIGGER_MID 5
#define ECHO_MID 4

#define SERVO_PIN 9

Vehicle::Vehicle() :
  sMid(TRIGGER_MID, ECHO_MID, MAX_DISTANCE), servo()
{
  servo.attach(SERVO_PIN);
}

float Vehicle::getMidDistance() {

  return float(sMid.ping_cm());
}

void Vehicle::moveServo(int angle, int turningSpeed) {
  servo.write(angle);
  delay(turningSpeed);
}

void Vehicle::left(int turningTime, int turnSpeed, bool clockwise ) {

  if (clockwise) {
    digitalWrite(MOTOR_LEFT_INPUT1, LOW);
    digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
    analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();
  } else {
    digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
    digitalWrite(MOTOR_LEFT_INPUT2, LOW);
    analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();

  }
}

void Vehicle::right(int turningTime, int turnSpeed, bool clockwise) {

  if (clockwise) {

    digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
    digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
    analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();

  } else {
    digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
    digitalWrite(MOTOR_RIGHT_INPUT2, LOW);
    analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();
  }
}

void Vehicle::fullStop() {

  digitalWrite(MOTOR_LEFT_INPUT1, LOW);
  digitalWrite(MOTOR_LEFT_INPUT2, LOW);

  digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
  digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

  analogWrite(MOTOR_LEFT_ENABLE, 0);
  analogWrite(MOTOR_RIGHT_ENABLE, 0 );
}
//example of action
//PWMLeft:121  | PWMRight: 160 | clockwiseLeft: 1  | clockwiseRight: 0 | timeLeft: 939 | timeRight: 698  | servoAngle: 141
void Vehicle::performActions(struct Action actions[], int duration) {

  for (int i = 0; i < duration; i++) {
    left(actions[i].timeLeft, actions[i].PWMLeft, actions[i].clockwiseLeft);
    right(actions[i].timeRight, actions[i].PWMRight, actions[i].clockwiseRight);
    moveServo(actions[i].servoAngle, 1000);
  }
}

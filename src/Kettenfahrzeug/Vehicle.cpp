#include "Vehicle.h"
#include <NewPing.h>
#include <Servo.h>

#define MOTOR_RIGHT_ENABLE 6
#define MOTOR_RIGHT_INPUT1 7
#define MOTOR_RIGHT_INPUT2 8

#define MOTOR_LEFT_ENABLE 11
#define MOTOR_LEFT_INPUT1 12
#define MOTOR_LEFT_INPUT2 13

#define MAX_DISTANCE 400
#define TRIGGER_MID 5
#define ECHO_MID 4

#define SERVO_PIN 9

Vehicle::Vehicle() :
  sMid(TRIGGER_MID, ECHO_MID, MAX_DISTANCE), servo()
{
  servo.attach(SERVO_PIN);
}

//uses the serial port to send sensors measurements to mapper in processing
void Vehicle::sendToMapper()
{
  Serial.print(sMid.ping_cm());
  Serial.print("\n");
  delay(500);
}

float Vehicle::getMidDistance(){
    return float(sMid.ping_cm());
}

void Vehicle::moveServo(int angle, int turningSpeed){
  servo.write(angle);
  delay(turningSpeed);
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

#include "Vehicle.h"
#include <NewPing.h>
#include <Servo.h>
#include "Wire.h"

#define MOTOR_LEFT_ENABLE 6
#define MOTOR_LEFT_INPUT1 7
#define MOTOR_LEFT_INPUT2 8

#define MOTOR_RIGHT_ENABLE 11
#define MOTOR_RIGHT_INPUT1 12
#define MOTOR_RIGHT_INPUT2 13

#define MAX_DISTANCE 200
#define TRIGGER_MID 5
#define ECHO_MID 4

#define SERVO_PIN 9

Vehicle::Vehicle() :
  sMid(TRIGGER_MID, ECHO_MID, MAX_DISTANCE), servo()
{
}

//returns the average of 3 readings in cms
int Vehicle::readSonarCms() {
  return (sMid.convert_cm(sMid.ping_median(3)));
}

int Vehicle::readSonarNormalized() {
  return map(readSonarCms(), 3, MAX_DISTANCE, 0, 100);

}

void Vehicle::moveServo(int angle, int turningSpeed) {
  int newAngle = map(angle, 0, 100, 0, 180);
  servo.attach(SERVO_PIN);
  servo.write(newAngle);
  delay(turningSpeed);
  servo.detach();
}

//true turn right, false turn left// counter clockwise on the left is turnnig right
void Vehicle::drive(int pwmLeft, int pwmRight) {
    int steps = 100;
    Serial.print(pwmLeft);
    for (int i = 0; i < 1000; i+=200) {
    Serial.println(i);    
      //forwards
      if (pwmLeft > 0 && pwmRight > 0) {
        digitalWrite(MOTOR_LEFT_INPUT1, LOW);
        digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
        analogWrite(MOTOR_LEFT_ENABLE, pwmLeft);
        delay(steps);
        digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
        digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
        analogWrite(MOTOR_RIGHT_ENABLE, pwmRight);
        delay(steps);
        //backwards
      } else if(pwmLeft< 0 && pwmRight < 0){
        digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
        digitalWrite(MOTOR_LEFT_INPUT2, LOW);
        analogWrite(MOTOR_LEFT_ENABLE, pwmLeft * -1);
        delay(steps);
        digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
        digitalWrite(MOTOR_RIGHT_INPUT2, LOW);
        analogWrite(MOTOR_RIGHT_ENABLE, pwmRight * -1);
        delay(steps);

        //turn right
      } else if(pwmLeft< 0 && pwmRight > 0){
        digitalWrite(MOTOR_LEFT_INPUT1, LOW);
        digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
        analogWrite(MOTOR_LEFT_ENABLE, pwmLeft);
        delay(steps);
        digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
        digitalWrite(MOTOR_RIGHT_INPUT2, LOW);
        analogWrite(MOTOR_RIGHT_ENABLE, pwmRight * -1);
        delay(steps);
      } 
      //turn left
      else {
        digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
        digitalWrite(MOTOR_LEFT_INPUT2, LOW);
        analogWrite(MOTOR_LEFT_ENABLE, pwmLeft);
        delay(steps);
        digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
        digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
        analogWrite(MOTOR_RIGHT_ENABLE, pwmRight * -1);
        delay(steps);
      }
    }
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

//example of action
//PWMLeft:121  | PWMRight: 160 | clockwiseLeft: 1  | clockwiseRight: 0 | timeLeft: 939 | timeRight: 698  | servoAngle: 141
void Vehicle::performActions(int action[8][8], int PatternCount, int OutputNodes ) {
  for (int i = 0; i < PatternCount; i++) {
    for (int j = 0; j < OutputNodes - 1; j++) {
      Serial.print("action (");
      Serial.print(i);
      Serial.print(",");
      Serial.print(j);
      Serial.print(") = ");
      Serial.println(action[i][j]);
      delay(1000);
    }
  }
}

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
  sMid(TRIGGER_MID, ECHO_MID, MAX_DISTANCE), servo(), servoAngle(90) {}

//returns the average of 3 readings in cms
int Vehicle::readSonarCms() {
  return (sMid.convert_cm(sMid.ping_median(3)));
}

void Vehicle::runTestRoutine() {
  
      Serial.println("Testing sonar");
      for (int i = 0; i < 10; i++) {
        Serial.print("read sonar cms: ");
        Serial.println(readSonarCms());
        delay(1000);
      }


      Serial.println("Testing sonar");
      for (int i = 0; i < 10; i++) {
        Serial.print("read sonar normal: ");
        Serial.println((readSonarNormalized()));
        delay(1000);
      }
     /*
      
      
      Serial.println("Testing sonar finished");
      Serial.println();

      Serial.println("Testing servo");

      for (int i = 0; i < 180; i+=10) {
        Serial.print("Moving servo to: ");
        Serial.println(i);
        moveServo(i);
        delay(500);
      }

      Serial.println("Testing Left Motor 70 PWM for 2000 mms");
      digitalWrite(MOTOR_LEFT_INPUT1, LOW);
      digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
      analogWrite(MOTOR_LEFT_ENABLE, 70);
      delay(2000);
      analogWrite(MOTOR_LEFT_ENABLE, 0);

      Serial.println("Testing Right Motor 70 PWM for 2000 mms");
      digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
      digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
      analogWrite(MOTOR_RIGHT_ENABLE, 70);
      delay(2000);
      analogWrite(MOTOR_RIGHT_ENABLE, 0);

      Serial.println("Testing Left Motor 140 PWM for 2000 mms");
      digitalWrite(MOTOR_LEFT_INPUT1, LOW);
      digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
      analogWrite(MOTOR_LEFT_ENABLE, 140);
      delay(2000);
      analogWrite(MOTOR_LEFT_ENABLE, 0);

      Serial.println("Testing Right Motor 140 PWM for 2000 mms");
      digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
      digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
      analogWrite(MOTOR_RIGHT_ENABLE, 140);
      delay(2000);
      analogWrite(MOTOR_RIGHT_ENABLE, 0);

      Serial.println("Testing Left Motor 255  Max PWM for 2000 mms");
      digitalWrite(MOTOR_LEFT_INPUT1, LOW);
      digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
      analogWrite(MOTOR_LEFT_ENABLE, 255);
      delay(2000);
      analogWrite(MOTOR_LEFT_ENABLE, 0);

      Serial.println("Testing Right Motor 255 Max PWM for 2000 mms");
      digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
      digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
      analogWrite(MOTOR_RIGHT_ENABLE, 255);
      delay(2000);
      analogWrite(MOTOR_RIGHT_ENABLE, 0);

      Serial.println("both motor forwards: ");
      mappedDrive(0.8, 0.8);
      analogWrite(MOTOR_LEFT_ENABLE, 0);
      analogWrite(MOTOR_RIGHT_ENABLE, 0);

      Serial.println("both motor backwards: ");
      mappedDrive(0.2, 0.2);

      analogWrite(MOTOR_LEFT_ENABLE, 0);
      analogWrite(MOTOR_RIGHT_ENABLE, 0);


    Serial.println("test left turn: ");
    mappedDrive(0.0, 0.0);
    //analogWrite(MOTOR_LEFT_ENABLE, 0);
    // analogWrite(MOTOR_RIGHT_ENABLE, 0);

    //Serial.println("test right turn: ");
    //mappedDrive(0.8, 0.2);
    //analogWrite(MOTOR_LEFT_ENABLE, 0);
    //analogWrite(MOTOR_RIGHT_ENABLE, 0);
  */

  //Serial.println("Turning on sonar sweeping for 4 cycles");

  //sonarSweep(4);

}

void Vehicle::sonarSweep(int cycles) {
  int counter = 0;
  while (counter < cycles) {
    for (int i = 0; i < 100; i += 10) {
      Serial.println(i);
      moveServo(i);
    }
    for (int i = 100; i > 0; i -= 10) {
      Serial.println(i);
      moveServo(i);
    }

    counter++;
  }
  moveServo(44);

}

float Vehicle::readSonarNormalized() {
  return (float)map(readSonarCms(), 3, MAX_DISTANCE, 0, 100)/100;
}

int Vehicle::getServoAngle() {
  return servoAngle;
}

void Vehicle::moveServo(int angle) {

  int newAngle = map(angle, 0, 100, 0, 180);
  servoAngle = newAngle;
  servo.attach(SERVO_PIN);
  servo.write(newAngle);
  delay(300);

  //Sometimes detaching causes servo to lose position
  //servo.detach();
}

// params would be in range 0.0 to 1.0, need to be mapped to the 0 to 255 and the fucntion recognised which direction the motors need to spin
void Vehicle::mappedDrive(float pwmLeft, float pwmRight) {
  int steps = 100;

  Serial.println(pwmLeft);
  Serial.println(pwmRight);

  int mPwmLeft = map(pwmLeft * 100, 0, 100, -255, 255);
  int mPwmRight = map(pwmRight * 100, 0, 100, -255, 255);

  Serial.println(mPwmLeft);
  Serial.println(mPwmRight);

  //simultaneous drive loop
  for (int i = 0; i < 1000; i += 200) {
    //forwards
    if (mPwmLeft >= 0 && mPwmRight >= 0) {
      digitalWrite(MOTOR_LEFT_INPUT1, LOW);
      digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
      analogWrite(MOTOR_LEFT_ENABLE, mPwmLeft);
      delay(steps);

      digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
      digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
      analogWrite(MOTOR_RIGHT_ENABLE, mPwmRight);
      delay(steps);
    }
    //backwards
    else if (mPwmLeft < 0 && mPwmRight < 0 ) {
      digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
      digitalWrite(MOTOR_LEFT_INPUT2, LOW);
      analogWrite(MOTOR_LEFT_ENABLE, mPwmLeft);
      delay(steps);

      digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
      digitalWrite(MOTOR_RIGHT_INPUT2, LOW);
      analogWrite(MOTOR_RIGHT_ENABLE, mPwmRight);
      delay(steps);
    }
    //turn left
    else if (mPwmLeft < 0 && mPwmRight >= 0) {
      Serial.println("turned left");
      digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
      digitalWrite(MOTOR_LEFT_INPUT2, LOW);
      analogWrite(MOTOR_LEFT_ENABLE, mPwmLeft);
      delay(steps);
      digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
      digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
      analogWrite(MOTOR_RIGHT_ENABLE, mPwmRight);
      delay(steps);
    }
    //turn right
    else if (mPwmLeft >= 0 && mPwmRight < 0) {
      Serial.println("turned right");
      digitalWrite(MOTOR_LEFT_INPUT1, LOW);
      digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
      analogWrite(MOTOR_LEFT_ENABLE, mPwmLeft);
      delay(steps);
      digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
      digitalWrite(MOTOR_RIGHT_INPUT2, LOW);
      analogWrite(MOTOR_RIGHT_ENABLE, mPwmRight);
      delay(steps);
    }
  }
}

//true turn right, false turn left// counter clockwise on the left is turnig right
void Vehicle::drive(int pwmLeft, int pwmRight) {
  int steps = 100;

  for (int i = 0; i < 1000; i += 200) {

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
    } else if (pwmLeft < 0 && pwmRight < 0) {
      digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
      digitalWrite(MOTOR_LEFT_INPUT2, LOW);
      analogWrite(MOTOR_LEFT_ENABLE, pwmLeft * -1);
      delay(steps);
      digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
      digitalWrite(MOTOR_RIGHT_INPUT2, LOW);
      analogWrite(MOTOR_RIGHT_ENABLE, pwmRight * -1);
      delay(steps);

      //turn right
    } else if (pwmLeft < 0 && pwmRight > 0) {
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
  analogWrite(MOTOR_LEFT_ENABLE, 0);
  analogWrite(MOTOR_RIGHT_ENABLE, 0 );
}

//example of action
//PWMLeft:0.2  | PWMRight: 0.7 | servo: 0.4
void Vehicle::performActions(float Target[8][8], int PatternCount, int OutputNodes ) {
  for (int i = 0; i < PatternCount; i++) {
    for (int j = 0; j < OutputNodes - 1; j++) {
      Serial.print("action (");
      Serial.print(i);
      Serial.print(",");
      Serial.print(j);
      Serial.print(") = ");
      Serial.println(Target[i][j]);
      delay(1000);
    }
  }
}

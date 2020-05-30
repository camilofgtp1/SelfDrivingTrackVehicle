#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>
#include <Servo.h>
#include "Wire.h"

class Vehicle {

  public:
    Vehicle();

    void drive(int pwmLeft, int pwmRight);
    void moveServo(int angle);
    int getServoAngle();
    int readSonarCms();
    int readSonarNormalized();
    void fullStop();
    void performActions(float Target[8][8], int PatternCount, int OutputNodes);
    void gyro();
    
  private:
    NewPing sMid;
    Servo servo;
    int servoAngle;
};

#endif

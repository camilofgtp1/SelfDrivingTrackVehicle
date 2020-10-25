#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>
#include <Servo.h>
#include "Wire.h"

class Vehicle {

  public:
    Vehicle();

    void runTestRoutine();
    void drive(int pwmLeft, int pwmRight);
    void mappedDrive(float pwmLeft, float pwmRight);
    void moveServo(int angle);
    void sonarSweep(int cycles);

    int getServoAngle();
    int readSonarCms();
    float readSonarNormalized();

    void fullStop();
    void performActions(float Target[8][8], int PatternCount, int OutputNodes);
    void gyro();

  private:
    NewPing sMid;
    Servo servo;
    int servoAngle;
};

#endif

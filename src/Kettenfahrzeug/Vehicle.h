#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>
#include <Servo.h>
#include "Wire.h"

class Vehicle {

  public:
    Vehicle();

    void drive(int pwmLeft, int pwmRight, int turningTime, bool turnDirection);
    void moveServo(int angle, int turningSpeed);
    int readSonarCms();
    int readSonarNormalized();
    void fullStop();
    void performActions(int action[8][8], int PatternCount, int OutputNodes);
    void gyro();
    //char* Vehicle::convert_int16_to_str(int16_t i, char tmp_str);
    
  private:
    NewPing sMid;
    Servo servo;
};

#endif

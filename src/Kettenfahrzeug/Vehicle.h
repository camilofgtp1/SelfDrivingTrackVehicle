#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>
#include <Servo.h>
#include "Wire.h"

class Vehicle {

  public:
    Vehicle();

    void left(int turningTime, int turnSpeed, bool clockwise);
    void right(int turningTime, int turnSpeed, bool clockwise);
    void moveServo(int angle, int turningSpeed);
    int getMidDistance();
    void fullStop();
    void performActions(struct Action actions[], int duration);
    void gyro();
    char* Vehicle::convert_int16_to_str(int16_t i, char tmp_str);
    
  private:
    NewPing sMid;
    Servo servo;
};

#endif

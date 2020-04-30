#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>
#include <Servo.h>

class Vehicle {

  public:
    Vehicle();

    void left(int turningTime, int turnSpeed, bool clockwise);
    void right(int turningTime, int turnSpeed, bool clockwise);
    void moveServo(int angle, int turningSpeed);
    int getMidDistance();
    void fullStop();
    void performActions(struct Action actions[], int duration);
   
  private:
    NewPing sMid;
    Servo servo;
};

#endif

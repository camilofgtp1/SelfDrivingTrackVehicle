#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>
#include <Servo.h>

class Vehicle {

  public:
    Vehicle();

    void left(int turningTime, int turnSpeed, bool clockwise);
    void right(int turningTime, int turnSpeed, bool clockwise);
    
    void fullStop();

    void moveServo(int angle, int turningSpeed);
    float getMidDistance();

    void getRandomStates(int duration);

  private:
    NewPing sMid;
    Servo servo;
};

#endif

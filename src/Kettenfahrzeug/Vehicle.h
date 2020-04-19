#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>
#include <Servo.h>

class Vehicle {

  public:
    Vehicle();

    float performAction();
    
    void forwards(int time, int turnSpeed);
    void reverse(int time, int turnSpeed);
    
    void left(int turningTime, int turnSpeed);
    void right(int turningTime, int turnSpeed);
    
    float getMidDistance();

    void turnLeft(int turningTime, int turnSpeed);
    void turnRight(int turningTime, int turnSpeed);
    
    void fullStop();
    void testTurning();
    void sendToMapper();
    void moveServo(int angle, int turningSpeed);

  private:
    NewPing sMid;
    Servo servo;
};

#endif

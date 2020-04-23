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
    float getLeftDistance();

    float getMidDistance();

    void turnLeft(int turningTime, int turnSpeed);
    void turnRight(int turningTime, int turnSpeed);
    void fullStop();
    void testTurning();
    void demoMotors();
    void sendToMapper();
    void turnServo(int angle);
    float getServoAngle();
    

  private:
    NewPing sMid;
    Servo servo;
    int servoAngle;
};

#endif

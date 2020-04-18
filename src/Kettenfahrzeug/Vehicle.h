#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>

class Vehicle {

  public:
    Vehicle();
    void sendToMapper();
    int perform(int& action);
    int getObservation();
    
    void forwards(int time, int turnSpeed);
    void reverse(int time, int turnSpeed);
    
    void left(int turningTime, int turnSpeed);
    void right(int turningTime, int turnSpeed);

    float getLeftDistance();
    float getMidDistance();
    float getRightDistance();
    void turnLeft(int turningTime, int turnSpeed);
    void turnRight(int turningTime, int turnSpeed);
    void fullStop();
    void testTurning();
    void demoMotors();

  private:
    NewPing sLeft, sMid, sRight;
};

#endif

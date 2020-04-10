#ifndef Vehicle_h
#define Vehicle_h

#include <NewPing.h>

class Vehicle {

  public:
    Vehicle();
    void readSensors();
    int perform(int& action);
    int getObservation();
    void forwards();
    void reverse();
    void turnLeft(int turningTime, int turnSpeed);
    void turnRight(int turningTime, int turnSpeed);
    void fullStop();
    void testTurning();
    void demoMotors();

  private:
    NewPing sLeft, sMid, sRight;
    /*
        const int MOTOR_RIGHT_ENABLE = 6;
        const int MOTOR_RIGHT_INPUT1 = 7;
        const int MOTOR_RIGHT_INPUT2 = 8;

        const int MOTOR_LEFT_ENABLE = 11;
        const int MOTOR_LEFT_INPUT1 = 12;
        const int MOTOR_LEFT_INPUT2 = 13;

        const int MAX_DISTANCE = 200;

        const int TRIGGER_LEFT = 10;
        const int ECHO_LEFT = 9;
        const int TRIGGER_MID = 5;
        const int ECHO_MID = 4;
        const int TRIGGER_RIGHT = 3;
        const int ECHO_RIGHT = 2;

      replaced with define on cpp file

        const int vehicleSpeed = 125;

    */
};

#endif

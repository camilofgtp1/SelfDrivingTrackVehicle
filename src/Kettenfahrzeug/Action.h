#ifndef ACTION_H
#define ACTION_H

class Action {

public:
    Action(bool clockwiseLeft, bool clockwiseRight,
            int turningTimeLeft, int turningTimeRight,
            int PWMLeft, int PWMRight, int servoAngle);

    bool clockwiseLeft, clockwiseRight;
    int turningTimeLeft, turningTimeRight, PWMLeft, PWMRight, servoAngle;

    //todo: add reward
    float perform();

};

#endif

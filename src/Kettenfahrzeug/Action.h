#ifndef ACTION_H
#define ACTION_H

class Action {

public:
    Action(int motorLeftDirection, int motorRightDirection,
            int turningTimeLeft, int turningTimeRight,
            int PWMLeft, int PWMRight);

    Action(int turningTimeLeft, int turningTimeRight,
            int PWMLeft, int PWMRight);

    int motorLeftDirection;
    int motorRightDirection;
    int turningTimeLeft;
    int turningTimeRight;
    int PWMLeft;
    int PWMRight;

    float perform();
};


#endif ACTION_H

/* [ [sensorMid], [left, time, speed], [right, time, speed] ]

   V1:
    actions:
    left:time:speed
    right:time:speed

    observation:
    sensorMid
*/
#ifndef DQN_h
#define DQN_h
//TODO: refactor Q array to be multidimensional, at least Q[State][Actions]

class DQN{

public:
    DQN();

    float motorImpulseLeftMin;
    float motorImpulseLeftMax;
    float motorImpulseRightMin;
    float motorImpulseRightMax;

    void randomMeasurements(float session[], int duration);
    void randomTimes(float arr[], int duration);
    void randomSpeeds(float arr[], int duration);
    void randomMotor(float arr[], int duration);
    void printArr(float arr[], int arrayLength);

    float getAction();
    float getReward();
    
};

#endif

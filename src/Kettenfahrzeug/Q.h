#ifndef Q_h
#define Q_h

class Q{

public:
    Q();
    float gamma;
    float epsilon;  //Wahrschenlichkeit einer zufälligen Aktionsnauswahl
    float alpha;    //Gewicht für die Vergesslichkeit des Agentes

    float sensorLeft;
    float sensorMid;
    float sensorRight;

    float motorImpulseLeftMin;
    float motorImpulseLeftMax;
    float motorImpulseRightMin;
    float motorImpulseRightMax;

    void randomMeasurements(float session[], int duration);
    void randomTimes(float arr[], int duration);
    void randomSpeeds(float arr[], int duration);
    void randomMotor(float arr[], int duration);
    void printArr(float arr[], int arrayLength);
    
};

#endif

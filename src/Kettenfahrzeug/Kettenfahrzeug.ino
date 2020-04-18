/*
  https://www.arduino.cc/en/Reference/RobotMotorsWrite
  Robot.motorsWrite(speedLeft, speedRight) to replace cumbersome functions to controlling the movement

  TODO: Arduino can connect to laptop using wirless network to send sensor data and recieve manual control instructions
  TODO: Arduino can connecto to RC Controller
  TODO: Arduino is powered by battery
  TODO: The turning can be made by giving an angle in degrees
  TODO: The processing sketch maps the sensor data at scale and can be zoomed in and out
  TODO: QLearning.md algorithm gives actions that move the vehicle for the amount of time specified
  TODO: Mobile app shows room, vehicle finds the best way to a selected spot
  TODO: Easy Mode: QLearning.md outputs one of 4 actions corresponding to the direction it should drive to
        Hard Mode: QLearning.md ouputs outputs speed and direction of the spinning of the motors
*/
#include "Vehicle.h"
#include "Q.h"

Vehicle v;
Q q;

int steps = 20;
float measurements[20];
float leftMotor[20];
float rightMotor[20];
float turningTimes[20];
float turningSpeeds[20];

float gamma;
float alpha;
float epsilon;

float stateSensorMid;
int numActions= ;
int numStates;


//has initial positions , nothing else
void setup() {
  Serial.begin(9600);
  q.randomMeasurements(measurements, steps);
  q.randomMotor(leftMotor, steps);
  q.randomMotor(rightMotor, steps);
  q.randomSpeeds(turningSpeeds, steps);
  q.randomTimes(turningTimes, steps);

  //Serial.println("measurements");
  //q.printArr(measurements, steps);

  Serial.println("right motor: ");
  q.printArr(rightMotor, steps);

  Serial.println("left motor: ");
  q.printArr(leftMotor, steps);

  Serial.println("turning times: ");
  q.printArr(turningTimes, steps);

  Serial.println("turning speeds");
  q.printArr(turningSpeeds, steps);

}

int t = 0;
const float explorationConst = (explorationMinutes * 60.0) / ((float(rollDelay)) / 1000.0); //this is the approximate exploration time in units of number of times through the loop

void loop(){
    t++;
    epsilon = exp(-float(t) / explorationConst);

    // a was between 0 and 3, also, it return which motor to move and how
    a = getAction();
}

/*returns and action from the list
 * TODO: Make an action class which returns and object with spin time and speed, one additional constructor for the servo
 * Action::a, time, speed
 * 0: left
 * 1: right
 * 2: Sensor
*/
float val;
float Q[numStates][numActions];
int getAction(){
    int action;
    float valMax = -10000000.0;
    int aMax;
    // s = state index
    //val = Q[s][0];
    if(val > valMax){
        valMax = val;
        aMax = 0;
    }
}

void randomSession(int duration){
  for (int i = 0; i < steps; i++) {
    Serial.println(i);
    if (leftMotor[i] == 1.00 && rightMotor[i] == 0.00) {

      Serial.println("left: ");
      Serial.print("speed: ");
      Serial.println(turningSpeeds[i]);
      Serial.print("time: ");
      Serial.println(turningTimes[i]);

      v.left(turningTimes[i], turningSpeeds[i]);
    } else if (leftMotor[i] == 0.00 && rightMotor[i] == 1.00) {

        Serial.println("right: ");
        Serial.print("speed: ");
        Serial.println(turningSpeeds[i]);
        Serial.print("time: ");
        Serial.println(turningTimes[i]);

        v.right(turningTimes[i], turningSpeeds[i]);
      } else if (rightMotor[steps] == 1.00 && leftMotor[i] == 1.00) {

        Serial.println("both");
        Serial.print("speed: ");
        Serial.println(turningSpeeds[i]);
        Serial.print("time: ");
        Serial.println(turningTimes[i]);

        v.forwards(turningTimes[i], turningSpeeds[i]);
      } else {
      Serial.println("none");
      delay(turningTimes[i]);
    }

    delay(1500);


  }
  Serial.println("end of epoch ");
}

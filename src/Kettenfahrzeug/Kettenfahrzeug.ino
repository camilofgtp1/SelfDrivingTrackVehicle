/*
   TODO: QLearning.md algorithm gives actions that move the vehicle for the amount of time specified
   TODO: Implent Markovs decision process
   TODO: Implement https://github.com/GiorgosXou/NeuralNetworks NN Library for Arduino
   TODO: Vehicle moves away from the walls sending rotation direction of motors, time and speed each 500 milliseconds
   TODO: Implement and action class for the action space of the vehicle
*/
#include "Vehicle.h"
#include "DQN.h"
#include "Action.h"
#include "NeuralNetwork.h"

#define DURATION 20

Vehicle vehicle;
DQN q;

//NeuralNetwork NN(3, 4, 4, 3);


int replayMemory = 20;
float initialRandomStates[DURATION];

int numStates;
int numActions;

float leftMotor[20];
float rightMotor[20];
float turningTimes[20];
float measurements[20];
float turningSpeeds[20];

float gamma;
float epsilon;  //Wahrschenlichkeit einer zufälligen Aktionsnauswahl
float alpha;    //Gewicht für die Vergesslichkeit des Agentes
float stateSensorMid;

//has initi
int t = 0;
//const float explorationConst = (explorationMinutes * 60.0) / ((float(rollDelay)) /1000.0);
//this is the approximate exploration time in units of number of times through the loop

float val;
// float Q[numalStates][numActions]; positions, nothing else
void setup() {
  Serial.begin(9600);
}

void loop() {

 
  //t++;
  //    epsilon = exp(-float(t) / explorationConst);

  // a was between 0 and 3, also, it return which motor to move and how
  //    a = getAction();
}


int getAction() {
  int action;
  float valMax = -10000000.0;
  int aMax;
  // s = state index
  //val = Q[s][0];
  if (val > valMax) {
    valMax = val;
    aMax = 0;
  }


}

void randomSession(int duration) {
  for (int i = 0; i < replayMemory; i++) {
    Serial.println(i);
    if (leftMotor[i] == 1.00 && rightMotor[i] == 0.00) {

      Serial.println("left: ");
      Serial.print("speed: ");
      Serial.println(turningSpeeds[i]);
      Serial.print("time: ");
      Serial.println(turningTimes[i]);

      vehicle.left(turningTimes[i], turningSpeeds[i]);
    } else if (leftMotor[i] == 0.00 && rightMotor[i] == 1.00) {

      Serial.println("right: ");
      Serial.print("speed: ");
      Serial.println(turningSpeeds[i]);
      Serial.print("time: ");
      Serial.println(turningTimes[i]);

      vehicle.right(turningTimes[i], turningSpeeds[i]);
    } else if (rightMotor[replayMemory] == 1.00 && leftMotor[i] == 1.00) {

      Serial.println("both");
      Serial.print("speed: ");
      Serial.println(turningSpeeds[i]);
      Serial.print("time: ");
      Serial.println(turningTimes[i]);

      vehicle.forwards(turningTimes[i], turningSpeeds[i]);
    } else {
      Serial.println("none");
      delay(turningTimes[i]);
    }

    delay(1500);


  }
  Serial.println("end of epoch ");
}



void launchRandom() {

  q.randomMeasurements(measurements, replayMemory);
  q.randomMotor(leftMotor, replayMemory);
  q.randomMotor(rightMotor, replayMemory);
  q.randomSpeeds(turningSpeeds, replayMemory);
  q.randomTimes(turningTimes, replayMemory);

  //Serial.println("measurements");
  //q.printArr(measurements, replayMemory);

  Serial.println("right motor: ");
  q.printArr(rightMotor, replayMemory);

  Serial.println("left motor: ");
  q.printArr(leftMotor, replayMemory);

  Serial.println("turning times: ");
  q.printArr(turningTimes, replayMemory);

  Serial.println("turning speeds");
  q.printArr(turningSpeeds, replayMemory);

}

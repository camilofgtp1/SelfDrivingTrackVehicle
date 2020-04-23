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

//TODO: CURRENT, define state to be passed as inputs to the neural network
/*
  the state is made of observations of the environment
  one time step of the vehicle's state is composed by:

  distance sensor
  servo angle
  pitch
  yaw
  roll


*/


//NeuralNetwork NN(3, 4, 4, 3);

int replayMemory = DURATION;
float initialRandomStates[DURATION];

int numStates;
int numActions;

float leftMotor[DURATION];
float rightMotor[DURATION];
float turningTimes[DURATION];
float measurements[DURATION];
float turningSpeeds[DURATION];

float gamma;
float epsilon;  //Wahrschenlichkeit einer zufälligen Aktionsnauswahl
float alpha;    //Gewicht für die Vergesslichkeit des Agentes
float stateSensorMid;


//first an array of ultrasonic sensor measurements
//second servo angle 
float state[DURATION];

void getStates() {

  for (int i = 0; i < replayMemory; i++) {
    state[i] = vehicle.getMidDistance();
    Serial.print("state[i]:");
    Serial.println(state[i]);
  }
}
void setup() {
  Serial.begin(9600);
  /*
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
  */
}



void loop() {


}


void randomSession() {

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

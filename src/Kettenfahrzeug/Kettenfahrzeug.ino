/*
   CURRENT: functions with random state inputs on an array, to init the network?
   TODO: QLearning.md algorithm gives actions that move the vehicle for the amount of time specified
   TODO: Implent Markovs decision process
   TODO: Implement https://github.com/GiorgosXou/NeuralNetworks NN Library for Arduino
   TODO: Vehicle moves away from the walls sending rotation direction of motors, time and speed each 500 milliseconds
   TODO: Implement and action class for the action space of the vehicle

  State:
  distance sensor int
  servo angle int

  Actions:
  int moveleft
  int moveright
  bool directionleft
  bool directionsright
  int timeleft
  int timeright
  int servo
  bool break
*/

#include "Vehicle.h"
#include "DQN.h"
#include "NeuralNetwork.h"

#include "Action.h"
#include "State.h"

#define NumberOf(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))
#define DURATION 50

Vehicle vehicle;
DQN dqn;

int replayMemory = DURATION;

float gamma;
float epsilon;  //Wahrschenlichkeit einer zufälligen Aktionsnauswahl
float alpha;    //Gewicht für die Vergesslichkeit des Agentes
int session[DURATION];

struct State state[DURATION];
struct Action actions[DURATION];


void setup() {
  Serial.begin(9600);
  const unsigned int layers[] = {2, 3, 5, 7};
  randomStates();
  NeuralNetwork NN(layers, weights, biases, NumberOf(layers));
}


void loop() {
  //Serial.println(vehicle.getMidDistance());
  //vehicle.moveServo(0, 1000);

  //vehicle.getRandomStates(session[DURATION], DURATION);
  //vehicle.performActions(actions, DURATION);
  //Serial.println(vehicle.getMidDistance());
  //vehicle.moveServo(82, 1000);
  //Serial.println(vehicle.getMidDistance());
  //vehicle.moveServo(174, 1000);
  // Serial.println(vehicle.getMidDistance());
  //vehicle.moveServo(82, 1000);
}

void randomStates() {

  //init random states
  for (int i = 0; i < DURATION; i++) {
    state[i].sonar = random(0, 200);
    state[i].servo = random(0, 180);

    Serial.print("sonar:");
    Serial.print(state[i].sonar);
    Serial.print("\t| servo: ");
    Serial.print(state[i].servo);
    delay(500);
  }
}



/*
  // random actions for each second
  for (int i = 0; i < DURATION; i++) {
  actions[i].PWMLeft  = random(80, 255);
  actions[i].PWMRight = random(80, 255);
  actions[i].clockwiseLeft  = random(0, 2) == 0 ? false : true;
  actions[i].clockwiseRight = random(0, 2) == 0 ? false : true;
  actions[i].timeLeft  = random(0, 500);
  actions[i].timeRight = random(0, 500);
  actions[i].servoAngle  = random(0, 180);
  }

    Serial.print("PWMLeft:");
    Serial.print(actions[i].PWMLeft);
    Serial.print("\t| PWMRight: ");
    Serial.print(actions[i].PWMRight);
    Serial.print("\t| clockwiseLeft: ");
    Serial.print(actions[i].clockwiseLeft);
    Serial.print("\t| clockwiseRight: ");
    Serial.print(actions[i].clockwiseRight);
    Serial.print("\t| timeLeft: ");
    Serial.print(actions[i].timeLeft);
    Serial.print("\t| timeRight: ");
    Serial.print(actions[i].timeRight);
    Serial.print("\t| servoAngle: ");
    Serial.println(actions[i].servoAngle);
    //delay(500);
*/

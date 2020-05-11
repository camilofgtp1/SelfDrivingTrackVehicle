/*
  State:
  distance sensor int
  servo angle int

  Actions:
  int PWMLeft;
  int PWMRight;
  bool clockwiseLeft;
  bool clockwiseRight;
  int timeLeft;
  int timeRight;
  int servoAngle;

CURRENT IMPLEMENTING:
https://planetachatbot.com/q-learning-con-arduino-crawling-robot-espanol-5eb0acf5aaaf

*/

#include "Vehicle.h"
#include "Action.h"
#define DURATION 50


Vehicle vehicle;

// distance:120 | servoAngle: 90 - 8 offset
int Q[6][2] = {
  {0, 0 },
  {0, 0 },
  {0, 0 },
  {0, 0 },
  {0, 0 },
  {0, 0 }
};

int action = 0;
int state = 0;
int cont = 0;
float gamma = 0.8;
float Qmax = 0;
int x = 0;
int goal = 15;


void setup() {
  Serial.begin(9600);

  //PWMLeft:121  | PWMRight: 160 | clockwiseLeft: 1  | clockwiseRight: 0 | timeLeft: 939 | timeRight: 698  | servoAngle: 141 | Reward: 1000
  int R[6][8] = {
    {120, 120, 1, 0, 1000, 1000, 180, 0},
    {120, 120, 1, 1, 1000, 1000, 82, 1000},
    {120, 120, 0, 1, 1000, 1000, 82, 0},
    {120, 120, 0, 0, 1000, 1000, 82, 0 },
    {120, 120, 0, 1, 1000, 1000, 82, 0 },
    {120, 120, 0, 1, 1000, 1000, 82, 0 },
  };

}

void loop() {

}

void randomStates() {
  /*
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
  */
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

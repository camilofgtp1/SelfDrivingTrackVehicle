#include "DQN.h"
#include <Arduino.h>

DQN::DQN() {

}


/* [ [sensorMid], [left, time, speed], [right, time, speed] ]

   V1:
    actions:
    left:time:speed
    right:time:speed

    observation:
    sensorMid
*/

/*
   one session is the set of actions taken
   by the agent in the given time in seconds
   Here is the comparisson session with random actions
*/
void DQN::randomMeasurements(float session[], int duration) {
  for (int i = 0; i < duration; i++) {
    session[i] = (random(0, 4000) / 10);
  }
}

void DQN::randomMotor(float arr[], int duration){
  for (int i = 0; i < duration; i++) {
    arr[i] = float(random(0, 2));

  }
}

void DQN::randomSpeeds(float arr[], int duration){
  for (int i = 0; i < duration; i++) {
    arr[i] = float(random(80, 256));
  }
}

void DQN::randomTimes(float arr[], int duration){
  for (int i = 0; i < duration; i++) {
    arr[i] = (random(200, 2000));
  }
}

void DQN::printArr(float arr[], int arrayLength) {
  //Serial.print("\n__ArrayLenght: ");
  //Serial.println(arrayLength);
  for (int i = 0; i < arrayLength; i++ ) {
    Serial.println(arr[i]);
  }
  Serial.println("___");
}

void getAction(){

}

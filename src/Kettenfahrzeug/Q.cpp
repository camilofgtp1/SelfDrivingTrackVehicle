#include "Q.h"

//todo: organize action array
//todo: generate random
//todo: save it to file
//todo: read from file
//todo: upload to robot
//todo: enjoy
//todo: real Qlearning
#include <Arduino.h>

Q::Q() {

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
void Q::randomMeasurements(float session[], int duration) {
  for (int i = 0; i < duration; i++) {
    session[i] = (random(0, 4000) / 10);
  }
}

void Q::randomMotor(float arr[], int duration){
  for (int i = 0; i < duration; i++) {
    arr[i] = float(random(0, 2));

  }
}

void Q::randomSpeeds(float arr[], int duration){
  for (int i = 0; i < duration; i++) {
    arr[i] = float(random(80, 255));
  }
}

void Q::randomTimes(float arr[], int duration){
  for (int i = 0; i < duration; i++) {
    arr[i] = (random(100, 1000));
  }
}

void Q::printArr(float arr[], int arrayLength) {
  //Serial.print("\n__ArrayLenght: ");
  //Serial.println(arrayLength);
  for (int i = 0; i < arrayLength; i++ ) {
    Serial.println(arr[i]);
  }
  Serial.println("___");
}

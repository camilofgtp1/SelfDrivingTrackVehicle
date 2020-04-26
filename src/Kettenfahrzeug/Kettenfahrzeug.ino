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
#include "Wire.h"

#define DURATION 20

Vehicle vehicle;
DQN q;

const int MPU_ADDR = 0x68;
int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;
char tmp_str[7];

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

//NeuralNetwork NN(3, 4, 4, 3);
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



float val;
// float Q[numalStates][numActions]; positions, nothing else
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}
//todo: callibrate module
//check out https://www.youtube.com/watch?v=dzjRk3qdCzk for heeading calculation

void compass() {
   Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  // print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();

  // delay
  delay(1000);

}

void loop() {

  compass();
  Serial.print("midSe : ");
  delay(1000);
  Serial.println(vehicle.getMidDistance());
  //vehicle.forwards(10000, 120);
  //t++;
  //    epsilon = exp(-float(t) / explorationConst);

  // a was between 0 and 3, also, it return which motor to move and how
  //    a = getAction();
}


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

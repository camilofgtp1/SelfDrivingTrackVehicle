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
  yaw int

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
#include "Wire.h"
#include "Action.h"
#include "State.h"

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

  //init random states
  for (int i = 0; i < DURATION; i++) {
    state[i].sonar = random(0, 200);
    state[i].servo = random(0, 180);
    state[i].yaw = random(0, 360);

    Serial.print("sonar:");
    Serial.print(state[i].sonar);
    Serial.print("\t| servo: ");
    Serial.print(state[i].servo);
    Serial.print("\t| yaw: ");
    Serial.println(state[i].yaw);
    //delay(500);
  }

  // random actions for each second
  for (int i = 0; i < DURATION; i++) {
    actions[i].PWMLeft  = random(80, 255);
    actions[i].PWMRight = random(80, 255);
    actions[i].clockwiseLeft  = random(0, 2) == 0 ? false : true;
    actions[i].clockwiseRight = random(0, 2) == 0 ? false : true;
    actions[i].timeLeft  = random(0, 500);
    actions[i].timeRight = random(0, 500);
    actions[i].servoAngle  = random(0, 180);

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
  }


  /*
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
  */
}


void loop() {

  //Serial.println(vehicle.getMidDistance());
  //vehicle.getRandomStates(session[DURATION], DURATION);
  
  vehicle.performActions(actions, DURATION);
  vehicle.moveServo(180, 100);
    delay(1000);

  vehicle.moveServo(0, 100);
    delay(1000);


}



/*
  int16_t accelerometer_x, accelerometer_y, accelerometer_z;
  const int MPU_ADDR = 0x68;
  int16_t gyro_x, gyro_y, gyro_z;
  int16_t temperature;
  char tmp_str[7];

  char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
  }

  void compass() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read() << 8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  // print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print(" | tmp = "); Serial.print(temperature / 340.00 + 36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();

  // delay
  delay(1000);

  }

*/

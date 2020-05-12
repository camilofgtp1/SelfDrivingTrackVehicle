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

  Bellmans equation:

  current
  state    reward  discount factor    greatest of Q(new state, new action)
  action
  Q(s,a) = r +     gamma            * max(Q(s', a'))

*/

#include "Vehicle.h"
#include "Action.h"
#include <TinyMPU6050.h>

#define DURATION 50


Vehicle vehicle;

// distance:120 | servoAngle: 90 - 8 offset
//states along rows, actions along columns
/**
   Q matrix init zeros
   for each episode, select random state
   select one of all possible actions for current state
   perform action, go to next state
   for all possible actions from new state, select the one with highest Q value (reward?)
   update q table
   set next state as the current state
   if goal state reached finish

*/

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

MPU6050 mpu (Wire);

void setup() {
  Serial.begin(9600);

  // Initialization
  mpu.Initialize();

  // Calibration
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");
  Serial.println("Offsets:");
  Serial.print("GyroX Offset = ");
  Serial.println(mpu.GetGyroXOffset());
  Serial.print("GyroY Offset = ");
  Serial.println(mpu.GetGyroYOffset());
  Serial.print("GyroZ Offset = ");
  Serial.println(mpu.GetGyroZOffset());

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
  compass();
}

void compass() {

 //set up sensitivy gyro
    Wire.beginTransmission(0x1B);
    Wire.write(1);
    Wire.endTransmission(false);

    //set up sensitivy accelerometer
    Wire.beginTransmission(0x1C);
    Wire.write(1);
    Wire.endTransmission(false);
 
  mpu.Execute();
  Serial.print("AngX = ");
  Serial.print(mpu.GetAngX());
  Serial.print("  /  AngY = ");
  Serial.print(mpu.GetAngY());
  Serial.print("  /  AngZ = ");
  Serial.println(mpu.GetAngZ());
 
  /*
    Wire.beginTransmission(0x68);
    Wire.write(0x3B); // start at register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40
    Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(0x68, 14, true); // request 14 registers

    //set up sensitivy gyro
    Wire.beginTransmission(0x1B);
    Wire.write(2);
    Wire.endTransmission(false);

    //set up sensitivy accelerometer
    Wire.beginTransmission(0x1C);
    Wire.write(3);
    Wire.endTransmission(false);

    // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
    accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    //accelerometer_x = accelerometer_x + 32768;
    Serial.print("accelX: ");
    Serial.print(accelerometer_x);
    accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
    temperature = Wire.read() << 8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
    gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
    gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
    gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
    Serial.print("\t| gyroX: "); Serial.println(gyro_x);
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
        (this is for +-2 G sensitivity)
        raw acc value / 16384
        write to set sensitivity
        FS_SEL  -  Register 1B, Bits 3 and 4 (gyroscope sensitivity)
        Value written to FS_SEL at 0x1B  -  sensitivity:
        0 - +-250
        1 - +-500
        2 - +-1000
        3 - +-2000
        AFS_SEL  -  Register 1C, Bits 3 and 4 (accelerometer sensitivity)
        Value written to AFS_SEL at 0x1C  -  sensitivity:
        0 - +-2
        1 - +-4
        2 - +-8
        3 - +-16
        int xAng = map(acceleration_x,minVal,maxVal,-90,90);
        x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  */


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

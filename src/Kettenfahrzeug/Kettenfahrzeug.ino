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

#include "Action.h"
#include "State.h"
#include <TinyMPU6050.h>


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


MPU6050 mpu (Wire);

long int accelerometer_x;
long int gyro_x;

/*
  int16_t accelerometer_y, accelerometer_z; // variables for accelerometer raw data
  int16_t gyro_y, gyro_z; // variables for gyro raw data
  int16_t temperature; // variables for temperature data
  char tmp_str[7]; // temporary variable used in convert function
  int minVal = 265; int maxVal = 402;
  double x; double y; double z;
*/

/*
  char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
  }
*/

const int MPU = 0x68;
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
void setup() {


/*
  // Initialization
  mpu.Initialize();

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
      delay(1000);
  */
/*
  Wire.begin();
  Wire.beginTransmission(0x68); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register //power
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  //set up sensitivy gyro
  Wire.beginTransmission(0x1B);
  Wire.write(0);
  Wire.endTransmission(true);

  //set up sensitivy accelerometer
  Wire.beginTransmission(0x1C);
  Wire.write(3);
  Wire.endTransmission(true);

*/

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

  // random actions for each second
  for (int i = 0; i < DURATION; i++) {
    actions[i].PWMLeft  = random(80, 255);
    actions[i].PWMRight = random(80, 255);
    actions[i].clockwiseLeft  = random(0, 2) == 0 ? false : true;
    actions[i].clockwiseRight = random(0, 2) == 0 ? false : true;
    actions[i].timeLeft  = random(0, 500);
    actions[i].timeRight = random(0, 500);
    actions[i].servoAngle  = random(0, 180);

    /*
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
  }

  Serial.begin(9600);

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

  //vehicle.gyro();
  //compass();
  //libTest();



}

void plotGyro() {
mpu.Execute();

  Serial.print(mpu.GetAngX());

  Serial.print(mpu.GetAngY());

  Serial.println(mpu.GetAngZ());

}

//mpu libraries test exclude until new sensors arrive
void libTest() {
  mpu.Execute();
  Serial.print("AngX = ");
  Serial.print(mpu.GetAngX());
  Serial.print("  /  AngY = ");
  Serial.print(mpu.GetAngY());
  Serial.print("  /  AngZ = ");
  Serial.println(mpu.GetAngZ());
  delay(1000);
}
void compass() {

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 12, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  //Serial.print("Accelerometer: ");
  //Serial.print("X = "); 
  Serial.print(AcX + 32768);
 /* Serial.print(" | Y = "); Serial.print(AcY + 32768);
  Serial.print(" | Z = "); Serial.println(AcZ - 8548);

  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX + 4310);
  Serial.print(" | Y = "); Serial.print(GyY + 400);
  Serial.print(" | Z = "); Serial.println(GyZ - 260);
  Serial.println(" ");
  delay(1000);
*/
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

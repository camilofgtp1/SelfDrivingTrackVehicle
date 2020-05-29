#include "Vehicle.h"
#include <TinyMPU6050.h>

Vehicle vehicle;
MPU6050 mpu (Wire);

const int PatternCount = 8;
const int InputNodes = 3;
const int HiddenNodes = 4;
const int OutputNodes = 3;
const float LearningRate = 0.3;
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;
const float Success = 0.0004;

//Input states
// ultrasonicSensor: 0.0 to 1.0 | servoAngle : 0.0 to 1.0, right to left | gyroZ: 0 is south, 0.5 is north, 0.25 is east, 0.75 is west
float Input[PatternCount][InputNodes] = {
  {0.1, 0,  0  }, //01 close to obstacle, servo to the right, heading south
  {0.1, 0,  0.5}, //02 close to obstacle, servo to the right, heading north
  {0.1, 1,  0  }, //03 close to obstacle, servo to the left, heading south
  {0.1, 1,  0.5}, //04 close to obstacle, servo to the left, heading north
  {0.1, 50, 0  }, //05 close from obstacle, servo to the front, heading south
  {0.1, 50, 0.5}, //06 close from obstacle, servo to the front, heading north
  {0.9, 1,  0  }, //07 far from obstacle, servo to the left, heading south
  {0.9, 1,  0.5}  //08 far from obstacle, servo to the left, heading north};
};

//Reference Outputs
//PWMLeft:0.0 to 1.0 | PWMRight: 0. to 1.0 | servoAngle: 0 to 1.0
const float Target[PatternCount][OutputNodes] = {
  {0.3, 0.70, 1},     //01 turn left
  {0.3, 0.70, 1},     //02 turn left
  {0.7, 0.30, 1},     //03 turn right
  {0.7, 0.30, 1},     //04 turn right
  {0.30, 0.30, 0.50 },//05 backwards
  {0.30, 0.30, 0.50 },//05 backwards
  {0.80, 0.80, 0.50 },//07 forwards
  {0.80, 0.80, 0.50}  //08 forwards
};

int i, j, p, q, r;
int ReportEvery1000;
int RandomizedIndex[PatternCount];
long  TrainingCycle;
float Rando;
float Error;
float Accum;
float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes + 1][HiddenNodes];
float OutputWeights[HiddenNodes + 1][OutputNodes];
float HiddenDelta[HiddenNodes];
float OutputDelta[OutputNodes];
float ChangeHiddenWeights[InputNodes + 1][HiddenNodes];
float ChangeOutputWeights[HiddenNodes + 1][OutputNodes];

void startMPU() {

  //set up sensitivy gyro
  Wire.beginTransmission(0x1B);
  Wire.write(1);
  Wire.endTransmission(false);

  //set up sensitivy accelerometer
  Wire.beginTransmission(0x1C);
  Wire.write(1);
  Wire.endTransmission(false);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");
}

void setup() {
  Serial.begin(9600);
  // Initialization
  mpu.Initialize();
  randomSeed(analogRead(3));
  ReportEvery1000 = 1;
  for ( p = 0 ; p < PatternCount ; p++ ) {
    RandomizedIndex[p] = p ;
  }
  train();
  //map nn output before passing to drive function
  /*
    float testLeft= 0.8;
    float testRight = 0.2;
    int mappedLeft = map(testLeft*100, 0, 100, -255, 255);
    int mappedRight = map(testRight*100, 0, 100, -255, 255);
    vehicle.drive(mappedLeft, mappedRight, 1000, false);
  */
}

void loop() {
  initWeights();
  Serial.println ();
  Serial.println();
  Serial.print ("TrainingCycle: ");
  Serial.print (TrainingCycle);
  Serial.print ("  Error = ");
  Serial.println (Error, 5);

  Serial.print(Error);
  toTerminal();

  Serial.println ();
  Serial.println ();
  Serial.println ("Training Set Solved! ");
  Serial.println ("--------");
  Serial.println ();
  Serial.println ();
  ReportEvery1000 = 1;
}

//Scan servo range left to right and right to left
//Serial.println(float(vehicle.readSonarNormalized() / 100.0));

//vehicle.moveServo(0, 1000);  // 0 is to the right, 100 to the left, function receives and int from 0 to 100
//Serial.print("Z axis: ");
//Serial.println(mapZAxis() / 100.0);


/*
  for (int i = 0; i <= 100; i += 10 ) {
  Serial.println(float(vehicle.readSonarNormalized() / 100.0));
  vehicle.moveServo(i, 500);
  }

  for (int i = 100; i >= 0; i -= 10 ) {
  Serial.println(float(vehicle.readSonarNormalized() / 100.0));
  vehicle.moveServo(i, 500);

  }
*/

int mapZAxis() {
  mpu.Execute();
  int mapped = map(mpu.GetAngZ(), -179.9, 179.9, 0, 100);
  return mapped;
}

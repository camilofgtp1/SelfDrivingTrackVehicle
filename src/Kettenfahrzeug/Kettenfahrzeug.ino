#include "Vehicle.h"
#include <TinyMPU6050.h>

Vehicle vehicle;
MPU6050 mpu (Wire);

const int PatternCount = 4;
const int InputNodes = 2;
const int OutputNodes = 2;
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;

const float Success = 0.06;
const int HiddenNodes = 3;
const float LearningRate = 0.4;

//Reference Input states, 
// ultrasonicSensor: 0.0 to 1.0 | gyroZ: 0 is south, 0.5 is north, 0.25 is east, 0.75 is west
float Input[PatternCount][InputNodes] = {
  {0.1, 0.1},   //01 close to obstacle, heading south
  {0.1, 0.5},   //02 close to obstacle, heading north
  {0.9, 0.1},   //07 far from obstacle, heading south
  {0.9, 0.5}    //08 far from obstacle,  heading north};
};

//Reference Outputs
//PWMLeft:0.0 to 1.0 | PWMRight: 0. to 1.0 | servoAngle: 0 to 1.0
const float Target[PatternCount][OutputNodes] = {
  {0.1, 0.9},     //01 turn left
  {0.9, 0.9},     //04 turn right
  {0.10, 0.50 },  //05 backwards
  {0.90, 0.50}    //08 forwards
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
  drive();
}

int mapZAxis() {
  mpu.Execute();
  int mapped = map(mpu.GetAngZ(), -179.9, 179.9, 0, 100);
  return mapped;
}


//PWMLeft:0.0 to 1.0 | PWMRight: 0. to 1.0 | servoAngle: 0 to 1.0
void drive()
{
  if (Success < Error) {

    Serial.println("NN not Trained");
  }
  while (Error < Success) {

    float TestInput[] = {0, 0, 0};

    float sonarReading = vehicle.readSonarNormalized() / 100.0;
    float headingAngle = mapZAxis() / 100.0;

    TestInput[0] = sonarReading;
    TestInput[1] = headingAngle;

    /*
        Serial.print("sonar: ");
        Serial.print(TestInput[0]);
        Serial.print("| servoAngle: ");
        Serial.print(TestInput[1]);
        Serial.print("| gyroZ: ");
        Serial.print(TestInput[2]);
        Serial.println();
    */
    InputToOutput(TestInput[0], TestInput[1]); //INPUT to ANN to obtain OUTPUT

    Serial.print("pwmLeft: ");
    Serial.print(Output[0]);
    Serial.print("| pwmRight: ");
    Serial.print(Output[1]);
    Serial.println();
    
    //vehicle.drive((Output[0] * 100)+100, (Output[1] *100)+100);

 
  }
}


void InputToOutput(float input0, float input1)
{

  float TestInput[] = {0.0, 0.0};
  TestInput[0] = input0;
  TestInput[1] = input1;


  /***********************************
    Compute hidden layer activations
  ************************************/

  for ( i = 0 ; i < HiddenNodes ; i++ ) {
    Accum = HiddenWeights[InputNodes][i] ;
    for ( j = 0 ; j < InputNodes ; j++ ) {
      Accum += TestInput[j] * HiddenWeights[j][i] ;
    }
    Hidden[i] = 1.0 / (1.0 + exp(-Accum)) ;
  }

  /*******************************************************
    Compute output layer activations and calculate errors
  ********************************************************/

  for ( i = 0 ; i < OutputNodes ; i++ ) {
    Accum = OutputWeights[HiddenNodes][i] ;
    for ( j = 0 ; j < HiddenNodes ; j++ ) {
      Accum += Hidden[j] * OutputWeights[j][i] ;
    }
    Output[i] = 1.0 / (1.0 + exp(-Accum));
  }

}

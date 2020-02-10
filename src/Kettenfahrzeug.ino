
#include <NewPing.h>
#include <L298N.h>

//Ultrasound senson Pins
#define TRIGGER_LEFT 10
#define ECHO_LEFT 9
#define MAX_DISTANCE 200

#define TRIGGER_MID 5
#define ECHO_MID 4

#define TRIGGER_RIGHT 3
#define ECHO_RIGHT 2

const long duration;
const int distance;

//Motors  // prefix m
const int mRightEnable = 6;
const int mRightInput1 = 7;
const int mRightInput2 = 8;

const int mLeftEnable = 11;
const int mLeftInput1 = 12;
const int mLeftInput2 = 13;

//incoming serial byte
int inByte = 0;  

NewPing sonarLeft(TRIGGER_LEFT, ECHO_LEFT, MAX_DISTANCE);
NewPing sonarMid(TRIGGER_MID, ECHO_MID, MAX_DISTANCE);
NewPing sonarRight(TRIGGER_RIGHT, ECHO_RIGHT, MAX_DISTANCE);
  
void setup() {

  Serial.begin(9600);
  pinMode(mLeftEnable, OUTPUT);
  pinMode(mLeftInput1, OUTPUT);
  pinMode(mLeftInput2, OUTPUT);

  pinMode(mRightEnable, OUTPUT);
  pinMode(mRightInput1, OUTPUT);
  pinMode(mRightInput2, OUTPUT);
  
}

void readUltrasonicSensor(){
  // Clears the trigPin
  //Serial.print("Sonar left: ");

  //float measurements= [];
  
  /*
  Serial.print(sonarLeft.ping_cm());
  Serial.print("\n");

  //Serial.print("Sonar mid: ");
  Serial.print(sonarMid.ping_cm());
  Serial.print("\n");
  
  //Serial.print("Sonar right: ");
  Serial.print(sonarRight.ping_cm());
  Serial.print("\n");
*/

  /*
  double sonarData[3];

  sonarData[0] = sonarLeft.ping_cm();
  sonarData[1] = sonarMid.ping_cm();
  sonarData[2] = sonarRight.ping_cm();
  */
   
  Serial.print(sonarLeft.ping_cm());
  Serial.print(":");
  Serial.print(sonarMid.ping_cm());
  Serial.print(":");
  Serial.println(sonarRight.ping_cm());
  
  delay(500);
}

void loop() {
  
 //forwards(199);
 readUltrasonicSensor();
 
}


void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}
//call this function to test motors
void demoMotors(){

  //HIGH or Low sets the direction
 
  for(int i=130; i< 255; i++){
    
    if(i % 2 == 0){
       delay(6000);
       Serial.print("left  \n");
       analogWrite(mLeftEnable, i);
       analogWrite(mRightEnable, 0);
    } else {
       delay(6000);
       Serial.print("right \n");
       analogWrite(mLeftEnable, 0);
       analogWrite(mRightEnable, i);      
    }
    
  }
  
}

//applies same voltage with PWM to each motor; speed parameter goes from 0 to 255
void forwards(int speed){

  digitalWrite(mLeftInput1, LOW);
  digitalWrite(mLeftInput2, HIGH);

  digitalWrite(mRightInput1, LOW);
  digitalWrite(mRightInput2, HIGH);

  analogWrite(mLeftEnable, speed);
  analogWrite(mRightEnable, speed);

}

void reverse(int speed){

  digitalWrite(mLeftInput1, HIGH);
  digitalWrite(mLeftInput2, LOW);

  digitalWrite(mRightInput1, HIGH);
  digitalWrite(mRightInput2, LOW);

  analogWrite(mLeftEnable, speed);
  analogWrite(mRightEnable, speed);
}

void turnLeft(int degrees){
  
}

void turnRight(int degress){

  
}

#include "Vehicle.h"
#include "Action.h"
#include <NewPing.h>
#include <Servo.h>
#include "Wire.h"

#define MOTOR_RIGHT_ENABLE 6
#define MOTOR_RIGHT_INPUT1 7
#define MOTOR_RIGHT_INPUT2 8

#define MOTOR_LEFT_ENABLE 11
#define MOTOR_LEFT_INPUT1 12
#define MOTOR_LEFT_INPUT2 13

#define MAX_DISTANCE 200
#define TRIGGER_MID 5
#define ECHO_MID 4

#define SERVO_PIN 9

Vehicle::Vehicle() :
  sMid(TRIGGER_MID, ECHO_MID, MAX_DISTANCE), servo()
{
}

int Vehicle::getMidDistance() {
  return (sMid.convert_cm(sMid.ping_median(3)));
}

//todo: set turning speed
//todo: set turning limit, measure real turning angle
void Vehicle::moveServo(int angle, int turningSpeed) {
  //to scale
  //val = map(val, 0, 1023, 0, 179);  // scale it to use it with
  servo.attach(SERVO_PIN);
  servo.write(angle);
  delay(turningSpeed);
  servo.detach();

  /*
    int pos1 =0;
    void moveTo(int position, int speed){
    mapSpeed = map(speed, 0, 30, 30,0);
    if(position > pos){
      for(pos=pos1; pos<= position; pos++){
        myservo.write(pos);
        pos1=pos;
        delay(mapSpeed);
      }
    }
    }
  */
}

void Vehicle::left(int turningTime, int turnSpeed, bool clockwise) {

  if (clockwise) {
    digitalWrite(MOTOR_LEFT_INPUT1, LOW);
    digitalWrite(MOTOR_LEFT_INPUT2, HIGH);
    analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();
  } else {
    digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
    digitalWrite(MOTOR_LEFT_INPUT2, LOW);
    analogWrite(MOTOR_LEFT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();

  }
}

void Vehicle::right(int turningTime, int turnSpeed, bool clockwise) {

  if (clockwise) {

    digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
    digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);
    analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();

  } else {
    digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
    digitalWrite(MOTOR_RIGHT_INPUT2, LOW);
    analogWrite(MOTOR_RIGHT_ENABLE, turnSpeed);
    delay(turningTime);
    fullStop();
  }
}

void Vehicle::fullStop() {

  digitalWrite(MOTOR_LEFT_INPUT1, LOW);
  digitalWrite(MOTOR_LEFT_INPUT2, LOW);

  digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
  digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

  analogWrite(MOTOR_LEFT_ENABLE, 0);
  analogWrite(MOTOR_RIGHT_ENABLE, 0 );
}

//example of action
//PWMLeft:121  | PWMRight: 160 | clockwiseLeft: 1  | clockwiseRight: 0 | timeLeft: 939 | timeRight: 698  | servoAngle: 141
void Vehicle::performActions(struct Action actions[], int duration) {

  for (int i = 0; i < duration; i++) {
    left(actions[i].timeLeft, actions[i].PWMLeft, actions[i].clockwiseLeft);
    right(actions[i].timeRight, actions[i].PWMRight, actions[i].clockwiseRight);
    moveServo(actions[i].servoAngle, 1000);
    Serial.print("servo");
    Serial.println(actions[i].servoAngle);
  }
}


char* Vehicle::convert_int16_to_str(int16_t i, char tmp_str) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void Vehicle::gyro() {
  int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
  int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
  int16_t temperature; // variables for temperature data
  char tmp_str[7]; // temporary variable used in convert function

  Wire.beginTransmission(0x68);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(0x68, 7 * 2, true); // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read() << 8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  // print out data
  Serial.print("aX = "); Serial.print((accelerometer_x));
  Serial.print(" | aY = "); Serial.print((accelerometer_y));
  Serial.print(" | aZ = "); Serial.print((accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print(" | tmp = "); Serial.print(temperature / 340.00 + 36.53);
  Serial.print(" | gX = "); Serial.print((gyro_x));
  Serial.print(" | gY = "); Serial.print((gyro_y));
  Serial.print(" | gZ = "); Serial.print((gyro_z));
  Serial.println();

  // delay
  delay(1000);


}

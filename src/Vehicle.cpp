#include <NewPing.h>
#include <L298N.h>

class Vehicle {

  private:

    //Motors prefix m
    const int MOTOR_RIGHT_ENABLE;
    const int MOTOR_RIGHT_INPUT1;
    const int MOTOR_RIGHT_INPUT2;

    const int MOTOR_LEFT_ENABLE;
    const int MOTOR_LEFT_INPUT1;
    const int MOTOR_LEFT_INPUT2;

    const int TRIGGER_LEFT ;
    const int ECHO_LEFT ;
    const int MAX_DISTANCE;

    const int TRIGGER_MID;
    const int ECHO_MID;

    const int TRIGGER_RIGHT;
    const int ECHO_RIGHT;

    int vehicleSpeed;

    NewPing sLeft;
    NewPing sMid;
    NewPing sRight;

  public:

    Vehicle(): sLeft(TRIGGER_LEFT, ECHO_LEFT, MAX_DISTANCE), sMid(TRIGGER_MID, ECHO_MID, MAX_DISTANCE), sRight(TRIGGER_RIGHT, ECHO_RIGHT, MAX_DISTANCE) {

      Serial.begin(9600);

      pinMode(MOTOR_LEFT_ENABLE, OUTPUT);
      pinMode(MOTOR_LEFT_INPUT1, OUTPUT);
      pinMode(MOTOR_LEFT_INPUT2, OUTPUT);

      pinMode(MOTOR_RIGHT_ENABLE, OUTPUT);
      pinMode(MOTOR_RIGHT_INPUT1, OUTPUT);
      pinMode(MOTOR_RIGHT_INPUT2, OUTPUT);

    }


    void Vehicle::readSensors() {
      // Clears the trigPin
      //Serial.print("Sonar left: ");
      //float measurements= [];

      Serial.print(sLeft.ping_cm());
      Serial.print("\n");

      //Serial.print("Sonar mid: ");
      Serial.print(sMid.ping_cm());
      Serial.print("\n");

      //Serial.print("Sonar right: ");
      Serial.print(sRight.ping_cm());
      Serial.print("\n");

      double sonarData[3];
      
      /*
            sonarData[0] = sLeft.ping_cm();
            sonarData[1] = sMid.ping_cm();
            sonarData[2] = sRight.ping_cm();

            //turned off to test mapping
            Serial.print(sLeft.ping_cm());
              Serial.print(":");
              Serial.print(sMid.ping_cm());
              Serial.print(":");
              Serial.println(sRight.ping_cm());*/

      delay(500);
    }

    void Vehicle::forwards() {

      digitalWrite(MOTOR_LEFT_INPUT1, LOW);
      digitalWrite(MOTOR_LEFT_INPUT2, HIGH);

      digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
      digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);

      analogWrite(MOTOR_LEFT_ENABLE, vehicleSpeed);
      analogWrite(MOTOR_RIGHT_ENABLE, vehicleSpeed);

    }

    void Vehicle::reverse() {

      digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
      digitalWrite(MOTOR_LEFT_INPUT2, LOW);

      digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
      digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

      analogWrite(MOTOR_LEFT_ENABLE, vehicleSpeed);
      analogWrite(MOTOR_RIGHT_ENABLE, vehicleSpeed);
    }

    //TODO: make this so it turn only 10 degrees at constant speed or a given angle
    void Vehicle::turnLeft() {
      digitalWrite(MOTOR_LEFT_INPUT1, HIGH);
      digitalWrite(MOTOR_LEFT_INPUT2, LOW);

      digitalWrite(MOTOR_RIGHT_INPUT1, LOW);
      digitalWrite(MOTOR_RIGHT_INPUT2, HIGH);

      analogWrite(MOTOR_LEFT_ENABLE, vehicleSpeed);
      analogWrite(MOTOR_RIGHT_ENABLE, vehicleSpeed);
    }

    //TODO: turn 10 degrees
    void Vehicle::turnRight() {
      digitalWrite(MOTOR_LEFT_INPUT1, LOW);
      digitalWrite(MOTOR_LEFT_INPUT2, HIGH);

      digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
      digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

      analogWrite(MOTOR_LEFT_ENABLE, vehicleSpeed);
      analogWrite(MOTOR_RIGHT_ENABLE, vehicleSpeed);

    }
    //try different turning speeds
    void Vehicle::testTurningRight() {

      for (int i = 0; i < 10; i++) {
      digitalWrite(MOTOR_LEFT_INPUT1, LOW);
      digitalWrite(MOTOR_LEFT_INPUT2, HIGH);

      digitalWrite(MOTOR_RIGHT_INPUT1, HIGH);
      digitalWrite(MOTOR_RIGHT_INPUT2, LOW);

      analogWrite(MOTOR_LEFT_ENABLE, vehicleSpeed);
      analogWrite(MOTOR_RIGHT_ENABLE, vehicleSpeed);
      }
    }

    void Vehicle::demoMotors() {

      //HIGH or Low sets the direction

      for (int i = 130; i < 2550; i++) {

        if (i % 2 == 0) {
          delay(6000);
          Serial.print("left  \n");
          analogWrite(MOTOR_LEFT_ENABLE, i);
          analogWrite(MOTOR_RIGHT_ENABLE, 0);
        } else {
          delay(6000);
          Serial.print("right \n");
          analogWrite(MOTOR_LEFT_ENABLE, 0);
          analogWrite(MOTOR_RIGHT_ENABLE, i);
        }
      }
    }

    void Vehicle::setSpeed(int newSpeed) {
      vehicleSpeed = newSpeed;
    }

    /*
       An action [0, 0, 0, 0] -> forwards, backwards, left, right
       the action is executed if the value is 1, then it returns a reward
    */
    int Vehicle::perform(int *action) {
      int reward;

      if (action[0]==1) {
        forwards();
      }
      if (action[1]==1) {
        reverse();
      }
      if (action[2]==1) {
        turnLeft();
      }
      if (action[3]==1) {
        turnRight();
      }

      return reward;
      
    }

    int Vehicle::getObservation(){
      
      int obs[3] = {sLeft.ping_cm(), sMid.ping_cm(), sRight.ping_cm()};

      return obs;
    }


};

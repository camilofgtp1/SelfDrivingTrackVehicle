/*
  https://www.arduino.cc/en/Reference/RobotMotorsWrite
  Robot.motorsWrite(speedLeft, speedRight) to replace cumbersome functions to controlling the movement

  TODO: Arduino can connect to laptop using wirless network to send sensor data and recieve manual control instructions
  TODO: Arduino can connecto to RC Controller
  TODO: Arduino is powered by battery
  TODO: The turning can be made by giving an angle in degrees
  TODO: The processing sketch maps the sensor data at scale and can be zoomed in and out
  TODO: QLearning algorithm gives actions that move the vehicle for the amount of time specified
  TODO: Mobile app shows room, vehicle finds the best way to a selected spot
  TODO: Easy Mode: QLearning outputs one of 4 actions corresponding to the direction it should drive to
        Hard Mode: QLearning ouputs outputs speed and direction of the spinning of the motors
*/
#include "Vehicle.cpp"

Vehicle trackVehicle;

void setup() {
  
  Vehicle trackVehicle();
}

void loop() {

  trackVehicle.readSensors();

}

/*Q learning:
  The Agent has two motor which can be turn on both directions
  All the possible actions for a controlled vehicle at constant speed for:
  forward();
  reverser();
  turnLeft(); -10 degrees at the time, but  ideally with any given negative angle
  turnRight(); +10 degrees or any positive angle

  The agent has different learnable actions

  we could limit the possible speeds  between 120 and 200

  first stage:
  it can move backwards in a straigh line away from an obstacle

  second stage:
  if can turn left and right

  third:
  it can move freely with no sense of direction but avoids obstacles and reverses if it finds caught on a close end

  fourth:
  it maps the entire room avoiding collisions, looks actively for blind spots

  Orientation:
  it could be done by setting the turning


*/

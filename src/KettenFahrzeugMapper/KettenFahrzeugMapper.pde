//TODO: Connect to serial port arduino
//TODO: Use wireless connection

import processing.serial.*;

String[] sensorData;

ArrayList sensorLeft = new ArrayList<PVector>();
ArrayList sensorMid = new ArrayList<PVector>();
ArrayList sensorRight =new ArrayList<PVector>();
Vehicle vehicle;

void setup () {
  vehicle = new Vehicle(this);
}

void draw () {

  vehicle.serialEvent();

}

void data() {

  //generate data
  sensorLeft.add(new PVector(10, this.vehicle.position.y));
  sensorLeft.add(new PVector(20, this.vehicle.position.y));
  sensorLeft.add(new PVector(30, this.vehicle.position.y));
  sensorLeft.add(new PVector(40, this.vehicle.position.y));
  sensorLeft.add(new PVector(50, this.vehicle.position.y));
  sensorLeft.add(new PVector(60, this.vehicle.position.y));
  sensorLeft.add(new PVector(70, this.vehicle.position.y));
  sensorLeft.add(new PVector(80, this.vehicle.position.y));
  sensorLeft.add(new PVector(90, this.vehicle.position.y));
  sensorLeft.add(new PVector(100, this.vehicle.position.y));

  sensorMid.add(new PVector(this.vehicle.position.x, 10));
  sensorMid.add(new PVector(this.vehicle.position.x, 20));
  sensorMid.add(new PVector(this.vehicle.position.x, 30));
  sensorMid.add(new PVector(this.vehicle.position.x, 40));
  sensorMid.add(new PVector(this.vehicle.position.x, 50));
  sensorMid.add(new PVector(this.vehicle.position.x, 60));
  sensorMid.add(new PVector(this.vehicle.position.x, 70));
  sensorMid.add(new PVector(this.vehicle.position.x, 80));
  sensorMid.add(new PVector(this.vehicle.position.x, 90));
  sensorMid.add(new PVector(this.vehicle.position.x, 100));

  sensorRight.add(new PVector(this.vehicle.position.x+10, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+20, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+30, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+40, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+50, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+60, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+70, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+80, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+90, this.vehicle.position.y));
  sensorRight.add(new PVector(this.vehicle.position.x+100, this.vehicle.position.y));
}

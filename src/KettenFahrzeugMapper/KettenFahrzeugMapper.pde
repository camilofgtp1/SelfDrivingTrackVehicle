//TODO: Organize in a OOP Module
//TODO: Connect to serial port arduino
//TODO: Use wireless connection

import processing.serial.*;

Serial myPort;
float inByte = 0;

String[] sensorData;

ArrayList<PVector> sensorLeft; 
ArrayList<PVector> sensorMid;   
ArrayList<PVector> sensorRight; 

PVector vehicle;
int xPos;
int yPos;

int vehicleWidth;
int vehicleHeight;

float zoom;
  
float scale;
float xPan;
float yPan;

boolean zoomIn;
boolean zoomOut;

boolean panUp;
boolean panRight;
boolean panDown;
boolean panLeft;

float panSpeed;
float zoomSpeed;

void setup () {

  scale = 1;
  xPan = width/2;
  yPan = height/2;

  size(800, 800);
  zoom=1;

  zoomIn = false;
  zoomOut = false;
  panUp = false;
  panRight =false;
  panDown =false;
  panLeft =false;

  panSpeed=3;
  zoomSpeed= 1.2;

  //myPort = new Serial(this, Serial.list()[1], 9600);
  //myPort.bufferUntil('\n');

  vehicleWidth = 40;
  vehicleHeight = 60;
  vehicle = new PVector(0, 0);

  sensorLeft = new ArrayList<PVector>();
  sensorMid = new ArrayList<PVector>();
  sensorRight =new ArrayList<PVector>();

  data();

  //print available serial ports
  printArray(Serial.list());
  drawBackground();
}

void draw () {

  //handleZoom();

  drawVehicle();
  drawLeftSensor();
  drawMidSensor();
  drawRightSensor();
  //mouseWheel();
} 

//maybe there is  problem with the magic mouse that it becomes 0 when not sliding over the surface
void mouseWheel(MouseEvent event) {
  float e = event.getCount()*0.9;
  //zoom=e;
  println("e: " +e);
  println("zoom: "+zoom);
}

void serialEvent (Serial myPort) {

  //get the ASCII string; Read bytes up to linebreak
  String inString = myPort.readStringUntil('\n');
  print("serialevent: ");
  print(inString);

  sensorData = inString.split(":");

  /*
   sensorLeft.add(sensorData[0]);
   sensorMid.add(sensorData[1]);
   sensorRight.add(sensorData[2]);
   */
}

void data() {

  //generate random data
  sensorLeft.add(new PVector(10, vehicle.y));
  sensorLeft.add(new PVector(20, vehicle.y));
  sensorLeft.add(new PVector(30, vehicle.y));
  sensorLeft.add(new PVector(40, vehicle.y));
  sensorLeft.add(new PVector(50, vehicle.y));
  sensorLeft.add(new PVector(60, vehicle.y));
  sensorLeft.add(new PVector(70, vehicle.y));
  sensorLeft.add(new PVector(80, vehicle.y));
  sensorLeft.add(new PVector(90, vehicle.y));
  sensorLeft.add(new PVector(100, vehicle.y));

  sensorMid.add(new PVector(vehicle.x, 10));
  sensorMid.add(new PVector(vehicle.x, 20));
  sensorMid.add(new PVector(vehicle.x, 30));
  sensorMid.add(new PVector(vehicle.x, 40));
  sensorMid.add(new PVector(vehicle.x, 50));
  sensorMid.add(new PVector(vehicle.x, 60));
  sensorMid.add(new PVector(vehicle.x, 70));
  sensorMid.add(new PVector(vehicle.x, 80));
  sensorMid.add(new PVector(vehicle.x, 90));
  sensorMid.add(new PVector(vehicle.x, 100));

  sensorRight.add(new PVector(vehicle.x+10, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+20, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+30, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+40, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+50, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+60, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+70, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+80, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+90, vehicle.y));
  sensorRight.add(new PVector(vehicle.x+100, vehicle.y));
}

void drawVehicle() {

  int cornerRadius = 7;
  //rotate(radians(90));
  stroke(255);

  pushMatrix();
  translate(width/2, height/2);
  fill(26, 63, 92);
  rectMode(CENTER);
  rect(vehicle.x, vehicle.y, vehicleWidth, vehicleHeight, cornerRadius);
  popMatrix();
}

//x is the negative sensor measurement minus vehicle width, y is the vehicle position
void drawLeftSensor() {
  fill(26, 63, 92);
  for (int i =0; i< sensorLeft.size(); i++) {
    float x = sensorLeft.get(i).x;
    float y = sensorLeft.get(i).y;
    pushMatrix();
    translate(width/2, height/2);
    circle(-x*scale, vehicle.y, 10);
    popMatrix();
  }
}

//x is the vehicle position, y is the negative sensor measurement
void drawMidSensor() {
  for (int i =0; i< sensorMid.size(); i++) {
    float x = sensorMid.get(i).x;
    float y = sensorMid.get(i).y;
    pushMatrix();
    fill(189, 241, 148);
    translate(width/2, height/2);
    circle(x, -y*scale, 10);
    popMatrix();
  }
}

//
void drawRightSensor() {
  for (int i =0; i< sensorRight.size(); i++) {
    float x = sensorRight.get(i).x;
    float y = sensorRight.get(i).y;
    pushMatrix();
    fill(252, 48, 3);
    translate(width/2, height/2);
    circle(x*scale, y, 10);
    popMatrix();
  }
}

void drawBackground() {
  background(0);

  stroke(115, 243, 64);
  pushMatrix();
  translate(width/2, height/2);

  float firstRadius = vehicleWidth/2;

  circle(0, 0, firstRadius);

  for (int i=0; i<80; i++) {
    if (i%10==0) {
      noFill();
      circle(0, 0, (i*10)-vehicleWidth);
      fill(115, 243, 64);

      //vertical distance
      text(str(i), 2, (i*10)-2);
      text(str(i), 2, -(i*10)-2);

      //horizontal distance
      text(str(i), (i*5)+2, 15);
      text(str(i), -(i*5)+2, 15);
    }
  }

  rotate(0);
  strokeWeight(2);
  line(0, -height, 0, height);
  line(-width, 0, width, 0 );

  rotate(radians(-90));
  for (int j=0; j<360; j++) {
    if (j%10==0) {
      rotate(radians(1));

      //text(str(i), 250, 200 );
      strokeWeight(1);
      //line(0, 0, 100, 309);
      text(str(j), 0, 360);
    } else {
      rotate(radians(1));
    }
  }
  popMatrix();
}

void handleZoom() {
  translate(mouseX, mouseY);
  scale(scale);
  translate(-xPan, -yPan);

  if (zoomOut) {
    scale /=zoomSpeed;
  }
  if (zoomIn) {
    scale *=zoomSpeed;
  }
  if (panUp) {
    yPan+=panSpeed;
  }
  if (panDown) {
    yPan-=panSpeed;
  }
  if (panRight) {
    xPan-=panSpeed;
  }
  if (panLeft) {
    xPan += panSpeed;
  }
}

void keyPressed() {

  if (keyCode == UP) {
    zoomIn=true;
    zoomOut = false;
  }
  if (keyCode == DOWN) {
    zoomOut = true;
    zoomIn = false;
  }
  if (key == 'w') { 
    panUp = true;
    panDown = false;
  }
  if (key== 's') {
    panDown = true;
    panUp = false;
  }
  if (key == 'a') {
    panLeft = true;
    panRight =false;
  }
  if (key == 'd') {
    panRight = true;
    panLeft = false;
  }
}

void keyReleased() {
  if (keyCode == UP) {
    zoomIn = false;
  }
  if (keyCode== DOWN) {
    zoomOut =false;
  }
  if (key == 'w') { 
    panUp = false;
  }
  if (key== 's') {
    panDown = false;
  }
  if (key == 'a') {
    panLeft = false;
  }
  if (key == 'd') {
    panRight = false;
  }
}

//TODO: scale the dots and the radar to zoom in proportionally to a input slider, or button, evt mouse wheel

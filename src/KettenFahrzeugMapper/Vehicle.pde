import processing.serial.*;

class Vehicle {

  PVector position;
  Serial port;
  String[] sensorData;

  ArrayList<PVector> sensorLeft; 
  ArrayList<PVector> sensorMid; 
  ArrayList<PVector> sensorRight; 

  int vehicleWidth;
  int vehicleHeight;
  PApplet ref;

  Vehicle(PApplet pa) {

    ref = pa;
    vehicleWidth = 40;
    vehicleHeight = 60;
    position = new PVector(0, 0);

    sensorLeft = new ArrayList<PVector>();
    sensorMid = new ArrayList<PVector>();
    sensorRight =new ArrayList<PVector>();

    printArray(Serial.list());

    //open ports
    port = new Serial(ref, Serial.list()[3], 9600);
    port.bufferUntil('\n');
    port.clear();

}

  void serialEvent () {

    String inString = port.readStringUntil('\n');
   
    if(inString != null){
      sensorData = inString.split(":");  
    }
    //sensorLeft.add(new PVector(float(sensorData[0])));
    //sensorMid.add(sensorData[1]);
    //sensorRight.add(sensorData[2]);
  }

  void drawVehicle() {

    int cornerRadius = 7;
    //rotate(radians(90));
    stroke(255);

    pushMatrix();
    translate(width/2, height/2);

    rectMode(CENTER);


    fill(123);

    //track left
    rect(position.x-(vehicleWidth*0.42), position.y, vehicleWidth/3, vehicleHeight*0.8, 5);

    //track right
    rect(position.x + (vehicleWidth*0.42), position.y, vehicleWidth/3, vehicleHeight*0.8, 5);

    //carosserie
    fill(26, 63, 92);
    rect(position.x, position.y, vehicleWidth, vehicleHeight, cornerRadius);
    popMatrix();
  }

  void drawLeftSensor() {
    fill(26, 63, 92);
    for (int i =0; i< sensorLeft.size(); i++) {
      int scale=5;
      float x = (sensorLeft.get(i).x)*(-scale) ;
      float y = sensorLeft.get(i).y;
      int markerSize = 10;
      pushMatrix();
      translate(width/2, height/2);
      circle(x, y, markerSize);
      popMatrix();
    }
  }

  //x is the vehicle position, y is the negative sensor measurement
  void drawMidSensor() {
    for (int i =0; i< sensorMid.size(); i++) {
      int scale = 5;
      float x = sensorMid.get(i).x;
      float y = sensorMid.get(i).y*(scale);
      int markerSize = 10;
      pushMatrix();
      fill(189, 241, 148);
      translate(width/2, height/2);
      circle(x, -y, markerSize);
      popMatrix();
    }
  }

  //
  void drawRightSensor() {
    fill(252, 48, 3);
    for (int i =0; i< sensorRight.size(); i++) {
      int scale = 5;
      int markerSize = 10;
      float x = sensorRight.get(i).x * scale ;
      float y = sensorRight.get(i).y;
      pushMatrix();
      translate(width/2, height/2);
      circle(x, y, markerSize);
      popMatrix();
    }
  }

  void data() {

    //generate random data
    sensorLeft.add(new PVector(0, position.y));
    sensorLeft.add(new PVector(10, position.y));
    sensorLeft.add(new PVector(20, position.y));
    sensorLeft.add(new PVector(30, position.y));
    sensorLeft.add(new PVector(40, position.y));
    sensorLeft.add(new PVector(50, position.y));
    sensorLeft.add(new PVector(60, position.y));
    sensorLeft.add(new PVector(70, position.y));
    sensorLeft.add(new PVector(80, position.y));
    sensorLeft.add(new PVector(90, position.y));
    sensorLeft.add(new PVector(100, position.y));

    sensorMid.add(new PVector(position.x, 10));
    sensorMid.add(new PVector(position.x, 20));
    sensorMid.add(new PVector(position.x, 30));
    sensorMid.add(new PVector(position.x, 40));
    sensorMid.add(new PVector(position.x, 50));
    sensorMid.add(new PVector(position.x, 60));
    sensorMid.add(new PVector(position.x, 70));
    sensorMid.add(new PVector(position.x, 80));
    sensorMid.add(new PVector(position.x, 90));
    sensorMid.add(new PVector(position.x, 100));

    sensorRight.add(new PVector(position.x+10, position.y));
    sensorRight.add(new PVector(position.x+20, position.y));
    sensorRight.add(new PVector(position.x+30, position.y));
    sensorRight.add(new PVector(position.x+40, position.y));
    sensorRight.add(new PVector(position.x+50, position.y));
    sensorRight.add(new PVector(position.x+60, position.y));
    sensorRight.add(new PVector(position.x+70, position.y));
    sensorRight.add(new PVector(position.x+80, position.y));
    sensorRight.add(new PVector(position.x+90, position.y));
    sensorRight.add(new PVector(position.x+100, position.y));
  }
}

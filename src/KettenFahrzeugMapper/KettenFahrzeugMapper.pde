 //<>//
Vehicle trackVehicle = new Vehicle();
Radar radar = new Radar();

void setup () {

  //size(width, height);
  size(800, 800);
  
  //myPort = new Serial(this, Serial.list()[1], 9600);
  //myPort.bufferUntil('\n');

  //print available serial ports
  radar.drawBackground();
  //trackVehicle.drawLeftSensor();
  //trackVehicle.drawRightSensor();
  //trackVehicle.drawMidSensor();
  
  trackVehicle.drawVehicle();
}

void draw () {
  //handleZoom();
  //mouseWheel();
} 

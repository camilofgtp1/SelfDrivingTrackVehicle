class Radar {

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

  Radar() {
    zoom=1;

    zoomIn = false;
    zoomOut = false;
    panUp = false;
    panRight =false;
    panDown =false;
    panLeft =false;

    panSpeed=3;
    zoomSpeed= 1.2;
  }


  /*
Draws the green circles on the background of the radar
   */
  void drawBackground() {
    background(0);
    stroke(115, 243, 64);
    pushMatrix();
    translate(width/2, height/2);
    int vehicleWidth = 40;
    int radius= 10;
    int scale = 10;

    for (int i=10; i<width; i+=radius) {
      if (i %10 ==0) {
        noFill();
        circle(0, 0, (i*scale));
        fill(115, 243, 64);

        //vertical upper distance markers
        if (i != 70) {
          text(str(i), 3, -(i*5)+4);
        }
        //vertical lower distance markers
        //text(str(i), 1, (i*5));

        //right distance markers
        text(str(i), (i*5)-15, 15);

        //left distance markers
        //text(str(i), -(i*5)+2, 15);
      }
    }

    strokeWeight(2);
    /* Center lines */
    line(0, -height, 0, height);
    line(-width, 0, width, 0 );

    /* set the starting point of polar coordinates to the front */
    rotate(radians(-180));

    for (int j=0; j<360; j++) {
      if (j%10==0) {
        rotate(radians(1));

        strokeWeight(1);

        if (j != 90 && j != 270 && j != 180 ) {
          text(str(j), 0, 360);
        }
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

  //maybe there is  problem with the magic mouse that it becomes 0 when not sliding over the surface
  void mouseWheel(MouseEvent event) {
    float e = event.getCount()*0.9;
    //zoom=e;
    println("e: " +e);
    //println("zoom: "+zoom);
  }
}

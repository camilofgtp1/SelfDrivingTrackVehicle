
  import processing.serial.*;

   // Globals


  Serial myPort;        // The serial port
  int xPos = 1;         // horizontal position of the graph
  float inByte = 0;
  
  String[] sensorData;
  
  //String[] sensorLeft;
  String[] sensorMid;
  String[] sensorRight;
  ArrayList<String> sensorLeft; 
  
  void setup () {
    
    sensorLeft = new ArrayList<String>();
    // set the window size:
    size(400, 300);

    // List all the available serial ports
    printArray(Serial.list());

    // Open whatever port is the one you're using.
    myPort = new Serial(this, Serial.list()[1], 9600);

    // don't generate a serialEvent() unless you get a newline character:
    // a byte array that ends at the first given character, this gets sent from Arduino file using Serial.write(myDataAsString + "\n")
    myPort.bufferUntil('\n');

    // color:
    background(0);
  }

  void draw () {
    // draw the line:
    stroke(127, 34, 255);
    line(xPos, height, xPos, height - inByte);

    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPos++;
    }
  }

  // gets called when buffer ends
  void serialEvent (Serial myPort) {

    // get the ASCII string:
    // it is possible to pass different counting number systems
    String inString = myPort.readStringUntil('\n');
    print("serialevent: ");
    print(inString);

    // 3  Ultrasound Sensor data is send together as string separated by a colon
    sensorData = inString.split(":");

    print("left: ");

    //draw mapping
    sensorLeft.add(sensorData[0]);
    //sensorLeft=sensorData[0];
    print(sensorData[0]);
    //print(sensorLeft);
    print("\n");
    
    print("Left: " + "\n" + sensorData[0] + \n");
    print("Mid: " + "\n" + sensorData[1] + \n");
    print("Right: " + "\n" + sensorData[2] + \n");

    for (int i=0; i< sensorLeft.size(); i++){
      print(sensorLeft.get(i));
   
    }

  }

/**************************************************************************
   Textile Game Controller workshop
   Working with Arduino Micro board and conductive materials
   Digital switch example
   Based on based on this Lab on the ITP Physical Computing site:
   https://itp.nyu.edu/physcomp/labs/labs-serial-communication/two-way-duplex-serial-communication-using-an-arduino/
   Social Body Lab, 2018 Oct.
**************************************************************************/

#include <Servo.h>

int sensor1val;
int sensor2val;
int sensor3val;

int servoPin1 = 3;           //Pin that the servo is attached to.
int servoPin2 = 4;           //Pin that the servo is attached to.
int servoPin3 = 5;           //Pin that the servo is attached to.
int servoPin4 = 6;           //Pin that the servo is attached to.

int moveRate = 10;        //the time between updates in milliseconds
int minAngle = 0;     //sets the low point of the movement range
int maxAngle = 180;   //sets the high point of the movement range
int moveIncrement1 = 1;    // how much to move the motor each cycle
int moveIncrement2 = 2;    // how much to move the motor each cycle
int moveIncrement3 = 3;    // how much to move the motor each cycle
int moveIncrement4 = 4;    // how much to move the motor each cycle

int servoAngle1;
int servoAngle2;


long lastTimeYouMoved1;
long lastTimeYouMoved2;
long lastTimeYouMoved3;
long lastTimeYouMoved4;

Servo servo1;  // create the Servo object
Servo servo2;  // create the Servo object
Servo servo3;  // create the Servo object
Servo servo4;  // create the Servo object

void setup() {
  //start serial connection
  Serial.begin(9600);
  servo1.attach(servoPin1);  //attach the servo to the corresponding control pin
  servo2.attach(servoPin2);  //attach the servo to the corresponding control pin
  servo3.attach(servoPin3);  //attach the servo to the corresponding control pin
  servo4.attach(servoPin4);
  servoAngle1 = minAngle;
}

void loop() {
  // read the sensor value
  sensor1val = analogRead(0);
  // print out the sensor value
  Serial.print(sensor1val);
  // print a comma to separate the values
  Serial.println();




  // if (millis() - lastTimeYouMoved1 >= moveRate) //this very simple statement is the timer,
  //{ //it subtracts the value of the moment in time the last blink happened, and sees if that number is larger than your set blinking value
  servo1.write(servoAngle1);

  if (sensor1val > 1000) {
    servoAngle1 += moveIncrement1;

    if (servoAngle1 <= minAngle || servoAngle1 >= maxAngle)
    {
      moveIncrement1 = -moveIncrement1;
    }

    servoAngle2 += moveIncrement2;

    if (servoAngle2 <= minAngle || servoAngle2 >= maxAngle)
    {
      moveIncrement2 = -moveIncrement2;
    }

    //lastTimeYouMoved1 = millis();            //save the value in time that this switch occured, so we can use it again.

  } else {
    servo1.write(servoAngle1);
    servo2.write(servoAngle2);
  }
  /*  if (millis() - lastTimeYouMoved2 >= moveRate) //this very simple statement is the timer,
    { //it subtracts the value of the moment in time the last blink happened, and sees if that number is larger than your set blinking value
      servo2.write(servoAngle2);

      servoAngle2 += moveIncrement;

      if (servoAngle2 <= minAngle || servoAngle2 >= maxAngle)
      {
        moveIncrement = -moveIncrement;
      }

      lastTimeYouMoved2 = millis();            //save the value in time that this switch occured, so we can use it again.

    }
    if (millis() - lastTimeYouMoved3 >= moveRate) //this very simple statement is the timer,
    { //it subtracts the value of the moment in time the last blink happened, and sees if that number is larger than your set blinking value
      servo3.write(servoAngle3);

      servoAngle3 += moveIncrement;

      if (servoAngle3 <= minAngle || servoAngle3 >= maxAngle)
      {
        moveIncrement = -moveIncrement;
      }

      lastTimeYouMoved3 = millis();            //save the value in time that this switch occured, so we can use it again.

    }
    if (millis() - lastTimeYouMoved4 >= moveRate) //this very simple statement is the timer,
    { //it subtracts the value of the moment in time the last blink happened, and sees if that number is larger than your set blinking value
      servo4.write(servoAngle4);

      servoAngle4 += moveIncrement;

      if (servoAngle4 <= minAngle || servoAngle4 >= maxAngle)
      {
        moveIncrement = -moveIncrement;
      }

      lastTimeYouMoved4 = millis();            //save the value in time that this switch occured, so we can use it again.

    }*/

  //attach the servo to the corresponding control pin


  /* read the sensor value
    /sensor2val = analogRead(1);
    // print out the sensor value
    Serial.print(sensor2val);
    // print a comma to separate the values
    Serial.print(",");

    // read the sensor value
    sensor3val = analogRead(2);
    // print out the sensor value and add a line break
    Serial.println(sensor3val);
  */
  delay(1); // the delay is necessary for the serial communication


}


#include <Servo.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define LedPin1           1
#define LedPin2           0
#define LedPin3           14
#define LedPin4           15
#define LedPin5           16
#define LedPin6           17
#define LedPin7           18
#define LedPin8           19
#define LedPin9           20
#define LedPin10          21

// Which pin on the Arduino is connected to the Motors?
#define MotorPin1           11
#define MotorPin2           10
#define MotorPin3           9
#define MotorPin4           8
#define MotorPin5           7
#define MotorPin6           6
#define MotorPin7           5
#define MotorPin8           4
#define MotorPin9           3
#define MotorPin10          2

// Which pin on the Arduino is connected to the Textile?
// Quad [1,2,3,4] = which quadrant the pin is in;
// S = small sensor, M = medium sensor, : = large sensor;
#define Quad1S          0
#define Quad1M          1
#define Quad1L          2

#define Quad2S          3
#define Quad2M          4
#define Quad2L          5

#define Quad3S          6
#define Quad3M          7
#define Quad3L          8

#define Quad4S          9
#define Quad4M          10
#define Quad4L          11

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      6

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, LedPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, LedPin2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIXELS, LedPin3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUMPIXELS, LedPin4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(NUMPIXELS, LedPin5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(NUMPIXELS, LedPin6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(NUMPIXELS, LedPin7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(NUMPIXELS, LedPin8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(NUMPIXELS, LedPin9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(NUMPIXELS, LedPin10, NEO_GRB + NEO_KHZ800);

int sampleRate = 500;

unsigned long lastRead;
unsigned long lastReadLights;

boolean lightsOn1;
boolean lightsOn2;
boolean lightsOn3;
boolean lightsOn4;
boolean lightsOn5;
boolean lightsOn6;
boolean lightsOn7;
boolean lightsOn8;
boolean lightsOn9;
boolean lightsOn10;

boolean servo1Detach;
boolean servo2Detach;
boolean servo3Detach;
boolean servo4Detach;
boolean servo5Detach;
boolean servo6Detach;
boolean servo7Detach;
boolean servo8Detach;
boolean servo9Detach;
boolean servo10Detach;

int servoVal1;
int servoVal2;
int servoVal3;
int servoVal4;
int servoVal5;
int servoVal6;
int servoVal7;
int servoVal8;
int servoVal9;
int servoVal10;

int Quad1Sum;
int Quad2Sum;
int Quad3Sum;
int Quad4Sum;

int Quad1SVal;
int Quad2SVal;
int Quad3SVal;
int Quad4SVal;

int Quad1MVal;
int Quad2MVal;
int Quad3MVal;
int Quad4MVal;

int Quad1LVal;
int Quad2LVal;
int Quad3LVal;
int Quad4LVal;

int moveRate = 10;        //the time between updates in milliseconds
int minAngle = 0;     //sets the low point of the movement range
int maxAngle = 180;  //sets the high point of the movement range

int moveIncrement1 = 1;
int moveIncrement2 = 1;
int moveIncrement3 = 1;
int moveIncrement4 = 1;
int moveIncrement5 = 1;
int moveIncrement6 = 1;
int moveIncrement7 = 1;
int moveIncrement8 = 1;
int moveIncrement9 = 1;
int moveIncrement10 = 1;

//long lastTimeYouMoved1;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  setUpLights();
  setUpServos();

}

void loop() {


  if (millis() - lastRead >= sampleRate)
  {
    //    make function that checks the weight
    Quad1Sum = quad1();
    Quad2Sum = quad2();
    Quad3Sum = quad3();
    Quad4Sum = quad4();

    Serial.print("Quad1Sum = ");
    Serial.print(Quad1Sum);

    Serial.print(" Quad2Sum = ");
    Serial.print(Quad2Sum);

    Serial.print("Quad3Sum = ");
    Serial.print(Quad3Sum);

    Serial.print("Quad4Sum = ");
    Serial.print(Quad4Sum);

    Serial.println("");


    if (Quad1Sum > 500) {
      maxServos(1);
    } else if (Quad1Sum > 300) {
      medServos(1);
    } else if (Quad1Sum > 200) {
      minServos(1);
    } else {
      restingServos(1);
    }

    if (Quad2Sum > 500) {
      maxServos(2);
    } else if (Quad2Sum > 300) {
      medServos(2);
    } else if (Quad2Sum > 200) {
      minServos(2);
    } else {
      restingServos(2);
    }

    if (Quad3Sum > 500) {
      maxServos(3);
    } else if (Quad3Sum > 300) {
      medServos(3);
    } else if (Quad3Sum > 200) {
      minServos(3);
    } else {
      restingServos(3);
    }

    if (Quad4Sum > 210) {
      maxServos(4);
    } else if (Quad4Sum > 140) {
      medServos(4);
    } else if (Quad4Sum > 70) {
      minServos(4);
    } else {
      restingServos(4);
    }
    // print a comma to separate the values
    Serial.println();

    lastRead = millis();
  }
}

void setUpServos() {

  servo1.attach(MotorPin1);
  servo2.attach(MotorPin2);
  servo3.attach(MotorPin3);
  servo4.attach(MotorPin4);
  servo5.attach(MotorPin5);
  servo6.attach(MotorPin6);
  servo7.attach(MotorPin7);
  servo8.attach(MotorPin8);
  servo9.attach(MotorPin9);
  servo10.attach(MotorPin10);

  servo1Detach = false;
  servo2Detach = false;
  servo3Detach = false;
  servo4Detach = false;
  servo5Detach = false;
  servo6Detach = false;
  servo7Detach = false;
  servo8Detach = false;
  servo9Detach = false;
  servo10Detach = false;

}

void setUpLights() {

  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
  strip5.begin();
  strip6.begin();
  strip7.begin();
  strip8.begin();
  strip9.begin();
  strip10.begin();

  for (uint16_t i = 0; i < strip1.numPixels(); i++) {
    strip1.setPixelColor(i, strip1.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip1.show();
  }
  for (uint16_t i = 0; i < strip2.numPixels(); i++) {
    strip2.setPixelColor(i, strip2.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip2.show();
  }
  for (uint16_t i = 0; i < strip3.numPixels(); i++) {
    strip3.setPixelColor(i, strip3.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip3.show();
  }
  for (uint16_t i = 0; i < strip4.numPixels(); i++) {
    strip4.setPixelColor(i, strip4.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip4.show();
  }
  for (uint16_t i = 0; i < strip5.numPixels(); i++) {
    strip5.setPixelColor(i, strip5.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip5.show();
  }
  for (uint16_t i = 0; i < strip6.numPixels(); i++) {
    strip6.setPixelColor(i, strip6.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip6.show();
  }
  for (uint16_t i = 0; i < strip7.numPixels(); i++) {
    strip7.setPixelColor(i, strip7.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip7.show();
  }
  for (uint16_t i = 0; i < strip8.numPixels(); i++) {
    strip8.setPixelColor(i, strip8.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip8.show();
  }
  for (uint16_t i = 0; i < strip9.numPixels(); i++) {
    strip9.setPixelColor(i, strip9.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip9.show();
  }
  for (uint16_t i = 0; i < strip10.numPixels(); i++) {
    strip10.setPixelColor(i, strip10.Color(0, 0 , 0)); //turn every third pixel on
    // strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip10.show();

  }
}

int quad1() {

  Quad1SVal = analogRead(Quad1S);
  Quad1MVal = analogRead(Quad1M);
  Quad1LVal = analogRead(Quad1L);

  Quad1Sum = Quad1SVal + Quad1MVal + Quad1LVal;

  // print out the sensor value
  Serial.print("quad 1 small: ");
  Serial.print(Quad1S);
  Serial.print(" quad 1 medium: ");
  Serial.print(Quad1M);
  Serial.print(" quad 1 large: ");
  Serial.print(Quad1L);
  Serial.println();

  return Quad1Sum;

}
int quad2() {

  Quad2SVal = analogRead(Quad2S);
  Quad2MVal = analogRead(Quad2M);
  Quad2LVal = analogRead(Quad2L);

  Quad2Sum = Quad2SVal + Quad2MVal + Quad2LVal;

  // print out the sensor value
  Serial.print("quad 2 small: ");
  Serial.print(Quad2SVal);
  Serial.print(" quad 2 medium: ");
  Serial.print(Quad2MVal);
  Serial.print(" quad 2 large: ");
  Serial.print(Quad2LVal);
  Serial.println();

  return Quad2Sum;

}
int quad3() {

  Quad3SVal = analogRead(Quad3S);
  Quad3MVal = analogRead(Quad3M);
  Quad3LVal = analogRead(Quad3L);

  Quad3Sum = Quad3SVal + Quad3MVal + Quad3LVal;

  // print out the sensor value
  Serial.print("quad 3 small: ");
  Serial.print(Quad3SVal);
  Serial.print(" quad 3 medium: ");
  Serial.print(Quad3MVal);
  Serial.print(" quad 3 large: ");
  Serial.print(Quad3LVal);
  Serial.println();

  return Quad3Sum;

}
int quad4() {

  Quad4SVal = analogRead(Quad4S);
  Quad4MVal = analogRead(Quad4M);
  Quad4LVal = analogRead(Quad4L);

  Quad4Sum = Quad4SVal + Quad4MVal + Quad4LVal;
  // print out the sensor value
  Serial.print("quad 4 small: ");
  Serial.print(Quad4SVal);
  Serial.print(" quad 4 medium: ");
  Serial.print(Quad4MVal);
  Serial.print(" quad 4 large: ");
  Serial.print(Quad4LVal);
  Serial.println();

  return Quad4Sum;
}

int maxServos(int quad) {

  switch (quad) {
    case 1:
      if (servo1Detach == true) {
        servo1.attach(MotorPin1);
        servo1Detach == false;
      }
      if (servo2Detach == true) {
        servo2.attach(MotorPin2);
        servo2Detach == false;
      }
      if (servo3Detach == true) {
        servo3.attach(MotorPin3);
        servo3Detach == false;
      }


      ledLights1(255);
      ledLights2(255);
      ledLights3(255);

      moveServo1();
      moveServo2();
      moveServo3();

      // turn on all the motors
      break;
    case 2:

      if (servo4Detach == true) {
        servo4.attach(MotorPin4);
        servo4Detach == false;
      }
      if (servo5Detach == true) {
        servo5.attach(MotorPin5);
        servo5Detach == false;
      }
      if (servo6Detach == true) {
        servo6.attach(MotorPin6);
        servo6Detach == false;
      }

      moveServo4();
      moveServo5();
      moveServo6();


      ledLights4(255);
      ledLights5(255);
      ledLights6(255);
      // turns on all the motors
      break;

    case 3:
      if (servo7Detach == true) {
        servo7.attach(MotorPin7);
        servo7Detach == false;
      }
      if (servo8Detach == true) {
        servo8.attach(MotorPin8);
        servo8Detach == false;
      }

      moveServo7();
      moveServo8();

      ledLights7(255);
      ledLights8(255);
      // turn on all the motors
      break;

    case 4:
      if (servo9Detach == true) {
        servo9.attach(MotorPin9);
        servo9Detach == false;
      }
      if (servo10Detach == true) {
        servo10.attach(MotorPin10);
        servo10Detach == false;
      }

      moveServo9();
      moveServo10();

      ledLights9(255);
      ledLights10(255);
      // turns on all the motors
      break;
    default:
      // turns on all the motors
      break;
  }

}

int medServos(int quad) {

  switch (quad) {
    case 1:
      if (servo1Detach == true) {
        servo1.attach(MotorPin1);
        servo1Detach == false;
      }
      if (servo2Detach == true) {
        servo2.attach(MotorPin2);
        servo2Detach == false;
      }

      moveServo1();
      moveServo2();

      ledLights1(115);
      ledLights2(115);
      ledLights3(55);
      // turn on all the motors
      break;
    case 2:
      if (servo4Detach == true) {
        servo4.attach(MotorPin4);
        servo4Detach == false;
      }
      if (servo5Detach == true) {
        servo5.attach(MotorPin5);
        servo5Detach == false;
      }

      moveServo4();
      moveServo5();

      ledLights4(115);
      ledLights5(115);
      ledLights6(55);
      // turns on all the motors
      break;
    case 3:
      if (servo7Detach == true) {
        servo7.attach(MotorPin7);
        servo7Detach == false;
      }

      moveServo7();

      ledLights7(115);
      ledLights8(55);
      // turn on all the motors
      break;
    case 4:
      if (servo9Detach == true) {
        servo9.attach(MotorPin9);
        servo9Detach == false;
      }

      moveServo9();

      ledLights9(115);
      ledLights10(55);
  }
}
int minServos(int quad) {

  switch (quad) {
    case 1:

      int randQuad1min = random(1, 3);

      if (randQuad1min == 1) {
        if (servo1Detach == true) {
          servo1.attach(MotorPin1);
          servo1Detach == false;
        }
        moveServo1();
        ledLights1(115);

        servo2.detach();
        servo2Detach = true;

        servo3.detach();
        servo3Detach = true;

        ledLights2(50);
        ledLights3(50);


      } else if (randQuad1min == 2) {
        if (servo2Detach == true) {
          servo2.attach(MotorPin2);
          servo2Detach == false;

        }
        moveServo2();
        ledLights2(155);

        servo1.detach();
        servo1Detach = true;

        servo3.detach();
        servo3Detach = true;

        ledLights1(50);
        ledLights3(50);

      } else {
        if (servo3Detach == true) {
          servo3.attach(MotorPin3);
          servo3Detach == false;

        }
        moveServo3();
        ledLights3(155);

        servo1.detach();
        servo1Detach = true;

        servo2.detach();
        servo2Detach = true;

        ledLights1(50);
        ledLights2(50);

      }

      // turn on all the motors
      break;
    case 2:

      int randQuad2min = random(4, 6);
      if (randQuad2min == 4) {
        if (servo4Detach == true) {
          servo4.attach(MotorPin4);
          servo4Detach == false;
        }

        moveServo4();
        ledLights4(50);

        servo5.detach();
        servo5Detach = true;

        servo6.detach();
        servo6Detach = true;

        ledLights5(50);
        ledLights6(50);

      } else if (randQuad2min == 5) {
        if (servo5Detach == true) {
          servo5.attach(MotorPin5);
          servo5Detach == false;
        }
        moveServo5();
        ledLights5(155);


        servo4.detach();
        servo4Detach = true;
        servo6.detach();
        servo6Detach = true;

        ledLights4(50);
        ledLights6(50);

      } else {
        if (servo6Detach == true) {
          servo6.attach(MotorPin6);
          servo6Detach == false;
        }
        moveServo6();
        ledLights6(155);

        servo4.detach();
        servo4Detach = true;
        servo5.detach();
        servo5Detach = true;

        ledLights4(50);
        ledLights5(50);

      }

      // turns on all the motors
      break;
    case 3:

      int randQuad3min = random(7, 8);
      if (randQuad3min == 7) {
        if (servo7Detach == true) {
          servo7.attach(MotorPin7);
          servo7Detach == false;
        }
        moveServo7();
        ledLights7(155);

        servo8.detach();
        servo8Detach = true;

        ledLights8(55);

      } else {
        if (servo8Detach == true) {
          servo8.attach(MotorPin8);
          servo8Detach == false;
        }
        moveServo8();
        ledLights8(155);

        servo7.detach();
        servo7Detach = true;
        ledLights7(55);

      }
      // turn on all the motors
      break;
    case 4:
      int randQuad4min = random(9, 10);
      if (randQuad4min == 8) {
        if (servo9Detach == true) {
          servo9.attach(MotorPin9);
          servo9Detach == false;
        }
        moveServo9();
        ledLights9(155);

        servo10.detach();
        servo10Detach = true;

        ledLights6(55);

      } else {

        if (servo10Detach == true) {
          servo10.attach(MotorPin10);
          servo10Detach == false;
        }
        moveServo10();
        ledLights10(155);

        servo9.detach();
        servo9Detach = true;

        ledLights9(55);

      }
  }
}
int restingServos(int quad) {

  switch (quad) {
    case 1:
      servo1.detach();
      servo1Detach = true;
      servo2.detach();
      servo2Detach = true;
      servo3.detach();
      servo3Detach = true;

      ledLights1(25);
      ledLights2(25);
      ledLights3(25);

      break;

    case 2:
      servo4.detach();
      servo4Detach = true;

      servo5.detach();
      servo5Detach = true;

      servo6.detach();
      servo6Detach = true;


      ledLights4(25);
      ledLights5(25);
      ledLights6(25);

      break;
    case 3:
      servo7.detach();
      servo7Detach = true;

      servo8.detach();
      servo8Detach = true;

      ledLights7(25);
      ledLights8(25);

      break;
    case 4:
      servo9.detach();
      servo9Detach = true;

      servo10.detach();
      servo10Detach = true;

      ledLights9(25);
      ledLights10(25);

      break;
    default:
      // turns on all the motors
      break;
  }

}

void moveServo1() {
  servo1.write(servoVal1);

  servoVal1 += moveIncrement1;

  if (servoVal1 <= minAngle || servoVal1 >= maxAngle)
  {
    moveIncrement1 = -moveIncrement1;
  }

}
void moveServo2() {
  servo2.write(servoVal2);

  servoVal2 += moveIncrement2;

  if (servoVal2 <= minAngle || servoVal2 >= maxAngle)
  {
    moveIncrement2 = -moveIncrement2;
  }

}
void moveServo3() {
  servo3.write(servoVal3);

  servoVal3 += moveIncrement3;

  if (servoVal3 <= minAngle || servoVal3 >= maxAngle)
  {
    moveIncrement3 = -moveIncrement3;
  }
}
void moveServo4() {
  servo4.write(servoVal4);

  servoVal4 += moveIncrement4;

  if (servoVal4 <= minAngle || servoVal4 >= maxAngle)
  {
    moveIncrement4 = -moveIncrement4;
  }
}
void moveServo5() {
  servo5.write(servoVal5);

  servoVal5 += moveIncrement5;

  if (servoVal5 <= minAngle || servoVal5 >= maxAngle)
  {
    moveIncrement5 = -moveIncrement5;
  }
}
void moveServo6() {
  servo6.write(servoVal6);

  servoVal6 += moveIncrement6;

  if (servoVal6 <= minAngle || servoVal6 >= maxAngle)
  {
    moveIncrement6 = -moveIncrement6;
  }
}
void moveServo7() {
  servo7.write(servoVal7);

  servoVal7 += moveIncrement7;

  if (servoVal7 <= minAngle || servoVal7 >= maxAngle)
  {
    moveIncrement7 = -moveIncrement7;
  }
}
void moveServo8() {
  servo8.write(servoVal8);

  servoVal8 += moveIncrement8;

  if (servoVal8 <= minAngle || servoVal8 >= maxAngle)
  {
    moveIncrement8 = -moveIncrement8;
  }
}
void moveServo9() {
  servo9.write(servoVal9);

  servoVal9 += moveIncrement9;

  if (servoVal9 <= minAngle || servoVal9 >= maxAngle)
  {
    moveIncrement9 = -moveIncrement9;
  }
}
void moveServo10() {

  servo10.write(servoVal10);

  servoVal10 += moveIncrement10;

  if (servoVal10 <= minAngle || servoVal10 >= maxAngle)
  {
    moveIncrement10 = -moveIncrement10;
  }
}

int ledLights1(int brightness) {

  if (lightsOn1) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip1.setPixelColor(i + 1, strip1.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip1.setPixelColor(i - 2, strip1.Color(0, 0, 0));
      strip1.show();
    }
    lightsOn1 = !lightsOn1;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip1.setPixelColor(i + 1, strip1.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip1.setPixelColor(i - 2, strip1.Color(250, 0 , 0));
      strip1.show();
    }
    lightsOn1 = !lightsOn1;
  }
}

int ledLights2(int brightness) {

  if (lightsOn2) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip2.setPixelColor(i + 1, strip2.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip2.setPixelColor(i - 2, strip2.Color(0, 0, 0));
      strip2.show();
    }
    lightsOn2 = !lightsOn2;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip2.setPixelColor(i + 1, strip2.Color(0, 0, 0)); //turn every third pixel on
      strip2.setPixelColor(i - 2, strip2.Color(brightness, brightness, brightness));
      strip2.show();
    }
    lightsOn2 = !lightsOn2;
  }
}

int ledLights3(int brightness) {

  if (lightsOn3) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip3.setPixelColor(i + 1, strip3.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip3.setPixelColor(i - 2, strip3.Color(0, 0, 0));
      strip3.show();
    }
    lightsOn3 = !lightsOn3;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip3.setPixelColor(i + 1, strip3.Color(0, 0, 0)); //turn every third pixel on
      strip3.setPixelColor(i - 2, strip3.Color(brightness, brightness, brightness));
      strip3.show();
    }
    lightsOn3 = !lightsOn3;
  }
}

int ledLights4(int brightness) {

  if (lightsOn4) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip4.setPixelColor(i + 1, strip4.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip4.setPixelColor(i - 2, strip4.Color(0, 0, 0));
      strip4.show();
    }
    lightsOn4 = !lightsOn4;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip4.setPixelColor(i + 1, strip4.Color(0, 0, 0)); //turn every third pixel on
      strip4.setPixelColor(i - 2, strip4.Color(brightness, brightness, brightness));
      strip4.show();
    }
    lightsOn4 = !lightsOn4;
  }
}

int ledLights5(int brightness) {

  if (lightsOn5) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip5.setPixelColor(i + 1, strip5.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip5.setPixelColor(i - 2, strip5.Color(0, 0, 0));
      strip5.show();
    }
    lightsOn5 = !lightsOn5;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip5.setPixelColor(i + 1, strip5.Color(0, 0, 0)); //turn every third pixel on
      strip5.setPixelColor(i - 2, strip5.Color(brightness, brightness, brightness));
      strip5.show();
    }
    lightsOn5 = !lightsOn5;
  }
}

int ledLights6(int brightness) {

  if (lightsOn6) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip6.setPixelColor(i + 1, strip6.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip6.setPixelColor(i - 2, strip6.Color(0, 0, 0));
      strip6.show();
    }
    lightsOn6 = !lightsOn6;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip6.setPixelColor(i + 1, strip6.Color(0, 0, 0)); //turn every third pixel on
      strip6.setPixelColor(i - 2, strip6.Color(brightness, brightness, brightness));
      strip6.show();
    }
    lightsOn6 = !lightsOn6;
  }
}

int ledLights7(int brightness) {

  if (lightsOn7) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip7.setPixelColor(i + 1, strip7.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip7.setPixelColor(i - 2, strip7.Color(0, 0, 0));
      strip7.show();
    }
    lightsOn7 = !lightsOn7;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip7.setPixelColor(i + 1, strip7.Color(0, 0, 0)); //turn every third pixel on
      strip7.setPixelColor(i - 2, strip7.Color(brightness, brightness, brightness));
      strip7.show();
    }
    lightsOn7 = !lightsOn7;
  }
}

int ledLights8(int brightness) {

  if (lightsOn8) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip8.setPixelColor(i + 1, strip8.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip8.setPixelColor(i - 2, strip8.Color(0, 0, 0));
      strip8.show();
    }
    lightsOn8 = !lightsOn8;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip8.setPixelColor(i + 1, strip8.Color(0, 0, 0)); //turn every third pixel on
      strip8.setPixelColor(i - 2, strip8.Color(brightness, brightness, brightness));
      strip8.show();
    }
    lightsOn8 = !lightsOn8;
  }
}

int ledLights9(int brightness) {

  if (lightsOn9) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip9.setPixelColor(i + 1, strip9.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip9.setPixelColor(i - 2, strip9.Color(0, 0, 0));
      strip9.show();
    }
    lightsOn9 = !lightsOn9;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip9.setPixelColor(i + 1, strip9.Color(0, 0, 0)); //turn every third pixel on
      strip9.setPixelColor(i - 2, strip9.Color(brightness, brightness, brightness));
      strip9.show();
    }
    lightsOn9 = !lightsOn9;
  }
}

int ledLights10(int brightness) {

  if (lightsOn10) {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip10.setPixelColor(i + 1, strip10.Color(brightness, brightness, brightness)); //turn every third pixel on
      strip10.setPixelColor(i - 2, strip10.Color(0, 0, 0));
      strip10.show();
    }
    lightsOn10 = !lightsOn10;
  } else {
    for (int i = 0; i < NUMPIXELS; i = i + 2) {
      strip10.setPixelColor(i + 1, strip10.Color(0, 0, 0)); //turn every third pixel on
      strip10.setPixelColor(i - 2, strip10.Color(brightness, brightness, brightness));
      strip10.show();
    }
    lightsOn10 = !lightsOn10;
  }
}

#include <Time.h> 
#include <Servo.h>

//#define CALIBRATION      // enable calibration mode
//#define REALTIMECLOCK    // enable real time clock

#define WISHY 3 // Offset of the Y coordinats of the plate-wisher

// When in calibration mode, adjust the following factors until the servos move exactly 90 degrees
#define SERVOFAKTORLEFT 550
#define SERVOFAKTORRIGHT 600

// Zero-position of left and right servo
// When in calibration mode, adjust the NULL-values so that the servo arms are at all times parallel
// either to the X or Y axis
#define SERVOLEFTNULL 1950
#define SERVORIGHTNULL 815

#define SERVOPINLIFT  3
#define SERVOPINLEFT  7
#define SERVOPINRIGHT 9

#define ZOFF 90
// lift positions of lifting servo
#define LIFT0 2000+ZOFF // on drawing surface
#define LIFT1 995+ZOFF  // between numbers
#define LIFT2 735+ZOFF  // going towards sweeper

// speed of liftimg arm, higher is slower
#define LIFTSPEED 2000

// length of arms
#define L1 35
#define L2 55.1
#define L3 13.2
#define L4 45

// origin points of left and right servo 
#define O1X 24//22
#define O1Y -25
#define O2X 49//47
#define O2Y -25


#ifdef REALTIMECLOCK
// for instructions on how to hook up a real time clock,
// see here -> http://www.pjrc.com/teensy/td_libs_DS1307RTC.html
// DS1307RTC works with the DS1307, DS1337 and DS3231 real time clock chips.
// Please run the SetTime example to initialize the time on new RTC chips and begin running.

#include <Wire.h>
#include <DS1307RTC.h> // see http://playground.arduino.cc/Code/time    
#endif

int servoLift = 1500;

Servo servo1;  // 
Servo servo2;  // 
Servo servo3;  // 

volatile double lastX = 0;
volatile double lastY = 47.5;

int last_min = 0;

void setup() 
{ 
  servo1.attach(SERVOPINLIFT);  //  lifting servo
  servo2.attach(SERVOPINLEFT);  //  left servo
  servo3.attach(SERVOPINRIGHT);  //  right servo
  delay(1000);

  
   number(13, 1, 7, 1.2); // -
   number(27, 8, 1, 0.8); // |
   number(13, -19.5, 72, 1.5);// -
  
   number(41, 7.5, 12, 1);//|
   number(32, -3.5, 0, 1);//o
  
  
   number(46, 3, 0, 1.3);//o
  
    delay(4000);
  
   number(3, 3, 111, 1); 
} 

void loop() {} 

void number(float bx, float by, int num, float scale) {

  switch (num) {

  case 0:
    drawTo(bx + 5 * scale, by + 7 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 10  * scale, 5 * scale, 4.7, -2.5, 1);
   // bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
    lift(1);
    break;
    
  case 1:
    drawTo(bx -13 * scale, by + 20 * scale);
    lift(0);
    drawTo(bx * scale, by + 20 * scale);
    drawTo(bx * scale, by + 0 * scale);
    lift(1);
    break;
    
  case 12:
  drawTo(bx  * scale, by - 10 * scale);
  lift(0);
  drawTo(bx * scale, by + 30 * scale);
  drawTo(bx * scale, by + 0 * scale);
  lift(1);
  break; 
   
  case 2:
    drawTo(bx + 2 * scale, by + 12 * scale);
    lift(0);
    bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
    drawTo(bx + 1 * scale, by + 0 * scale);
    //drawTo(bx + 12 * scale, by + 0 * scale);
    lift(1);
    break;
    
  case 3:
    drawTo(bx + 2 * scale, by + 17 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
    bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
    lift(1);
    break;
    
  case 4:
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 6 * scale);
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(1);
    break;
    
  case 5:
    drawTo(bx + 2 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
    drawTo(bx + 5 * scale, by + 20 * scale);
    drawTo(bx + 12 * scale, by + 20 * scale);
    lift(1);
    break;
    
  case 6:
    drawTo(bx + 2 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
    drawTo(bx + 11 * scale, by + 20 * scale);
    lift(1);
    break;
    
  case 7:
    drawTo(bx + 0 * scale, by + 20 * scale);
    lift(0);
    drawTo(bx + 12 * scale, by + 20 * scale);
    //drawTo(bx + 2 * scale, by + 0);
    lift(1);
    break;
    
  case 72:
    drawTo(bx + 0 * scale, by + 20 * scale);
    lift(0);
    drawTo(bx + 11 * scale, by + 17 * scale);
    //drawTo(bx + 2 * scale, by + 0);
    lift(1);
    break;
    
  case 8:
    drawTo(bx + 5 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 12 * scale, 5 * scale, 4.7, -1.6, 1);
    //bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
    lift(1);
    break;

  case 9:
    drawTo(bx + 9 * scale, by + 11 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
    drawTo(bx + 5 * scale, by + 0);
    lift(1);
    break;
    
  case 111:
  drawTo(87, 36);
  
    lift(0);
    drawTo(70, 45);
    drawTo(70, 42);
    drawTo(40-WISHY, 45);
    drawTo(65-WISHY, 40);
    drawTo(65-WISHY, 40);
    
    drawTo(5, 49);
    drawTo(5, 46);
    drawTo(63-WISHY, 46);
    drawTo(63-WISHY, 42);
    
    drawTo(5, 42);
    drawTo(5, 38);
    drawTo(63-WISHY, 38);
    drawTo(63-WISHY, 34);

    drawTo(5, 34);
    drawTo(5, 29);
    drawTo(63-WISHY, 29);
    drawTo(63-WISHY, 25);
    drawTo(5, 25);
    drawTo(5, 20);
    drawTo(63-WISHY, 20);
    drawTo(63-WISHY, 15);
    drawTo(5, 15);
    drawTo(5, 10);
    drawTo(5, 5);
    drawTo(63-WISHY, 5);
    drawTo(63-WISHY, 0);
    drawTo(5, 0);
    drawTo(63-WISHY, 32);
    drawTo(63-WISHY, 40);
    drawTo(5, 15);
    drawTo(5, 5);
    
    drawTo(6, 37);
    drawTo(87-WISHY, 29);
    drawTo(9, 33);
    drawTo(87-WISHY, 29);

    drawTo(95, 40);
    drawTo(87, 35);
    delay(500);
    
    lift(1);
    delay(1000);
    lift(2);
    
    delay(1000);
    lift(2);
    lift(2);
    break;

  case 11:
    drawTo(bx + 5 * scale, by + 15 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
    delay(10);
    lift(1);
    drawTo(bx + 5 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
    delay(10);
    lift(1);
    break;

  }
}



void lift(char lift) {
  switch (lift) {
    // room to optimize  !

  case 0: //850

      if (servoLift >= LIFT0) {
      while (servoLift >= LIFT0) 
      {
        servoLift--;
        servo1.writeMicroseconds(servoLift);				
        delayMicroseconds(LIFTSPEED);
      }
    } 
    else {
      while (servoLift <= LIFT0) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(LIFTSPEED);

      }

    }

    break;

  case 1: //150

    if (servoLift >= LIFT1) {
      while (servoLift >= LIFT1) {
        servoLift--;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(LIFTSPEED);

      }
    } 
    else {
      while (servoLift <= LIFT1) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(LIFTSPEED);
      }

    }

    break;

  case 2:

    if (servoLift >= LIFT2) {
      while (servoLift >= LIFT2) {
        servoLift--;
        servo1.writeMicroseconds(servoLift);
        delayMicroseconds(LIFTSPEED);
      }
    } 
    else {
      while (servoLift <= LIFT2) {
        servoLift++;
        servo1.writeMicroseconds(servoLift);				
        delayMicroseconds(LIFTSPEED);
      }
    }
    break;
  }
}


void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = -0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) > ende);

}

void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = 0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) <= ende);
}


void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  //path lenght in mm, times 4 equals 4 steps per mm
  c = floor(7 * sqrt(dx * dx + dy * dy));

  if (c < 1) c = 1;

  for (i = 0; i <= c; i++) {
    // draw line point by point
    set_XY(lastX + (i * dx / c), lastY + (i * dy / c));

  }

  lastX = pX;
  lastY = pY;
}

double return_angle(double a, double b, double c) {
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

void set_XY(double Tx, double Ty) 
{
  delay(1);
  double dx, dy, c, a1, a2, Hx, Hy;

  // calculate triangle between pen, servoLeft and arm joint
  // cartesian dx/dy
  dx = Tx - O1X;
  dy = Ty - O1Y;

  // polar lemgth (c) and angle (a1)
  c = sqrt(dx * dx + dy * dy); // 
  a1 = atan2(dy, dx); //
  a2 = return_angle(L1, L2, c);

  servo2.writeMicroseconds(floor(((a2 + a1 - M_PI) * SERVOFAKTORLEFT) + SERVOLEFTNULL));

  // calculate joinr arm point for triangle of the right servo arm
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5°
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  // calculate triangle between pen joint, servoRight and arm joint
  dx = Hx - O2X;
  dy = Hy - O2Y;

  c = sqrt(dx * dx + dy * dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, L4, c);

  servo3.writeMicroseconds(floor(((a1 - a2) * SERVOFAKTORRIGHT) + SERVORIGHTNULL));
}

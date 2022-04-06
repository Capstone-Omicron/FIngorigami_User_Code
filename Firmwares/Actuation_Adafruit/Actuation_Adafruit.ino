//Servo
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  90// This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  490 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  SERVOMIN*4 // 600, This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  SERVOMAX*4 // 2400, This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates\

#define MAX_DELAY 500 // Slowest speed of motor
#define MIN_DELAY 10 // Fastest speed of motor

const int servonum0 = 0;
const int servonum1 = 1;
int angleX = 90;
int angleY = 90;
int pulselenX = map(angleX, 0, 180, SERVOMIN, SERVOMAX);
int pulselenY = map(angleY, 0, 180, SERVOMIN, SERVOMAX);

//FSR
#define FORCE_SENSOR_PIN A0 // the FSR and 10K pulldown are connected to A0
int forceRead = 0;
float force = 0;
const int e = 2.718281828;
const int forceReadThres = 500;

//Joystick
#define joyX A1
#define joyY A2

int xValue;
int yValue;

const int x_0 = 1024/2;
const int y_0 = 1024/2;
const int joyMax = 1024;
const int joyMin = 0;
const int joyBuffer = 30;

int delay_speed_X = map(x_0, x_0, joyMax, MAX_DELAY, MIN_DELAY);
int delay_speed_Y = map(y_0, y_0, joyMax, MAX_DELAY, MIN_DELAY);

int countX = 0;
int countY = 0;

int joyStick = 0;

void setup() {
  Serial.begin(9600); //how fast it reads every byte (bytes per second)
  pwm.begin();

  pwm.setOscillatorFrequency(25250000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  pwm.setPWM(servonum0, 0, pulselenX);
  pwm.setPWM(servonum1, 0, pulselenY);
  delay(20);
}

void loop() {
  // Read Force values
  forceRead = analogRead(FORCE_SENSOR_PIN);
  force = forceConvert(forceRead);
  
  // Read Joystick values
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  // Control Motors
  if(countX == 0){
    if (xValue > (x_0 + joyBuffer)){
      if (pulselenX<SERVOMAX){
        pulselenX++;
        countX = map(xValue, x_0, joyMax, MAX_DELAY, MIN_DELAY);
      }
    }else if(xValue < (x_0 - joyBuffer)){
      if (pulselenX>SERVOMIN){
        pulselenX--;
        countX = map(xValue, x_0, joyMin, MAX_DELAY, MIN_DELAY);
      }
    } 
    pwm.setPWM(servonum0, 0, pulselenX);
  } else {
    countX--;
  }

  if(countY == 0){
    if (yValue > (y_0 + joyBuffer)){
      if (pulselenY<SERVOMAX){
        pulselenY++;
        countY = map(yValue, y_0, joyMax, MAX_DELAY, MIN_DELAY);
      }
    }else if(yValue < (y_0 - joyBuffer)){
      if (pulselenY>SERVOMIN){
        pulselenY--;
        countY = map(yValue, y_0, joyMin, MAX_DELAY, MIN_DELAY);
      }
    } 
    pwm.setPWM(servonum1, 0, pulselenY);
  } else {
    countY--;
  }

  // Print to Serial
//  Serial.print(xValue);
//  Serial.print("\t");
//  Serial.print(yValue);
  
//  Serial.print("\t");
//  Serial.print(pulselenX);
  angleX = map(pulselenX, SERVOMIN, SERVOMAX, 0, 180);
//  Serial.print("\t");
  Serial.print(angleX);

//  Serial.print("\t");
//  Serial.print(pulselenY);
  angleY = map(pulselenY, SERVOMIN, SERVOMAX, 0, 180);
  Serial.print("\t");
  Serial.print(angleY);

  Serial.print("\t");
  Serial.println(force);
}

float forceConvert(int forceRead){
  if (forceRead <= forceReadThres){
    force = exp((forceRead+1069.3)/302.77); //[g]
  } else {
    force = exp((forceRead+229.09)/157.2); //[g];
  } 
  return force;
}

//Servo
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  90// This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  490 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  SERVOMIN*4 // 600, This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  SERVOMAX*4 // 2400, This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;

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

const int x_0 = 510;
const int y_0 = 489;

const int threshold_dif = 100;

int pulselenX = SERVOMIN;
int pulselenY = SERVOMIN;
int pulselen = SERVOMIN;

void setup() {
  Serial.begin(9600); //how fast it reads every byte (bytes per second)
  pwm.begin();

  pwm.setOscillatorFrequency(25250000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  //Set to specific angle
  pulselen = SERVOMAX; //MAX extend at 290
  pwm.setPWM(servonum=0, 0, pulselen);
  
  delay(10);
}

void loop() {
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
//    pwm.setPWM(servonum=0, 0, pulselen);
//    pwm.setPWM(servonum=1, 0, pulselen);
//    forceRead = analogRead(FORCE_SENSOR_PIN);
//    force = forceConvert(forceRead);
//    Serial.println (force);
//    delay(100);
//  }
//  delay(500);
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//    pwm.setPWM(servonum=0, 0, pulselen);
//    pwm.setPWM(servonum=1, 0, pulselen);
//    forceRead = analogRead(FORCE_SENSOR_PIN);
//    force = forceConvert(forceRead);
//    Serial.println (force);
//    delay(100);
//  }

  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  
  if (xValue > x_0 + threshold_dif && xValue < SERVOMAX){
    pulselen++;
  } else if (xValue < x_0 - threshold_dif && xValue > SERVOMIN){
    pulselen--;
  }
  Serial.println(pulselen);
}

float forceConvert(int forceRead){
  if (forceRead <= forceReadThres){
    force = exp((forceRead+1069.3)/302.77); //[g]
  } else {
    force = exp((forceRead+229.09)/157.2); //[g];
  } 
  return force;
}

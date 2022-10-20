#include <Arduino.h>
#include "SoftwareSerial.h"
#include "pressure.h"
#include "brewfather.h"

const int adcmax = 4095;

const int pressureInput = 34; //select the analog input pin for the pressure transducer
const float pressuretransducermaxmpa = 0.2000; //mpa value of transducer being used
//const int sensorreadDelay = 60*1000; //Take a reading once per minute
const int sensorreadDelay = 5000;
const int numReadings = 15;     //Average 15 readings

const float voltageBuffer = 3.3*0.1; //10% of range at each end is not used (ie 0.5..4.5v)
const float mpaToPsi = 145.037737797;


float rawAnalog = 0;
float mpa;
extern float psi;

void getPressure(){
  rawAnalog = analogRead(pressureInput);
  //readings[readIndex] = analogRead(pressureInput);
  //convertToPSI(readings[readIndex]);
  float voltage = rawAnalog/adcmax*3.3;
  mpa = (voltage - voltageBuffer) * pressuretransducermaxmpa / ((3.3-voltageBuffer) - voltageBuffer);
  psi = mpa * mpaToPsi;
  delay(sensorreadDelay); //delay in milliseconds between read values
}
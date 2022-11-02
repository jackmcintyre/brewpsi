#include <Arduino.h>
#include "SoftwareSerial.h"
#include "pressure.h"
#include "brewfather.h"
// #include <driver/adc.h>
// #include "esp_adc_cal.h"

#include <ESP32AnalogRead.h>
ESP32AnalogRead adc;

extern float psi;
extern float bar;

const int pressureInput = 34; //select the analog input pin for the pressure transducer

const float sensorMin = 0.0000; //mpa value of transducer being used
const float sensorMax = 0.2000; //mpa value of transducer being used
//const int sensorreadDelay = 60*1000; //Take a reading once per minute
const int sensorreadDelay = 1000; //Take a reading once per second
//const int numReadings = 15;     //Average 15 readings

const float mpaToPsi = 145.037737797;

void setupPressure(){
  adc.attach(34);
}

void getPressure(){
  //int rawAnalog = analogRead(pressureInput);
  float voltage = adc.readVoltage();
  float mpa = mapFloat(voltage, 0.33, 2.97, sensorMin, sensorMax);    // variation on the Arduino map() function

  psi = mpa * mpaToPsi;
  bar = mpa * 10;

  //Serial.println("raw " + String(rawAnalog) + " psi: " + String(psi,1)+ " mpa: " + String(mpa) + " v: " + String(voltage));

  delay(sensorreadDelay); //delay in milliseconds between read values
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
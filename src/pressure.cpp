#include <Arduino.h>
#include "SoftwareSerial.h"
#include "pressure.h"
#include "brewfather.h"

//TODO: 4095?
const int adcmax = 4095;

const int pressureInput = 34; //select the analog input pin for the pressure transducer
const float pressuretransducermaxmpa = 0.2000; //mpa value of transducer being used
const int sensorreadDelay = 60*1000; //Take a reading once per minute
//const int sensorreadDelay = 100; //Accelerate readings for dev
const int numReadings = 15;     //Average 15 readings
//const float value = 0;
  
//float pressureValue = 0;        //variable to store the value coming from the pressure transducer

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
//int readIndex = 13;              // force an API call at startup
int total = 0;                  // the running total
int average = 0;                // the average

float rawAnalog = 0;

float convertToPSI(float rawAnalog){

  // Serial.print(rawAnalog,8);
  // Serial.print("\n");

  float voltage = rawAnalog/adcmax*3.3;

  float mpa = (voltage - 0.33) * pressuretransducermaxmpa / (2.97 - 0.33);

  //basic PSI to MPa
  float psi = mpa * 145.037737797;

  return(psi);
}

void getPressure(){
  //readings[readIndex] = analogRead(pressureInput);
  //readings[readIndex] = 410;
  readings[readIndex] = 3686;

  //for debugging. Effective range 103-921 with 1023 range adc.
  // expect ~*4 for esp32 412 - 36841

  Serial.print(readIndex);

  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  
  if (readIndex >= numReadings) {
    log_brewfather(convertToPSI(average));
    readIndex = 0;
    total = 0;
    
  }

  average = total / numReadings;    
  delay(sensorreadDelay); //delay in milliseconds between read values
}

//shuffle the above to allow PSI to be returned to main. Ideally, individual readings. May mean having two calls from main - one that returns lots of raw values, and another that averages them before sending to BF
#include <Arduino.h>
#include "SoftwareSerial.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

float psi;
int loopCount = 15; //Loop 15 times before posting to brewfather. Do maths working back from 15 mins.
int readingCount = 0;

//#include "main.h"
#include "pressure.h"
#include "screen.h"

void setup(){
  Serial.begin(115200);
  
  printSplashScreen();

  // move wifi stuff to own file?

  WiFiManager wm;
  bool res;
  res = wm.autoConnect("brewPSI","brewpsi1");

  if(!res) {
    Serial.println("Failed to connect");
  } 
  else {
    Serial.println("Wifi Connected!");
  }

}

void loop(){
  getPressure();

  if (readingCount >= loopCount) {
    //log to brewfather
    Serial.print("Log to BF");
    Serial.print("\n");
    readingCount = 0;
  }
  readingCount = readingCount + 1;
  printToScreen(psi);
} 
  
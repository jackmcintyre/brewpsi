#include <Arduino.h>
#include "SoftwareSerial.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

float psi;
float bar;
int loopCount = 60*15; //every 15 minutes, post to brewfather
int readingCount = 0;

//#include "main.h"
#include "pressure.h"
#include "screen.h"
#include "brewfather.h"

void setup(){
  Serial.begin(115200);
  
  screenSetup();
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

  Serial.println(String(psi) + " psi");

  if (readingCount >= loopCount) {
    log_brewfather();
    readingCount = 0;
  }
  readingCount = readingCount + 1;
  printToScreen();
} 
  
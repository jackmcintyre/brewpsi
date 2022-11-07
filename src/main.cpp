#include <Arduino.h>
#include "SoftwareSerial.h"
#include <WiFiManager.h>
#include <LittleFS.h>
#include <FS.h>

float psi;
float bar;
int loopCount = 60*15; //every 15 minutes, post to brewfather
int readingCount = 0;
String brewfatherId = "";

#include "pressure.h"
#include "screen.h"
#include "brewfather.h"
#include "filesystem.h"
#include "wifiConfig.h"

void setup(){
  Serial.begin(115200);
  fsSetup();
  screenSetup();
  printSplashScreen();
  setupPressure();
  wifiSetup();
}

void loop(){
  getPressure();

  if (readingCount >= loopCount) {
    log_brewfather();
    readingCount = 0;
  }
  readingCount = readingCount + 1;
  printToScreen();
} 
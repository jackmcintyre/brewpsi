#include <Arduino.h>
#include "SoftwareSerial.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#include "main.h"
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
  getPressure(); //make this return pressure in PSI
  float psi = 5.5;
  
  //if count = 15 logic goes here

  //postToBrewfather(psi,time); //return success/fail
  
  printToScreen(psi);
} 
  
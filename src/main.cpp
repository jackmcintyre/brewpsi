#include <Arduino.h>
// #include <Wire.h>
#include "SoftwareSerial.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager



#include "main.h"
#include "pressure.h"
#include "screen.h"




void setup(){
  Serial.begin(115200);
  screenSetup();
  
  float psi = 5.5;
  printToScreen(psi);


  // move wifi stuff to own file

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
  //postToBrewfather(psi,time); //return result
  float psi = 5.5;
  printToScreen(psi);
} 
  
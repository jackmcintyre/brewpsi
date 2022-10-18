#include <Arduino.h>
// #include <Wire.h>
#include "SoftwareSerial.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

#include "main.h"
#include "pressure.h"

//move screen stuff to it's own file

#define TFT_CS 14  //for D32 Pro
#define TFT_DC 27  //for D32 Pro
#define TFT_RST 33 //for D32 Pro
#define TS_CS  12 //for D32 Pro

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

unsigned long printToScreen()
{
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(ILI9341_GREEN);
  tft.println(" ");
  tft.println("BrewPSI");
  tft.println(" ");
  tft.println(" ");
  tft.setFont(&FreeSans24pt7b);
  tft.setTextColor(ILI9341_WHITE  );
  tft.println("7.1 PSI");
  tft.println(" ");
  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(ILI9341_RED);
  tft.println(WiFi.localIP());
  return micros() - start;
}

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(1);


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

void loop() {
  getPressure(); //make this return pressure in PSI
  //postToBrewfather(psi,time); //return result
  printToScreen(/*psi*/);
} 
  
#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

#include <WiFiManager.h>

extern float psi;
extern float bar;

#define TFT_CS 14  //for D32 Pro
#define TFT_DC 27  //for D32 Pro
#define TFT_RST 33 //for D32 Pro
#define TS_CS  12 //for D32 Pro

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


// Full init of screen each time we use it seems wrong.

void screenSetup(){
    tft.begin();
}

unsigned long printToScreen(){
    //Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    //tft.begin();
    tft.setRotation(1);
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
    tft.println(String(psi,1) + " PSI");
    tft.println(String(bar,1) + " BAR");
    tft.setTextColor(ILI9341_RED);
    tft.setFont(&FreeSans12pt7b);
    tft.println(WiFi.localIP());
    return micros() - start;
}

unsigned long printSplashScreen(){
    //Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setFont(&FreeSans12pt7b);
    tft.println(" ");
    tft.println("BrewPSI is starting.");
    tft.println("Waiting for reading...");
    return micros() - start;
}
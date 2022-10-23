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

//#include "main.h"
#include "pressure.h"
#include "screen.h"
#include "brewfather.h"
#include "filesystem.h"

WiFiManager wm;
WiFiManagerParameter custom_field;



String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback(){
  Serial.println("[CALLBACK] saveParamCallback fired");
  Serial.println("PARAM brewfather_id = " + getParam("brewfather_id"));

  String str = getParam("brewfather_id");
  int str_len = str.length() + 1;
  char char_array[str_len];
  str.toCharArray(char_array, str_len);
  writeFile(LittleFS, "/brewfatherId.txt",char_array);
}

void setup(){
  Serial.begin(115200);

  fsSetup();
  screenSetup();
  printSplashScreen();

  // move wifi stuff to own file?

  //wm.resetSettings();

  int customFieldLength = 40;

  new (&custom_field) WiFiManagerParameter("brewfather_id", "Brewfather Stream ID", "Brewfather Stream ID", customFieldLength,"placeholder=\"Brewfather Stream ID\" type=\"input\""); // custom html type
  wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);

  bool res;
  res = wm.autoConnect("brewPSI","brewpsi1");

  if(!res) {
    Serial.println("Failed to connect");
  } 
  else {
    Serial.println("Wifi Connected!");
  }

  brewfatherId = readFile(LittleFS, "/brewfatherId.txt");
  Serial.println("brewfatherId: " + String(brewfatherId));

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
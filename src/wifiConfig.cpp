#include <Arduino.h>
#include <WiFiManager.h>
#include <LittleFS.h>
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

void wifiSetup(){
  //wm.resetSettings();

  int customFieldLength = 40;

  new (&custom_field) WiFiManagerParameter("brewfather_id", "Brewfather Stream ID", "Be8AuvedkrpwLZ", customFieldLength,"placeholder=\"Brewfather Stream ID\" type=\"input\""); // custom html type
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
}
#include <Arduino.h>
#include <HTTPClient.h>
#include <LittleFS.h>

#include "filesystem.h"

extern float psi;

void log_brewfather()
{
    String brewfatherId = readFile(LittleFS, "/brewfatherId.txt");
    const char* endpoint = "http://log.brewfather.net/stream?id=";
    String URL = endpoint + brewfatherId;
    const char *url = URL.c_str();

    String httpRequestData = "{\"name\":\"BrewPSI\",\"pressure\":" + String(psi) + ",\"pressure_unit\":\"PSI\"}";

    HTTPClient http;
    http.begin(url);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(httpRequestData);
    http.end();

    //make this return status?
}

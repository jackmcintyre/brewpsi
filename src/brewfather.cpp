#include <Arduino.h>
#include <HTTPClient.h>

extern float psi;

void log_brewfather()
{
    //TODO make the id a variable configurable with wifi settings
    const char* serverName = "http://log.brewfather.net/stream?id=Be8AuvedkrpwLZ";
    String httpRequestData = "{\"name\":\"BrewPSI\",\"pressure\":" + String(psi) + ",\"pressure_unit\":\"PSI\"}";

    HTTPClient http;
    http.begin(serverName);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(httpRequestData);
    http.end();

    //make this return status?
}

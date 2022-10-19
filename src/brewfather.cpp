#include <Arduino.h>
#include <HTTPClient.h>

void log_brewfather(float reading)
{
    //TODO make the id a variable configurable with wifi settings
    const char* serverName = "http://log.brewfather.net/stream?id=Be8AuvedkrpwLZ";

    String httpRequestData = "{\"name\":\"BrewPSI\",\"pressure\":" + String(reading) + ",\"pressure_unit\":\"PSI\"}";

    HTTPClient http;
    http.begin(serverName);

    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(httpRequestData);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();

    Serial.print(httpRequestData);
    Serial.print("\n");

    //make this return status
}

#include <Arduino.h>
#include <HTTPClient.h>

void log_brewfather(float reading)
{

    const char* serverName = "http://log.brewfather.net/stream?id=Be8AuvedkrpwLZ";

    // POST /stream?id=Be8AuvedkrpwLZ HTTP/1.1
    // Host: log.brewfather.net
    // Content-Type: application/json
    // Content-Length: 80

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
}

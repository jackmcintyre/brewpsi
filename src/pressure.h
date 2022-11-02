#include <Arduino.h>

void getPressure();
float convertToPSI();
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
void setupPressure();
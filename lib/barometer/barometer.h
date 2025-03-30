#ifndef BAROMETER_H
#define BAROMETER_H

#include <Wire.h>
#include <Adafruit_BME280.h>

extern float altitude;

void initializeBarometer();

void readAltitude();

void readTemperature(float* temperature);

void offsetBarometer();

void readPressure(float* pressure);

void readHumidity(float* humidity);

#endif
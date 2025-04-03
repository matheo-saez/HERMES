#ifndef BAROMETER_H
#define BAROMETER_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

extern float altitude;

void initializeBarometer();

void offsetBarometer();

void readBme(float* temperature, float* pressure, float* humidity, float* altitude45);

#endif
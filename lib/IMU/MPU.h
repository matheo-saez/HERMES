#ifndef MPU_H
#define MPU_H

#include <Arduino.h>
#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"
#include <Wire.h>
#include <../../include/Config.h>

void initializeMPU();

void calibrateMPU();

void readMPU(float* correctedAccel, float* correctedGyro, float* temperature);

#endif
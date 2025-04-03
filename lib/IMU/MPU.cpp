#include "MPU.h"

Adafruit_MPU6050 mpu;

float accelOffsetX = 0, accelOffsetY = 0, accelOffsetZ = 0;
float gyroOffsetX = 0, gyroOffsetY = 0, gyroOffsetZ = 0;

void initializeMPU() {
    Serial.println(F("Initialize System"));
    if (!mpu.begin(0x69)) { // Change address if needed
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void calibrateMPU() {
    sensors_event_t a, g, temp;

    // Initialiser les offsets à 0
    accelOffsetX = accelOffsetY = accelOffsetZ = 0;
    gyroOffsetX = gyroOffsetY = gyroOffsetZ = 0;

    // Lire plusieurs échantillons pour calculer les offsets
    const int numSamples = 100;
    for (int i = 0; i < numSamples; i++) {
        mpu.getEvent(&a, &g, &temp);

        accelOffsetX += a.acceleration.x;
        accelOffsetY += a.acceleration.y;
        accelOffsetZ += a.acceleration.z;

        gyroOffsetX += g.gyro.x;
        gyroOffsetY += g.gyro.y;
        gyroOffsetZ += g.gyro.z;

        delay(10); // Petite pause entre les lectures
    }

    // Calculer la moyenne des offsets
    accelOffsetX /= numSamples;
    accelOffsetY /= numSamples;
    accelOffsetZ /= numSamples;
    gyroOffsetX /= numSamples;
    gyroOffsetY /= numSamples;
    gyroOffsetZ /= numSamples;

    Serial.println("Calibration done!");
    Serial.print("Accel Offsets: X=");
    Serial.print(accelOffsetX);
    Serial.print(", Y=");
    Serial.print(accelOffsetY);
    Serial.print(", Z=");
    Serial.println(accelOffsetZ);

    Serial.print("Gyro Offsets: X=");
    Serial.print(gyroOffsetX);
    Serial.print(", Y=");
    Serial.print(gyroOffsetY);
    Serial.print(", Z=");
    Serial.println(gyroOffsetZ);
}

void readMPU(float* correctedAccel, float* correctedGyro, float* temperature) {
    // Nouvelle méthode pour lire les données avec votre librairie privée
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Appliquer les offsets pour corriger les valeurs
    correctedAccel[0] = a.acceleration.x - accelOffsetX;
    correctedAccel[1] = a.acceleration.y - accelOffsetY;
    correctedAccel[2] = a.acceleration.z - accelOffsetZ;

    correctedGyro[0] = g.gyro.x - gyroOffsetX;
    correctedGyro[1] = g.gyro.y - gyroOffsetY;
    correctedGyro[2] = g.gyro.z - gyroOffsetZ;

    *temperature = temp.temperature;
}
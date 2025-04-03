#include <Arduino.h>
#include "barometer.h"
#include "buzzer.h"
#include "Led.h"
#include "MPU.h"

// Variables pour stocker les données du BME280
float temperature_bme;
float pressure;
float humidity;
float altitude;

// Variables pour stocker les données du MPU6050
float correctedAccel[3];
float correctedGyro[3];
float temperature_mpu;

void setup() {
    Serial.begin(9600);

   
    
    Serial.println("BME280 test :");
    // Initialisation des capteurs
    initializeBarometer();
    offsetBarometer();

    readBme(&temperature_bme, &pressure, &humidity, &altitude);
    // Affichage des données des capteurs (facultatif)
    Serial.print("Température : ");
    Serial.println(temperature_bme);
    Serial.print("Pression : ");
    Serial.println(pressure);
    Serial.print("Humidité : ");
    Serial.println(humidity);
    Serial.print("Altitude : ");
    Serial.println(altitude);

    delay(1000); // Pause pour éviter de saturer le port série

    Serial.println("IMU test :");
    // Initialisation des capteurs
    initializeMPU();
    calibrateMPU();
    
    readMPU(correctedAccel, correctedGyro, &temperature_mpu);
    // Affichage des données des capteurs (facultatif)
    Serial.print("Acceleration: X=");
    Serial.print(correctedAccel[0]);
    Serial.print(", Y=");
    Serial.print(correctedAccel[1]);
    Serial.print(", Z=");
    Serial.println(correctedAccel[2]);

    Serial.print("Gyro: X=");
    Serial.print(correctedGyro[0]);
    Serial.print(", Y=");
    Serial.print(correctedGyro[1]);
    Serial.print(", Z=");
    Serial.println(correctedGyro[2]);

    Serial.print("Temperature: ");
    Serial.print(temperature_mpu);
    Serial.println("°C");

    delay(1000); // Pause pour éviter de saturer le port série

    Serial.println("Buzzer Test");
    initializeBuzzer();
    biiip(3, 200); // 3 bips de 200 ms

    delay(1000); // Pause pour éviter de saturer le port série

    Serial.println("LED Test");
    initializeLed();
    led(1, 0, 0);
    delay(500);
    led(0, 1, 0);
    delay(500);
    led(0, 0, 1);
    delay(500);
}

void loop() {
    //Rien ici pour l'instant
}
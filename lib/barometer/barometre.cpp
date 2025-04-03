#include "barometer.h"
#define SEALEVELPRESSURE_HPA (1013.25)

float altitude_offset = 0;

Adafruit_BME280 bme; // I2C

unsigned long delayTime;

void initializeBarometer() {
    Serial.println("BME280 test");

    // Initialisation du capteur BME280
    if (!bme.begin(0x76)) { // Assurez-vous que l'adresse I2C est correcte (0x76 ou 0x77)
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10); // Boucle infinie si le capteur n'est pas détecté
    }
}

void offsetBarometer() {
    altitude_offset = 0;
    for (int i = 0; i < 40; i++) {
        altitude_offset += bme.readAltitude(SEALEVELPRESSURE_HPA);
        delay(50);
    }
    altitude_offset /= 40;
    Serial.print("Altitude offset done : ");
    Serial.println(altitude_offset);
}

void readBme(float* temperature, float* pressure, float* humidity, float* altitude45) {
    *temperature = bme.readTemperature();
    *pressure = bme.readPressure() / 100.0F;
    *humidity = bme.readHumidity();
    *altitude45 = bme.readAltitude(SEALEVELPRESSURE_HPA) - altitude_offset;
}
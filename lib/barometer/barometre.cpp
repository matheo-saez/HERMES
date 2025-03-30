#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

float altitude = 0;
float altitude_offset = 0;

Adafruit_BME280 bme; // I2C



unsigned long delayTime;

void initializeBarometer() {
    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin();  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
}

void readAltitude() {
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA) - altitude_offset;
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

void readTemperature(float* temperature) {
    *temperature = bme.readTemperature();
}

void readPressure(float* pressure) {
    *pressure = bme.readPressure() / 100.0F;
}

void readHumidity(float* humidity) {
    *humidity = bme.readHumidity();
}
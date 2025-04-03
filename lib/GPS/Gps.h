#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include "Pins.h"

class Gps {
public:
    Gps(unsigned long baudRate = 9600);
    void begin();
    void update();
    void printData();

    // Getters for GPS data
    int getSatellites();
    double getLatitude();
    double getLongitude();
    double getAltitude();
    double getSpeed();
    String getDate();
    String getTime();

private:
    uint8_t rxPin;
    uint8_t txPin;
    unsigned long baudRate;
    SoftwareSerial gpsSerial;
    TinyGPSPlus gps;
};

#endif // GPS_H
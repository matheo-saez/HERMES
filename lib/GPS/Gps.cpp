#include "Gps.h"

Gps::Gps(unsigned long baudRate)
    : baudRate(baudRate), gpsSerial(RX_L80, TX_L80) {}

TinyGPSPlus gps; // Create a TinyGPSPlus object

void Gps::begin() {
    Serial.begin(9600); // Connect to the serial monitor
    gpsSerial.begin(baudRate); // Initialize GPS communication
}

void Gps::update() {
    while (gpsSerial.available()) {
        gps.encode(gpsSerial.read());
    }
}

void Gps::printData() {
    Serial.print("SATS: ");
    Serial.println(getSatellites());
    Serial.print("LAT: ");
    Serial.println(getLatitude(), 6);
    Serial.print("LONG: ");
    Serial.println(getLongitude(), 6);
    Serial.print("ALT: ");
    Serial.println(getAltitude());
    Serial.print("SPEED: ");
    Serial.println(getSpeed());
    Serial.print("Date: ");
    Serial.println(getDate());
    Serial.print("Hour: ");
    Serial.println(getTime());
    Serial.println("---------------------------");
}

int Gps::getSatellites() {
    return gps.satellites.value();
}

double Gps::getLatitude() {
    return gps.location.lat();
}

double Gps::getLongitude() {
    return gps.location.lng();
}

double Gps::getAltitude() {
    return gps.altitude.meters();
}

double Gps::getSpeed() {
    return gps.speed.mps();
}

String Gps::getDate() {
    return String(gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year());
}

String Gps::getTime() {
    return String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second());
}
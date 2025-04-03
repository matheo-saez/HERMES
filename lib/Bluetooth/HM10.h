#ifndef HM10_H
#define HM10_H

#include <Arduino.h>

class HM10 {
public:
    HM10(HardwareSerial &serial);
    void begin(unsigned long baudRate);
    void setCallback(void (*callback)(const String &message));
    void handleInterrupt();
    void send(const String & message);

private:
    HardwareSerial &hm10Serial;
    void (*messageCallback)(const String &message) = nullptr;
    String buffer;
};

#endif
#ifndef LORA_H
#define LORA_H

#include <Arduino.h>
#include "LoRa_E220.h"
#include "Pins.h"

class Lora {
public:
    Lora();
    void begin();
    void setCallback(void (*callback)(const String &message));
    void handleInterrupt();
    void sendMessage(const String &message);
    void printParameters();

private:
    LoRa_E220 e220ttl;
    void (*messageCallback)(const String &message) = nullptr;
};

#endif // LORA_H
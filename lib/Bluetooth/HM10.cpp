#include <Arduino.h>
#include "HM10.h"

HM10::HM10(HardwareSerial &serial) : hm10Serial(serial) {}

void HM10::begin(unsigned long baudRate) {
    hm10Serial.begin(baudRate);
}

void HM10::setCallback(void (*callback)(const String &message)) {
    messageCallback = callback;
}

void HM10::handleInterrupt() {
    while (hm10Serial.available()) {
        char c = hm10Serial.read();
        if (c == '\n') { // Fin de message
            if (messageCallback) {
                messageCallback(buffer);
            }
            buffer = ""; // Réinitialiser le buffer
        } else {
            buffer += c; // Ajouter le caractère au buffer
        }
    }
}

void HM10::send(const String &message) {
    hm10Serial.println(message); // Envoie le message suivi d'un retour à la ligne
}
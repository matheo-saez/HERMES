#include <Arduino.h>
#include "Pyro.h"

void initializePyro() {
    pinMode(PYRO_1, OUTPUT);
    pinMode(PYRO_2, OUTPUT);
    pinMode(PYRO_3, OUTPUT);
    pinMode(PYRO_4, OUTPUT);
    digitalWrite(PYRO_1, LOW);
    digitalWrite(PYRO_2, LOW);
    digitalWrite(PYRO_3, LOW);
    digitalWrite(PYRO_4, LOW);
    Serial.println("Pyro initialized.");
}

void pyro(int pyro_num, int state) {
    if (pyro_num < 1 || pyro_num > 4) {
        Serial.println("Invalid pyro number. Must be between 1 and 4.");
        return;
    }
    int pin = PYRO_1 + (pyro_num - 1);
    if (state == HIGH) {
        digitalWrite(pin, HIGH);
        Serial.print("Pyro ");
        Serial.print(pyro_num);
        Serial.println(" fired!");
        delay(50); // Wait for 50ms to allow the pyro to fire
        digitalWrite(pin, LOW); // Turn off the pyro after firing
        state = LOW; // Reset state to LOW after firing
    } else if (state == LOW) {
        digitalWrite(pin, LOW);
        Serial.print("Pyro ");
        Serial.print(pyro_num);
        Serial.println(" disabled.");
    } else {
        Serial.println("Invalid state. Use HIGH to fire or LOW to disable.");
    }
}
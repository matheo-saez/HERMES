#include <Arduino.h>
#include "Buzzer.h"

void initializeBuzzer() {
    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);

    // Startup music
    int startupMelody[] = {200, 400, 600}; // Frequencies in Hz
    int duration = 200; // Duration of each tone in milliseconds

    for (int i = 0; i < 3; i++) {
        tone(BUZZER, startupMelody[i], duration); // Play tone
        delay(duration + 50); // Wait for the tone to finish
    }
    noTone(BUZZER); // Stop the tone
}

void biiip(int nb, int d) {
    for (int i = 1; i <= nb; i++) {
        tone(BUZZER, 1000, d); // Génère un son à 1000 Hz pendant 'd' millisecondes
        delay(d + 50);         // Attendre que le bip se termine + une pause
    }
    noTone(BUZZER); // Arrête le signal après les bips
}
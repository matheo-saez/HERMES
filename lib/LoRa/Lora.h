#ifndef LORA_H
#define LORA_H

#include "LoRa_E220.h"
#include "Pins.h"

// Initialisation du module LoRa
void setupLora();

// Définir un callback pour les messages reçus
void setLoraCallback(void (*callback)(const String &message));

// Gestion des interruptions pour les messages LoRa
void handleLoraInterrupt();

// Afficher les paramètres du module
void printParameters(struct Configuration configuration);

#endif
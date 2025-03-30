#include <Arduino.h>
#include "Lora.h"

#define DESTINATION_ADDL 2
#define ENABLE_RSSI true

LoRa_E220 e220ttl(TX_E220_900T22D, RX_E220_900T22D, AUX, M0, M1);

// Callback pour gérer les messages reçus
void (*messageCallback)(const String &message) = nullptr;

void setupLora() {
    // Initialisation des broches et de l'UART
    e220ttl.begin();

    // Lecture de la configuration (sans impression)
    ResponseStructContainer c = e220ttl.getConfiguration();
    Configuration configuration = *(Configuration *)c.data;
    c.close(); // Libérer la mémoire allouée dynamiquement

    // Le module LoRa est maintenant prêt
}

void setLoraCallback(void (*callback)(const String &message)) {
    messageCallback = callback;
}

void handleLoraInterrupt() {
    // Vérifier si des données sont disponibles
    if (e220ttl.available() > 1) {
#ifdef ENABLE_RSSI
        ResponseContainer rc = e220ttl.receiveMessageRSSI();
#else
        ResponseContainer rc = e220ttl.receiveMessage();
#endif
        if (rc.status.code != 1) {
            // Gestion des erreurs (facultatif)
        } else {
            String receivedMessage = rc.data;

            // Appeler le callback si défini
            if (messageCallback) {
                messageCallback(receivedMessage);
            }
        }
    }
}
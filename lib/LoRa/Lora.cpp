#include "Lora.h"

Lora::Lora()
    : e220ttl(TX_E220_900T22D, RX_E220_900T22D, AUX, M0, M1) {}

void Lora::begin() {
    // Initialisation des broches et de l'UART
    e220ttl.begin();

    delay(1000); // Attendre 1 seconde pour la stabilisation

    if (!e220ttl.begin()) {
        Serial.println("Erreur : Impossible d'initialiser le module LoRa !");
    }

    // Lecture de la configuration (sans impression)
    ResponseStructContainer c = e220ttl.getConfiguration();
    Configuration configuration = *(Configuration *)c.data;
    c.close(); // Libérer la mémoire allouée dynamiquement

    Serial.println("Le module LoRa est maintenant prêt.");
}

void Lora::setCallback(void (*callback)(const String &message)) {
    messageCallback = callback;
}

void Lora::handleInterrupt() {
    // Vérifier si des données sont disponibles
    if (e220ttl.available() > 1) {
#ifdef ENABLE_RSSI
        ResponseContainer rc = e220ttl.receiveMessageRSSI();
#else
        ResponseContainer rc = e220ttl.receiveMessage();
#endif
        if (rc.status.code != 1) {
            Serial.println("Erreur lors de la réception du message.");
        } else {
            String receivedMessage = rc.data;

            // Appeler le callback si défini
            if (messageCallback) {
                messageCallback(receivedMessage);
            }
        }
    }
}

void Lora::sendMessage(const String &message) {
    ResponseStatus rs = e220ttl.sendMessage(message);

    if (rs.code != 1) {
        Serial.print("Erreur lors de l'envoi du message : ");
        Serial.println(rs.getResponseDescription());
    } else {
        Serial.println("Message envoyé avec succès !");
    }
}

void Lora::printParameters() {
    ResponseStructContainer c = e220ttl.getConfiguration();
    Configuration configuration = *(Configuration *)c.data;

    Serial.println("Configuration actuelle du module LoRa :");
    Serial.print("Adresse : ");
    Serial.println(configuration.ADDH, HEX);
    Serial.print("Vitesse UART : ");
    Serial.println(configuration.SPED.uartBaudRate);
    // Ajoutez d'autres paramètres si nécessaire

    c.close(); // Libérer la mémoire allouée dynamiquement
}
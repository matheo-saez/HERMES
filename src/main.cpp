#include <Arduino.h>
#include "HM10.h"
#include "Lora.h"
#include "barometer.h"
#include "MPU.h"

// Initialisation des objets
HM10 hm10(Serial1);

// Variables pour stocker les données des capteurs
float temperature, pressure, humidity, altitude;
Quaternion q;
float ypr[3];

// Callback pour les messages Bluetooth
void onBluetoothMessageReceived(const String &message) {
    if (message == "COMMAND1") {
        Serial.println("Commande 1 reçue via Bluetooth !");
    } else if (message == "COMMAND2") {
        Serial.println("Commande 2 reçue via Bluetooth !");
    }
}

// Callback pour les messages LoRa
void onLoraMessageReceived(const String &message) {
    if (message == "COMMAND1") {
        Serial.println("Commande 1 reçue via LoRa !");
    } else if (message == "COMMAND2") {
        Serial.println("Commande 2 reçue via LoRa !");
    }
}

void setup() {
    Serial.begin(9600);

    // Initialisation des modules Bluetooth et LoRa
    hm10.begin(9600);
    hm10.setCallback(onBluetoothMessageReceived);
    setupLora();
    setLoraCallback(onLoraMessageReceived);

    // Configurer les interruptions pour HM-10 et LoRa
    attachInterrupt(digitalPinToInterrupt(19), []() { hm10.handleInterrupt(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(AUX), []() {
        // Vérifier explicitement si des données LoRa sont disponibles
        handleLoraInterrupt();
    }, CHANGE);

    // Initialisation des capteurs
    initializeBarometer();
    offsetBarometer(); // Calibrer l'altitude
    initializeMPU();
}

void loop() {
    // Lecture des données des capteurs
    readTemperature(&temperature);
    readPressure(&pressure);
    readHumidity(&humidity);
    readAltitude();

    // Affichage des données des capteurs (facultatif)
    Serial.print("Température : ");
    Serial.println(temperature);
    Serial.print("Pression : ");
    Serial.println(pressure);
    Serial.print("Humidité : ");
    Serial.println(humidity);
    Serial.print("Altitude : ");
    Serial.println(altitude);

    // Lecture des données de l'IMU
    readMPU(&q, ypr);
    Serial.print("Yaw : ");
    Serial.println(ypr[0]);
    Serial.print("Pitch : ");
    Serial.println(ypr[1]);
    Serial.print("Roll : ");
    Serial.println(ypr[2]);

    delay(100); // Pause pour éviter de saturer le port série
}
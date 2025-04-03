#include <Arduino.h>
#include "HM10.h"
#include "Lora.h"
#include "barometer.h"
#include "buzzer.h"
#include "Led.h"
#include "MPU.h"
#include "Pyro.h"
#include "Gps.h"

// Initialisation des objets
HM10 hm10(Serial1);
Lora lora; // Utilisation de la classe Lora
Gps gps(9600); // Initialisation du GPS avec un débit en bauds de 9600

// Variables pour stocker les données du BME280
float temperature_bme;
float pressure;
float humidity;
float altitude;

// Variables pour stocker les données du MPU6050
float correctedAccel[3];
float correctedGyro[3];
float temperature_mpu;

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
    lora.begin(); // Initialiser le module LoRa
    lora.setCallback(onLoraMessageReceived);

    // Configurer les interruptions pour HM-10 et LoRa
    attachInterrupt(digitalPinToInterrupt(19), []() { hm10.handleInterrupt(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(AUX), []() { lora.handleInterrupt(); }, CHANGE);

    // Initialisation des capteurs
    initializeBarometer();
    offsetBarometer();

    Serial.println("BME280 test :");
    readBme(&temperature_bme, &pressure, &humidity, &altitude);
    // Affichage des données des capteurs (facultatif)
    Serial.print("Température : ");
    Serial.println(temperature_bme);
    Serial.print("Pression : ");
    Serial.println(pressure);
    Serial.print("Humidité : ");
    Serial.println(humidity);
    Serial.print("Altitude : ");
    Serial.println(altitude);

    delay(1000); // Pause pour éviter de saturer le port série

    readMPU(correctedAccel, correctedGyro, &temperature_mpu);
    // Affichage des données des capteurs (facultatif)
    Serial.print("Acceleration: X=");
    Serial.print(correctedAccel[0]);
    Serial.print(", Y=");
    Serial.print(correctedAccel[1]);
    Serial.print(", Z=");
    Serial.println(correctedAccel[2]);

    Serial.print("Gyro: X=");
    Serial.print(correctedGyro[0]);
    Serial.print(", Y=");
    Serial.print(correctedGyro[1]);
    Serial.print(", Z=");
    Serial.println(correctedGyro[2]);

    Serial.print("Temperature: ");
    Serial.print(temperature_mpu);
    Serial.println("°C");

    delay(1000); // Pause pour éviter de saturer le port série

    Serial.println("GPS test :");
    gps.begin(); // Initialiser le GPS
    delay(1000); // Pause pour laisser le GPS se stabiliser

    Serial.println("Buzzer Test");
    initializeBuzzer();
    biiip(3, 200); // 3 bips de 200 ms

    delay(1000); // Pause pour éviter de saturer le port série

    Serial.println("LED Test");
    initializeLed();
    led(1, 0, 0);
    delay(500);
    led(0, 1, 0);
    delay(500);
    led(0, 0, 1);
    delay(500);

    delay(1000); // Pause pour éviter de saturer le port série

    Serial.println("LoRa Test");
    lora.sendMessage("Hello from HERMES/LoRa !");

    delay(1000); // Pause pour éviter de saturer le port série

    Serial.println("Bluetooth Test");
    hm10.send("Hello from HERMES/Bluetooth !");

    delay(1000); // Pause pour éviter de saturer le port série

    Serial.println("Pyro Test");
    initializePyro();
    pyro(1); // Tirer le pyro 1
    delay(1000); // Attendre 1 seconde
    pyro(2); // Tirer le pyro 2
    delay(1000); // Attendre 1 seconde
    pyro(3); // Tirer le pyro 3
    delay(1000); // Attendre 1 seconde
    pyro(4); // Tirer le pyro 4

    delay(1000); // Attendre 1 seconde

    Serial.println("GPS Test");
    gps.update();
    Serial.println("GPS Data:");
    Serial.print("Satellites: ");
    Serial.println(gps.getSatellites());
    Serial.print("Latitude: ");
    Serial.println(gps.getLatitude(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.getLongitude(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.getAltitude());
    Serial.print("Speed: ");
    Serial.println(gps.getSpeed());
    Serial.print("Date: ");
    Serial.println(gps.getDate());
    Serial.print("Time: ");
    Serial.println(gps.getTime());
}

void loop() {
    //Rien ici pour l'instant
}
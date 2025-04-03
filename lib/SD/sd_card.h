#ifndef SDCARD_H
#define SDCARD_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "Pins.h" // Inclusion du fichier Pins.h pour accéder à SD_CS

class SDCard {
public:
    SDCard(); // Constructeur sans paramètre
    bool begin();          // Initialisation de la carte SD
    bool writeFile(const String &filename, const String &data); // Écrire dans un fichier
    String readFile(const String &filename);                   // Lire un fichier
    bool deleteFile(const String &filename);                   // Supprimer un fichier
    bool fileExists(const String &filename);                   // Vérifier si un fichier existe

private:
    const uint8_t csPin = SD_CS; // Utilisation de SD_CS défini dans Pins.h
};

#endif
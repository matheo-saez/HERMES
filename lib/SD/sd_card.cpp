#include "sd_card.h"

SDCard::SDCard() {}

bool SDCard::begin() {
    if (!SD.begin(csPin)) {
        Serial.println("Erreur : Impossible d'initialiser la carte SD !");
        return false;
    }
    Serial.println("Carte SD initialisée avec succès !");
    return true;
}

bool SDCard::writeFile(const String &filename, const String &data) {
    File file = SD.open(filename, FILE_WRITE);
    if (!file) {
        Serial.println("Erreur : Impossible d'ouvrir le fichier pour écriture !");
        return false;
    }
    file.println(data);
    file.close();
    Serial.println("Données écrites avec succès dans le fichier : " + filename);
    return true;
}

String SDCard::readFile(const String &filename) {
    File file = SD.open(filename, FILE_READ);
    if (!file) {
        Serial.println("Erreur : Impossible d'ouvrir le fichier pour lecture !");
        return "";
    }
    String data = "";
    while (file.available()) {
        data += (char)file.read();
    }
    file.close();
    Serial.println("Données lues avec succès depuis le fichier : " + filename);
    return data;
}

bool SDCard::deleteFile(const String &filename) {
    if (!SD.exists(filename)) {
        Serial.println("Erreur : Le fichier n'existe pas !");
        return false;
    }
    if (SD.remove(filename)) {
        Serial.println("Fichier supprimé avec succès : " + filename);
        return true;
    } else {
        Serial.println("Erreur : Impossible de supprimer le fichier !");
        return false;
    }
}

bool SDCard::fileExists(const String &filename) {
    return SD.exists(filename);
}
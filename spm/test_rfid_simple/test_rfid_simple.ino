// =====================================================
//  TEST SIMPLE RFID - sans LCD, sans Qt
//  Ouvre le Moniteur Série à 9600 bauds
//  Scanne une carte → l'UID s'affiche dans le moniteur
// =====================================================

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN   10
#define RST_PIN   9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    Serial.println("============================");
    Serial.println("  TEST RFID pret");
    Serial.println("  Scanne une carte...");
    Serial.println("============================");
}

void loop() {
    if (!rfid.PICC_IsNewCardPresent()) return;
    if (!rfid.PICC_ReadCardSerial())   return;

    Serial.print("UID detecte : ");
    for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) Serial.print("0");
        Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();
    Serial.println("----------------------------");

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}

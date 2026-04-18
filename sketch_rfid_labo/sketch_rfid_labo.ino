// =============================================================================
//  SKETCH ARDUINO - Scénario RFID + LCD stylé
//  Projet C++ Esprit - Atelier 4 Arduino
//
//  Brochage :
//    RFID-RC522 : SDA=10, SCK=13, MOSI=11, MISO=12, RST=9, VCC=3.3V, GND=GND
//    LCD I2C    : SDA=A4, SCL=A5, VCC=5V, GND=GND
// =============================================================================

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN   10
#define RST_PIN   9
#define ID_LABO   2

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ── Caractères personnalisés ──────────────────────────────────────────────────
byte CHECK[8]  = {0b00000,0b00000,0b00001,0b00011,0b10110,0b11100,0b01000,0b00000};
byte CROSS[8]  = {0b00000,0b10001,0b01010,0b00100,0b01010,0b10001,0b00000,0b00000};
byte LOCK[8]   = {0b01110,0b10001,0b10001,0b11111,0b11011,0b11011,0b11111,0b00000};
byte ARROW[8]  = {0b00100,0b00110,0b11111,0b11111,0b11111,0b00110,0b00100,0b00000};
byte BLOCK[8]  = {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
byte HALF[8]   = {0b11111,0b11111,0b11111,0b00000,0b00000,0b00000,0b00000,0b00000};

#define CHAR_CHECK  0
#define CHAR_CROSS  1
#define CHAR_LOCK   2
#define CHAR_ARROW  3
#define CHAR_BLOCK  4
#define CHAR_HALF   5

// ─────────────────────────────────────────────────────────────────────────────
void setup()
{
    Serial.begin(9600);

    // RFID en premier
    SPI.begin();
    rfid.PCD_Init();
    delay(50);
    rfid.PCD_SetAntennaGain(rfid.RxGain_max);

    // LCD
    Wire.begin();
    delay(50);
    lcd.init();
    lcd.init();
    lcd.backlight();

    // Charger les caractères personnalisés
    lcd.createChar(CHAR_CHECK, CHECK);
    lcd.createChar(CHAR_CROSS, CROSS);
    lcd.createChar(CHAR_LOCK,  LOCK);
    lcd.createChar(CHAR_ARROW, ARROW);
    lcd.createChar(CHAR_BLOCK, BLOCK);
    lcd.createChar(CHAR_HALF,  HALF);

    animationDemarrage();
    afficherAttente();
}

// ── Animation de démarrage ────────────────────────────────────────────────────
void animationDemarrage()
{
    lcd.clear();
    // Barre de chargement
    lcd.setCursor(0, 0);
    lcd.print("  POINTAGE SYSTEM");
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
        lcd.write(CHAR_BLOCK);
        delay(60);
    }
    delay(400);

    // Flash rétroéclairage
    for (int i = 0; i < 2; i++) {
        lcd.noBacklight(); delay(120);
        lcd.backlight();   delay(120);
    }
    delay(300);
}

// ── Écran d'attente ────────────────────────────────────────────────────────────
void afficherAttente()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write(CHAR_LOCK);
    lcd.print(" RFID SYSTEM  ");
    lcd.write(CHAR_LOCK);
    lcd.setCursor(0, 1);
    lcd.write(CHAR_ARROW);
    lcd.print(" Scan ta carte");
    lcd.write(CHAR_ARROW);
}

// ── Barre de progression (0–100%) ─────────────────────────────────────────────
void barreProgression(int pct)
{
    int blocs = (pct * 14) / 100;  // 14 colonnes pour la barre
    lcd.setCursor(1, 1);
    lcd.print("[");
    for (int i = 0; i < 14; i++) {
        if (i < blocs)       lcd.write(CHAR_BLOCK);
        else if (i == blocs) lcd.write(CHAR_HALF);
        else                  lcd.print(" ");
    }
    lcd.print("]");
}

// ── Flash rétroéclairage ───────────────────────────────────────────────────────
void flashBacklight(int fois, int duree)
{
    for (int i = 0; i < fois; i++) {
        lcd.noBacklight(); delay(duree);
        lcd.backlight();   delay(duree);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
void loop()
{
    if (!rfid.PICC_IsNewCardPresent()) { delay(50); return; }
    if (!rfid.PICC_ReadCardSerial())   { delay(50); return; }

    // Construire l'UID
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) uid += "0";
        uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();

    // ── Écran "Vérification..." + UID ────────────────────────────────────────
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write(CHAR_LOCK);
    lcd.print(" Verification  ");
    lcd.write(CHAR_LOCK);

    // Envoyer à Qt
    Serial.print("UID:"); Serial.print(uid);
    Serial.print(":"); Serial.println(ID_LABO);

    // Attendre Qt avec barre de progression
    unsigned long debut  = millis();
    unsigned long timeout = 4000;
    while (!Serial.available() && (millis() - debut) < timeout) {
        int pct = ((millis() - debut) * 100) / timeout;
        barreProgression(pct);
        delay(80);
    }
    barreProgression(100);
    delay(100);

    // ── Traiter la réponse ────────────────────────────────────────────────────
    if (Serial.available()) {
        String reponse = Serial.readStringUntil('\n');
        reponse.trim();

        if (reponse.startsWith("1:")) {
            // ── ACCÈS AUTORISÉ ─────────────────────────────────────────────
            int c1    = reponse.indexOf(':', 2);
            String prenom = reponse.substring(2, c1);
            String heure  = reponse.substring(c1 + 1);

            // Flash 2× rapide (feedback positif)
            flashBacklight(2, 80);

            // Ligne 1 : ✓  Bienvenu Prenom
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.write(CHAR_CHECK);
            lcd.print(" Bienvenu ");
            // Tronquer le prénom si trop long (max 5 chars)
            if (prenom.length() > 5) prenom = prenom.substring(0, 5);
            lcd.print(prenom);

            // Ligne 2 : Pointe a HH:MM
            lcd.setCursor(0, 1);
            lcd.write(CHAR_ARROW);
            lcd.print(" Pointe a ");
            lcd.print(heure);

            delay(3500);

        } else {
            // ── ACCÈS REFUSÉ ───────────────────────────────────────────────
            // Flash rapide 3× (feedback négatif)
            flashBacklight(3, 100);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.write(CHAR_CROSS);
            lcd.print(" ACCES REFUSE  ");
            lcd.write(CHAR_CROSS);
            lcd.setCursor(0, 1);
            lcd.print("  Non autorise  ");

            delay(2800);
        }

    } else {
        // ── TIMEOUT Qt ────────────────────────────────────────────────────
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Systeme hors  ");
        lcd.setCursor(0, 1);
        lcd.print("   ligne...     ");
        delay(2000);
    }

    // Retour à l'écran d'attente
    afficherAttente();

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}

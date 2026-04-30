// =============================================================================
<<<<<<< HEAD:SPM/sketch_rfid_labo/sketch_rfid_labo.ino
//  SKETCH ARDUINO - Scénario RFID + LCD stylé
//  Projet C++ Esprit - Atelier 4 Arduino
//
//  Brochage :
//    RFID-RC522 : SDA=10, SCK=13, MOSI=11, MISO=12, RST=9, VCC=3.3V, GND=GND
//    LCD I2C    : SDA=A4, SCL=A5, VCC=5V, GND=GND
=======
//  SKETCH ARDUINO — RFID + LCD 16×2 I2C  — Style Pro
//  Projet Smart Research — Esprit
//
//  Brochage :
//    RFID-RC522 : SDA=10, SCK=13, MOSI=11, MISO=12, RST=9
//    LCD I2C    : SDA=A4, SCL=A5, VCC=5V, GND=GND
//
//  Protocole série Qt → Arduino :
//    "1:Prenom:HH:MM\n"  →  Arrivée accordée
//    "2:Prenom:HH:MM\n"  →  Départ enregistré
//    "3:Prenom\n"        →  Déjà pointé aujourd'hui
//    "0\n"               →  Accès refusé
>>>>>>> 9a10c999ab5f4c212cf0f5bd865d9b0be17c739e:SmartResearchPublicationManagementt/sketch_rfid_labo/sketch_rfid_labo.ino
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

<<<<<<< HEAD:SPM/sketch_rfid_labo/sketch_rfid_labo.ino
// ── Caractères personnalisés ──────────────────────────────────────────────────
byte CHECK[8]  = {0b00000,0b00000,0b00001,0b00011,0b10110,0b11100,0b01000,0b00000};
byte CROSS[8]  = {0b00000,0b10001,0b01010,0b00100,0b01010,0b10001,0b00000,0b00000};
byte LOCK[8]   = {0b01110,0b10001,0b10001,0b11111,0b11011,0b11011,0b11111,0b00000};
byte ARROW[8]  = {0b00100,0b00110,0b11111,0b11111,0b11111,0b00110,0b00100,0b00000};
byte BLOCK[8]  = {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
byte HALF[8]   = {0b11111,0b11111,0b11111,0b00000,0b00000,0b00000,0b00000,0b00000};

=======
// =============================================================================
//  CARACTÈRES PERSONNALISÉS (slots 0-7)
// =============================================================================

// 0 — Coche  ✓
byte CHAR_DEF_CHECK[8] = {
    0b00000,
    0b00001,
    0b00011,
    0b10110,
    0b11100,
    0b01000,
    0b00000,
    0b00000
};

// 1 — Croix  ✗
byte CHAR_DEF_CROSS[8] = {
    0b00000,
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000
};

// 2 — Cadenas  🔒
byte CHAR_DEF_LOCK[8] = {
    0b01110,
    0b10001,
    0b10001,
    0b11111,
    0b11011,
    0b11011,
    0b11111,
    0b00000
};

// 3 — Flèche droite  ►
byte CHAR_DEF_ARROW[8] = {
    0b00100,
    0b00110,
    0b11111,
    0b11111,
    0b11111,
    0b00110,
    0b00100,
    0b00000
};

// 4 — Bloc plein  █  (barre de progression)
byte CHAR_DEF_BLOCK[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

// 5 — Demi-bloc  ▄  (barre de progression, remplissage partiel)
byte CHAR_DEF_HALF[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

// 6 — Silhouette personne  👤
byte CHAR_DEF_PERSON[8] = {
    0b00100,
    0b01110,
    0b01110,
    0b00100,
    0b11111,
    0b00100,
    0b01010,
    0b10001
};

// 7 — Horloge  🕐
byte CHAR_DEF_CLOCK[8] = {
    0b00000,
    0b01110,
    0b10101,
    0b10111,
    0b10001,
    0b01110,
    0b00000,
    0b00000
};

// Indices des slots
>>>>>>> 9a10c999ab5f4c212cf0f5bd865d9b0be17c739e:SmartResearchPublicationManagementt/sketch_rfid_labo/sketch_rfid_labo.ino
#define CHAR_CHECK  0
#define CHAR_CROSS  1
#define CHAR_LOCK   2
#define CHAR_ARROW  3
#define CHAR_BLOCK  4
#define CHAR_HALF   5
<<<<<<< HEAD:SPM/sketch_rfid_labo/sketch_rfid_labo.ino

// ─────────────────────────────────────────────────────────────────────────────
=======
#define CHAR_PERSON 6
#define CHAR_CLOCK  7

// =============================================================================
//  ÉTAT GLOBAL
// =============================================================================
unsigned long g_lastScroll  = 0;   // timer scrolling attente
int           g_scrollPos   = 0;   // position courante du scroll
bool          g_enAttente   = false;

// Message scrollant (padding pour effet circulaire)
const char SCROLL_MSG[] = "  Approchez votre badge...   ";
const int  SCROLL_LEN   = sizeof(SCROLL_MSG) - 1;  // sans \0

// =============================================================================
//  UTILITAIRES
// =============================================================================

void flashBacklight(int fois, int duree_ms)
{
    for (int i = 0; i < fois; i++) {
        lcd.noBacklight(); delay(duree_ms);
        lcd.backlight();   delay(duree_ms);
    }
}

// Affiche une ligne de 16 caractères centrée
void printCentered(int row, const char *text)
{
    int len = strlen(text);
    int pad = (16 - len) / 2;
    lcd.setCursor(0, row);
    for (int i = 0; i < 16; i++) {
        int idx = i - pad;
        if (idx >= 0 && idx < len) lcd.print(text[idx]);
        else                        lcd.print(' ');
    }
}

// Barre de progression [████░░░░░░░░░░] sur ligne 1  — 16 chars: 1[+14+1]
void barreProgression(int pct)
{
    int blocs = (pct * 14) / 100;
    lcd.setCursor(0, 1);       // col 0 → [ col1..14 ] col15  = 16 ✓
    lcd.print('[');
    for (int i = 0; i < 14; i++) {
        if (i < blocs)       lcd.write((byte)CHAR_BLOCK);
        else if (i == blocs) lcd.write((byte)CHAR_HALF);
        else                  lcd.print(' ');
    }
    lcd.print(']');
}

// Tronque + pad un prénom pour occuper exactement `width` caractères
String formatPrenom(String prenom, int width)
{
    if ((int)prenom.length() > width) prenom = prenom.substring(0, width);
    while ((int)prenom.length() < width) prenom += ' ';
    return prenom;
}

// =============================================================================
//  ANIMATION DE DÉMARRAGE
// =============================================================================
void animationDemarrage()
{
    // ── Phase 1 : slide-in du titre depuis la droite ───────────────────────
    const char *titre = "SMART RESEARCH";  // 14 chars
    for (int step = 16; step >= 1; step -= 2) {
        lcd.clear();
        lcd.setCursor(0, 0);
        for (int i = 0; i < 16; i++) {
            int idx = i - step;
            if (idx >= 0 && idx < 14) lcd.print(titre[idx]);
            else                       lcd.print(' ');
        }
        delay(60);
    }
    // Position finale titre centré
    printCentered(0, "SMART RESEARCH");

    // ── Phase 2 : barre de chargement ─────────────────────────────────────
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print('[');
    lcd.setCursor(15, 1);
    lcd.print(']');
    for (int i = 1; i <= 14; i++) {
        lcd.setCursor(i, 1);
        lcd.write((byte)CHAR_BLOCK);
        delay(55);
    }
    delay(200);

    // ── Phase 3 : flash + "SYSTEME PRET" ──────────────────────────────────
    flashBacklight(2, 90);
    lcd.clear();
    printCentered(0, "* SYSTEME PRET *");
    String labMsg = "  Labo ID: " + String(ID_LABO);
    printCentered(1, labMsg.c_str());
    delay(900);
    flashBacklight(1, 150);
}

// =============================================================================
//  ÉCRAN D'ATTENTE (fixe) — appelé une fois
// =============================================================================
void afficherAttenteFixe()
{
    g_scrollPos  = 0;
    g_enAttente  = true;

    // Ligne 0 : [LOCK][LOCK] RFID ACCESS[LOCK][LOCK]  2+12+2=16 ✓
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_LOCK);
    lcd.write((byte)CHAR_LOCK);
    lcd.print(" RFID ACCESS");
    lcd.write((byte)CHAR_LOCK);
    lcd.write((byte)CHAR_LOCK);

    // Ligne 1 sera animée par animerScroll()
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_ARROW);
    lcd.print("              ");
    lcd.write((byte)CHAR_ARROW);
}

// Animation scrolling sur la ligne 1 — appelée dans loop()
void animerScroll()
{
    if (!g_enAttente) return;
    if (millis() - g_lastScroll < 320) return;
    g_lastScroll = millis();

    lcd.setCursor(1, 1);
    for (int i = 0; i < 14; i++) {
        int idx = (g_scrollPos + i) % SCROLL_LEN;
        lcd.print(SCROLL_MSG[idx]);
    }
    g_scrollPos = (g_scrollPos + 1) % SCROLL_LEN;
}

// =============================================================================
//  ÉCRAN "VÉRIFICATION EN COURS"
// =============================================================================
void afficherVerification()
{
    g_enAttente = false;
    lcd.clear();

    // Ligne 0 : [LOCK] Verification [LOCK]  1+14+1=16 ✓
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_LOCK);
    lcd.print(" Verification ");
    lcd.write((byte)CHAR_LOCK);

    // Ligne 1 : barre de progression (vide au départ)
    barreProgression(0);
}

// =============================================================================
//  ARRIVÉE ACCORDÉE  ✓
// =============================================================================
void afficherArrivee(String prenom, String heure)
{
    flashBacklight(2, 75);

    lcd.clear();
    // Ligne 0 : [CHECK][PERSON] Prenom...  (16 chars)
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_CHECK);
    lcd.write((byte)CHAR_PERSON);
    lcd.print(' ');
    lcd.print(formatPrenom(prenom, 13));   // 1+1+1+13 = 16

    // Ligne 1 : [CLOCK] Arrivee  HH:MM  1+10+5=16 ✓
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CLOCK);
    lcd.print(" Arrivee  ");
    lcd.print(heure);

    delay(3500);
}

// =============================================================================
//  DÉPART ENREGISTRÉ  ✓
// =============================================================================
void afficherDepart(String prenom, String heure)
{
    flashBacklight(1, 130);

    lcd.clear();
    // Ligne 0 : [CHECK][PERSON] Prenom...
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_CHECK);
    lcd.write((byte)CHAR_PERSON);
    lcd.print(' ');
    lcd.print(formatPrenom(prenom, 13));

    // Ligne 1 : [CLOCK] Depart   HH:MM  1+10+5=16 ✓
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CLOCK);
    lcd.print(" Depart   ");
    lcd.print(heure);

    delay(3500);
}

// =============================================================================
//  DÉJÀ POINTÉ AUJOURD'HUI  🔒
// =============================================================================
void afficherDejaPointe(String prenom)
{
    flashBacklight(1, 200);

    lcd.clear();
    // Ligne 0 : [LOCK][PERSON] Prenom...
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_LOCK);
    lcd.write((byte)CHAR_PERSON);
    lcd.print(' ');
    lcd.print(formatPrenom(prenom, 13));

    // Ligne 1 : [CLOCK] Deja pointe!
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CLOCK);
    lcd.print(" Deja pointe!  ");

    delay(2800);
}

// =============================================================================
//  ACCÈS REFUSÉ  ✗
// =============================================================================
void afficherRefus()
{
    flashBacklight(3, 80);

    lcd.clear();
    // Ligne 0 : [CROSS] ACCES REFUSE [CROSS]  1+14+1=16 ✓
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_CROSS);
    lcd.print(" ACCES REFUSE ");
    lcd.write((byte)CHAR_CROSS);

    // Ligne 1 : [CROSS][CROSS] Non autorise [CROSS][CROSS]  2+12+2=16 ✓
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CROSS);
    lcd.write((byte)CHAR_CROSS);
    lcd.print("Non autorise");
    lcd.write((byte)CHAR_CROSS);
    lcd.write((byte)CHAR_CROSS);

    delay(2800);
}

// =============================================================================
//  TIMEOUT (Qt ne répond pas)
// =============================================================================
void afficherTimeout()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_CROSS);
    lcd.print("Hors ligne... ");   // 1+14+1=16 ✓
    lcd.write((byte)CHAR_CROSS);

    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CROSS);
    lcd.write((byte)CHAR_CROSS);
    lcd.print("Hors timeout");     // 2+12+2=16 ✓
    lcd.write((byte)CHAR_CROSS);
    lcd.write((byte)CHAR_CROSS);

    delay(2200);
}

// =============================================================================
//  SETUP
// =============================================================================
>>>>>>> 9a10c999ab5f4c212cf0f5bd865d9b0be17c739e:SmartResearchPublicationManagementt/sketch_rfid_labo/sketch_rfid_labo.ino
void setup()
{
    Serial.begin(9600);

<<<<<<< HEAD:SPM/sketch_rfid_labo/sketch_rfid_labo.ino
    // RFID en premier
=======
>>>>>>> 9a10c999ab5f4c212cf0f5bd865d9b0be17c739e:SmartResearchPublicationManagementt/sketch_rfid_labo/sketch_rfid_labo.ino
    SPI.begin();
    rfid.PCD_Init();
    delay(50);
    rfid.PCD_SetAntennaGain(rfid.RxGain_max);

<<<<<<< HEAD:SPM/sketch_rfid_labo/sketch_rfid_labo.ino
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
=======
    Wire.begin();
    delay(50);
    lcd.init();
    lcd.init();   // double init pour certains modules I2C
    lcd.backlight();

    // Charger tous les caractères personnalisés
    lcd.createChar(CHAR_CHECK,  CHAR_DEF_CHECK);
    lcd.createChar(CHAR_CROSS,  CHAR_DEF_CROSS);
    lcd.createChar(CHAR_LOCK,   CHAR_DEF_LOCK);
    lcd.createChar(CHAR_ARROW,  CHAR_DEF_ARROW);
    lcd.createChar(CHAR_BLOCK,  CHAR_DEF_BLOCK);
    lcd.createChar(CHAR_HALF,   CHAR_DEF_HALF);
    lcd.createChar(CHAR_PERSON, CHAR_DEF_PERSON);
    lcd.createChar(CHAR_CLOCK,  CHAR_DEF_CLOCK);
    lcd.clear();   // forcer retour curseur après createChar
    delay(100);

    animationDemarrage();
    afficherAttenteFixe();
}

// =============================================================================
//  LOOP PRINCIPAL
// =============================================================================
void loop()
{
    // Animer le scrolling si on est en attente
    animerScroll();

    // Attendre une carte
    if (!rfid.PICC_IsNewCardPresent()) return;
    if (!rfid.PICC_ReadCardSerial())   return;

    // ── Construire l'UID hex ──────────────────────────────────────────────
>>>>>>> 9a10c999ab5f4c212cf0f5bd865d9b0be17c739e:SmartResearchPublicationManagementt/sketch_rfid_labo/sketch_rfid_labo.ino
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) uid += "0";
        uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();

<<<<<<< HEAD:SPM/sketch_rfid_labo/sketch_rfid_labo.ino
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
=======
    // ── Afficher "Vérification" + envoyer UID à Qt ───────────────────────
    afficherVerification();
    Serial.print("UID:"); Serial.print(uid);
    Serial.print(":"); Serial.println(ID_LABO);

    // ── Attendre réponse Qt avec barre de progression ─────────────────────
    unsigned long debut   = millis();
    unsigned long timeout = 4500;
    while (!Serial.available() && (millis() - debut) < timeout) {
        int pct = (int)(((millis() - debut) * 100UL) / timeout);
        barreProgression(pct);
        delay(70);
    }
    barreProgression(100);
    delay(80);

    // ── Traiter la réponse ────────────────────────────────────────────────
    if (Serial.available()) {
        String rep = Serial.readStringUntil('\n');
        rep.trim();

        if (rep.startsWith("1:")) {
            // ── Arrivée accordée ──────────────────────────────────────────
            int c1 = rep.indexOf(':', 2);
            String prenom = rep.substring(2, c1);
            String heure  = rep.substring(c1 + 1);
            afficherArrivee(prenom, heure);

        } else if (rep.startsWith("2:")) {
            // ── Départ enregistré ─────────────────────────────────────────
            int c1 = rep.indexOf(':', 2);
            String prenom = rep.substring(2, c1);
            String heure  = rep.substring(c1 + 1);
            afficherDepart(prenom, heure);

        } else if (rep.startsWith("3:")) {
            // ── Déjà pointé aujourd'hui ───────────────────────────────────
            String prenom = rep.substring(2);
            afficherDejaPointe(prenom);

        } else {
            // ── Accès refusé (code "0" ou inconnu) ───────────────────────
            afficherRefus();
        }

    } else {
        // ── Pas de réponse → timeout ──────────────────────────────────────
        afficherTimeout();
    }

    // Retour à l'écran d'attente animé
    afficherAttenteFixe();
>>>>>>> 9a10c999ab5f4c212cf0f5bd865d9b0be17c739e:SmartResearchPublicationManagementt/sketch_rfid_labo/sketch_rfid_labo.ino

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}

// =============================================================================
//  SKETCH ARDUINO — RFID + LCD 16×2 + Keypad + OLED + Moteur
//  Projet Smart Research — Esprit
//
//  Brochage :
//    RFID-RC522 : SDA=10, SCK=13, MOSI=11, MISO=12, RST=A2, VCC=3.3V
//    LCD I2C    : SDA=A4, SCL=A5, adresse 0x27
//    OLED I2C   : SDA=A4, SCL=A5, adresse 0x3C  (même bus I2C)
//    Keypad 4x4 : Lignes=5,4,3,2  Colonnes=9,8,7,6
//    Moteur     : IN1=A0, IN2=A1
//
//  !! CHANGEMENTS par rapport aux sketches d'origine !!
//    - RFID RST  : 9  → A2  (broche 9 utilisée par le keypad colonne 0)
//    - Moteur IN1: 10 → A0  (broche 10 utilisée par RFID SS)
//    - Moteur IN2: 11 → A1  (broche 11 utilisée par SPI MOSI)
//
//  Protocole série Qt → Arduino :
//    RFID  : "1:Prenom:HH:MM"      → Arrivée accordée
//            "2:Prenom:HH:MM"      → Départ enregistré
//            "3:Prenom"            → Déjà pointé aujourd'hui
//            "0"                   → Accès refusé
//    SKU   : "MOTOR"               → Tourner moteur 7 secondes
//            "QTY:sku:avant:apres" → Afficher quantités sur OLED
//            "SKU_OK:sku"          → SKU validé par Qt
//
//  Protocole série Arduino → Qt :
//    RFID  : "UID:xxxx:labo_id"    → Badge scanné
//    SKU   : "SKU:xxxxxx"          → Demande vérification SKU
//            "INPUT:xxx"           → Saisie en cours
//            "RESET"               → SKU effacé
//            "ERREUR:SKU_INVALIDE" → SKU trop court
//            "MOTOR_DONE"          → Moteur terminé
// =============================================================================

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <U8x8lib.h>

// ===== RFID =====
#define SS_PIN   10
#define RST_PIN  A2    // déplacé depuis 9 (conflit keypad)
#define ID_LABO   2

MFRC522 rfid(SS_PIN, RST_PIN);

// ===== LCD I2C (système RFID) =====
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===== OLED I2C (système SKU) =====
U8X8_SSD1306_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);

// ===== KEYPAD =====
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'},
  {'A','B','C','D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ===== MOTEUR =====
const int IN1 = A0;   // déplacé depuis 10 (conflit RFID SS)
const int IN2 = A1;   // déplacé depuis 11 (conflit SPI MOSI)

// ===== ÉTAT GLOBAL SKU =====
String sku = "";

// ===== ÉTAT GLOBAL LCD (scroll d'attente RFID) =====
unsigned long g_lastScroll = 0;
int           g_scrollPos  = 0;
bool          g_enAttente  = false;

const char SCROLL_MSG[] = "  Approchez votre badge...   ";
const int  SCROLL_LEN   = sizeof(SCROLL_MSG) - 1;

// =============================================================================
//  CARACTÈRES PERSONNALISÉS LCD (slots 0-7)
// =============================================================================
byte CHAR_DEF_CHECK[8]  = {0b00000,0b00001,0b00011,0b10110,0b11100,0b01000,0b00000,0b00000};
byte CHAR_DEF_CROSS[8]  = {0b00000,0b10001,0b01010,0b00100,0b01010,0b10001,0b00000,0b00000};
byte CHAR_DEF_LOCK[8]   = {0b01110,0b10001,0b10001,0b11111,0b11011,0b11011,0b11111,0b00000};
byte CHAR_DEF_ARROW[8]  = {0b00100,0b00110,0b11111,0b11111,0b11111,0b00110,0b00100,0b00000};
byte CHAR_DEF_BLOCK[8]  = {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
byte CHAR_DEF_HALF[8]   = {0b00000,0b00000,0b00000,0b00000,0b11111,0b11111,0b11111,0b11111};
byte CHAR_DEF_PERSON[8] = {0b00100,0b01110,0b01110,0b00100,0b11111,0b00100,0b01010,0b10001};
byte CHAR_DEF_CLOCK[8]  = {0b00000,0b01110,0b10101,0b10111,0b10001,0b01110,0b00000,0b00000};

#define CHAR_CHECK  0
#define CHAR_CROSS  1
#define CHAR_LOCK   2
#define CHAR_ARROW  3
#define CHAR_BLOCK  4
#define CHAR_HALF   5
#define CHAR_PERSON 6
#define CHAR_CLOCK  7

// =============================================================================
//  FONCTIONS OLED (système SKU / Moteur)
// =============================================================================
void afficherOLED(String l1, String l2, String l3, String l4)
{
    oled.clearDisplay();
    oled.setCursor(0, 0); oled.print(l1);
    oled.setCursor(0, 2); oled.print(l2);
    oled.setCursor(0, 4); oled.print(l3);
    oled.setCursor(0, 6); oled.print(l4);
}

void tournerMoteur7Secondes()
{
    afficherOLED("Code valide", "Moteur tourne", "Attendre", "7 secondes");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(7000);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    Serial.println("MOTOR_DONE");
}

void afficherQuantiteDepuisQt(String cmd)
{
    int p1 = cmd.indexOf(':');
    int p2 = cmd.indexOf(':', p1 + 1);
    int p3 = cmd.indexOf(':', p2 + 1);

    if (p1 == -1 || p2 == -1 || p3 == -1) {
        afficherOLED("Erreur QTY", "Format faux", "", "");
        return;
    }

    String codeSku  = cmd.substring(p1 + 1, p2);
    String qteAvant = cmd.substring(p2 + 1, p3);
    String qteApres = cmd.substring(p3 + 1);

    afficherOLED("Produit:", codeSku, "Avant: " + qteAvant, "Apres: " + qteApres);
}

// =============================================================================
//  FONCTIONS LCD (système RFID / Pointage)
// =============================================================================
void flashBacklight(int fois, int duree_ms)
{
    for (int i = 0; i < fois; i++) {
        lcd.noBacklight(); delay(duree_ms);
        lcd.backlight();   delay(duree_ms);
    }
}

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

void barreProgression(int pct)
{
    int blocs = (pct * 14) / 100;
    lcd.setCursor(0, 1);
    lcd.print('[');
    for (int i = 0; i < 14; i++) {
        if (i < blocs)       lcd.write((byte)CHAR_BLOCK);
        else if (i == blocs) lcd.write((byte)CHAR_HALF);
        else                  lcd.print(' ');
    }
    lcd.print(']');
}

String formatPrenom(String prenom, int width)
{
    if ((int)prenom.length() > width) prenom = prenom.substring(0, width);
    while ((int)prenom.length() < width) prenom += ' ';
    return prenom;
}

void animationDemarrage()
{
    const char *titre = "SMART RESEARCH";
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
    printCentered(0, "SMART RESEARCH");

    lcd.setCursor(0, 1); lcd.print("                ");
    lcd.setCursor(0, 1); lcd.print('[');
    lcd.setCursor(15, 1); lcd.print(']');
    for (int i = 1; i <= 14; i++) {
        lcd.setCursor(i, 1);
        lcd.write((byte)CHAR_BLOCK);
        delay(55);
    }
    delay(200);

    flashBacklight(2, 90);
    lcd.clear();
    printCentered(0, "* SYSTEME PRET *");
    String labMsg = "  Labo ID: " + String(ID_LABO);
    printCentered(1, labMsg.c_str());
    delay(900);
    flashBacklight(1, 150);
}

void afficherAttenteFixe()
{
    g_scrollPos = 0;
    g_enAttente = true;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_LOCK);
    lcd.write((byte)CHAR_LOCK);
    lcd.print("   ACCESS   ");
    lcd.write((byte)CHAR_LOCK);
    lcd.write((byte)CHAR_LOCK);

    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_ARROW);
    lcd.print("              ");
    lcd.write((byte)CHAR_ARROW);
}

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

void afficherVerification()
{
    g_enAttente = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_LOCK);
    lcd.print(" Verification ");
    lcd.write((byte)CHAR_LOCK);
    barreProgression(0);
}

void afficherArrivee(String prenom, String heure)
{
    flashBacklight(2, 75);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_CHECK);
    lcd.write((byte)CHAR_PERSON);
    lcd.print(' ');
    lcd.print(formatPrenom(prenom, 13));
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CLOCK);
    lcd.print(" Arrivee  ");
    lcd.print(heure);
    delay(3500);
}

void afficherDepart(String prenom, String heure)
{
    flashBacklight(1, 130);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_CHECK);
    lcd.write((byte)CHAR_PERSON);
    lcd.print(' ');
    lcd.print(formatPrenom(prenom, 13));
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CLOCK);
    lcd.print(" Depart   ");
    lcd.print(heure);
    delay(3500);
}

void afficherDejaPointe(String prenom)
{
    flashBacklight(1, 200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_LOCK);
    lcd.write((byte)CHAR_PERSON);
    lcd.print(' ');
    lcd.print(formatPrenom(prenom, 13));
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CLOCK);
    lcd.print(" Deja pointe!  ");
    delay(2800);
}

void afficherRefus()
{
    flashBacklight(3, 80);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_CROSS);
    lcd.print(" ACCES REFUSE ");
    lcd.write((byte)CHAR_CROSS);
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CROSS);
    lcd.write((byte)CHAR_CROSS);
    lcd.print("Non autorise");
    lcd.write((byte)CHAR_CROSS);
    lcd.write((byte)CHAR_CROSS);
    delay(2800);
}

void afficherTimeout()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write((byte)CHAR_CROSS);
    lcd.print("Hors ligne... ");
    lcd.write((byte)CHAR_CROSS);
    lcd.setCursor(0, 1);
    lcd.write((byte)CHAR_CROSS);
    lcd.write((byte)CHAR_CROSS);
    lcd.print("Hors timeout");
    lcd.write((byte)CHAR_CROSS);
    lcd.write((byte)CHAR_CROSS);
    delay(2200);
}

// =============================================================================
//  SETUP
// =============================================================================
void setup()
{
    Serial.begin(9600);

    // Moteur
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    // RFID
    SPI.begin();
    rfid.PCD_Init();
    delay(50);
    rfid.PCD_SetAntennaGain(rfid.RxGain_max);

    // I2C + LCD
    Wire.begin();
    delay(50);
    lcd.init();
    lcd.init();
    lcd.backlight();

    lcd.createChar(CHAR_CHECK,  CHAR_DEF_CHECK);
    lcd.createChar(CHAR_CROSS,  CHAR_DEF_CROSS);
    lcd.createChar(CHAR_LOCK,   CHAR_DEF_LOCK);
    lcd.createChar(CHAR_ARROW,  CHAR_DEF_ARROW);
    lcd.createChar(CHAR_BLOCK,  CHAR_DEF_BLOCK);
    lcd.createChar(CHAR_HALF,   CHAR_DEF_HALF);
    lcd.createChar(CHAR_PERSON, CHAR_DEF_PERSON);
    lcd.createChar(CHAR_CLOCK,  CHAR_DEF_CLOCK);
    lcd.clear();
    delay(100);

    // OLED
    oled.setI2CAddress(0x3C * 2);
    oled.begin();
    oled.setFont(u8x8_font_chroma48medium8_r);

    // Animations de démarrage
    animationDemarrage();                                    // LCD
    afficherOLED("SmartResearch", "Systeme pret", "Entrez SKU", ""); // OLED
    afficherAttenteFixe();                                   // LCD scroll
}

// =============================================================================
//  LOOP PRINCIPAL
// =============================================================================
void loop()
{
    // ── 1. Commandes série Qt → Arduino ──────────────────────────────────────
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();

        if (cmd == "MOTOR") {
            tournerMoteur7Secondes();
        }
        else if (cmd.startsWith("QTY:")) {
            afficherQuantiteDepuisQt(cmd);
        }
        else if (cmd.startsWith("SKU_OK:")) {
            String codeSku = cmd.substring(7);
            afficherOLED("Code correct", codeSku, "Moteur bientot", "");
        }
        // Les réponses RFID (1:, 2:, 3:, 0) sont traitées dans le bloc RFID ci-dessous
    }

    // ── 2. Animation scroll LCD (attente badge RFID) ──────────────────────────
    animerScroll();

    // ── 3. Scan RFID ─────────────────────────────────────────────────────────
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {

        // Construire l'UID hex
        String uid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
            if (rfid.uid.uidByte[i] < 0x10) uid += "0";
            uid += String(rfid.uid.uidByte[i], HEX);
        }
        uid.toUpperCase();

        // Afficher vérification + envoyer UID à Qt
        afficherVerification();
        Serial.print("UID:"); Serial.print(uid);
        Serial.print(":"); Serial.println(ID_LABO);

        // Attendre réponse Qt avec barre de progression
        unsigned long debut   = millis();
        unsigned long timeout = 4500;
        while (!Serial.available() && (millis() - debut) < timeout) {
            int pct = (int)(((millis() - debut) * 100UL) / timeout);
            barreProgression(pct);
            delay(70);
        }
        barreProgression(100);
        delay(80);

        // Traiter la réponse
        if (Serial.available()) {
            String rep = Serial.readStringUntil('\n');
            rep.trim();

            if (rep.startsWith("1:")) {
                int c1 = rep.indexOf(':', 2);
                afficherArrivee(rep.substring(2, c1), rep.substring(c1 + 1));
            }
            else if (rep.startsWith("2:")) {
                int c1 = rep.indexOf(':', 2);
                afficherDepart(rep.substring(2, c1), rep.substring(c1 + 1));
            }
            else if (rep.startsWith("3:")) {
                afficherDejaPointe(rep.substring(2));
            }
            else {
                afficherRefus();
            }
        }
        else {
            afficherTimeout();
        }

        afficherAttenteFixe();
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
    }

    // ── 4. Saisie SKU via Keypad (OLED) ──────────────────────────────────────
    char key = keypad.getKey();

    if (key) {
        if (key == '*') {
            sku = "";
            Serial.println("RESET");
            afficherOLED("Reset", "Code efface", "Entrez SKU", "");
        }
        else if (key == '#') {
            if (sku.length() == 6) {
                Serial.println("SKU:" + sku);
                afficherOLED("Verification", "SKU:", sku, "");
            }
            else {
                Serial.println("ERREUR:SKU_INVALIDE");
                afficherOLED("Erreur", "SKU invalide", "6 caracteres", "");
            }
            sku = "";
        }
        else {
            if (sku.length() < 6) {
                sku += key;
                Serial.println("INPUT:" + sku);

                String affichage = sku;
                if (affichage.length() > 3)
                    affichage = affichage.substring(0, 3) + "-" + affichage.substring(3);

                afficherOLED("Saisie SKU", affichage, "# valider", "* reset");
            }
        }
    }
}

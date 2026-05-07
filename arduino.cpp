#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ================== PINS ==================
#define SS_PIN    10
#define RST_PIN   9
#define SERVO_PIN 2
#define ID_LABO   2

MFRC522            rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C  lcd(0x27, 16, 2);
Servo              myServo;

// ================== SETUP ==================
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Wire.begin();
  lcd.init();
  lcd.backlight();
  myServo.attach(SERVO_PIN);
  myServo.write(0); // closed

  lcd.setCursor(0, 0);
  lcd.print("RFID SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("Scan card...");
}

// ================== LOOP ==================
void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial())   return;

  // Build UID
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  // Send UID to Qt
  Serial.print("UID:");
  Serial.print(uid);
  Serial.print(":");
  Serial.println(ID_LABO);

  // Show verification
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Verification...");

  // Wait for response (4 seconds max)
  unsigned long start = millis();
  while (!Serial.available() && millis() - start < 4000);

  // ================== RESPONSE ==================
  if (Serial.available()) {
    String rep = Serial.readStringUntil('\n');
    rep.trim();

    if (rep.startsWith("1:")) {
      // ✅ ARRIVEE
      int    c1     = rep.indexOf(':', 2);
      String prenom = rep.substring(2, c1);
      String heure  = rep.substring(c1 + 1);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bienvenue");
      lcd.setCursor(0, 1);
      lcd.print(prenom + " " + heure);

      myServo.write(90); // open
      delay(3000);
      myServo.write(0);  // close

    } else if (rep.startsWith("2:")) {
      // 🚪 DEPART
      int    c1     = rep.indexOf(':', 2);
      String prenom = rep.substring(2, c1);
      String heure  = rep.substring(c1 + 1);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Au revoir");
      lcd.setCursor(0, 1);
      lcd.print(prenom + " " + heure);

      myServo.write(90); // open
      delay(3000);
      myServo.write(0);  // close

    } else if (rep.startsWith("3:")) {
      // ⚠️ DEJA POINTE
      String prenom = rep.substring(2);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Deja pointe:");
      lcd.setCursor(0, 1);
      lcd.print(prenom);

    } else {
      // ❌ ACCESS DENIED
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ACCES REFUSE");
    }

  } else {
    // ⏱ TIMEOUT
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TIMEOUT");
  }

  delay(2000);
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  // Back to waiting screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan card...");
}

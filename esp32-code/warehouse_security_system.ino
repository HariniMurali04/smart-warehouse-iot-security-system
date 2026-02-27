#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include "DHT.h"
#include <WebServer.h>

/* WiFi Credentials */
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

/* Firebase Configuration */
#define API_KEY "YOUR_FIREBASE_API_KEY"
#define DATABASE_URL "YOUR_FIREBASE_DATABASE_URL"

/* Honeypot Web Server */
WebServer hpServer(80);
WiFiServer hp21(21);
WiFiServer hp22(22);
WiFiServer hp23(23);

/* Hardware Setup */
#define DHTPIN1 32
#define DHTPIN2 33
#define DHTTYPE DHT11

#define BUZZER_PIN 26

#define TEMP_LIMIT 35.0
#define HUM_LIMIT 80.0

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

Servo servo1;
Servo servo2;

/* RFID Setup */
#define SS_1 5
#define RST_1 27
#define SS_2 21
#define RST_2 22

MFRC522 rfid1(SS_1, RST_1);
MFRC522 rfid2(SS_2, RST_2);

/* Authorized Cards */
String knownUID1 = "14 0D C9 01";
String knownUID2 = "AB B5 38 03";

/* Buzzer Alert */
void buzzerAlertNow() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(150);
  }
}

/* Door Control */
void openDoor(Servo &servo) {
  servo.write(0);
  delay(2000);
  servo.write(90);
}

/* Get RFID UID */
String getUID(MFRC522 &rfid) {
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  return uid;
}

/* Environment Monitoring */
void checkEnvironment() {
  float t1 = dht1.readTemperature();
  float h1 = dht1.readHumidity();
  float t2 = dht2.readTemperature();
  float h2 = dht2.readHumidity();

  if (t1 > TEMP_LIMIT || h1 > HUM_LIMIT ||
      t2 > TEMP_LIMIT || h2 > HUM_LIMIT) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);

  dht1.begin();
  dht2.begin();

  servo1.attach(13);
  servo2.attach(12);

  SPI.begin();
  rfid1.PCD_Init();
  rfid2.PCD_Init();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());

  hpServer.begin();
  hp21.begin();
  hp22.begin();
  hp23.begin();

  Serial.println("System Ready");
}

void loop() {

  hpServer.handleClient();

  checkEnvironment();

  if (rfid1.PICC_IsNewCardPresent() && rfid1.PICC_ReadCardSerial()) {
    String uid = getUID(rfid1);

    if (uid == knownUID1) {
      openDoor(servo1);
    } else {
      buzzerAlertNow();
    }
  }

  if (rfid2.PICC_IsNewCardPresent() && rfid2.PICC_ReadCardSerial()) {
    String uid = getUID(rfid2);

    if (uid == knownUID2) {
      openDoor(servo2);
    } else {
      buzzerAlertNow();
    }
  }

  delay(500);
}

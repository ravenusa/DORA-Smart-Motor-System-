#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define RXD2 16
#define TXD2 17

#define BOT_TOKEN "botToken"
#define CHAT_ID "chatID"

const char* ssid = "ssid";
const char* password = "pass";

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

SoftwareSerial SerialGPS(RXD2, TXD2);
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("GPS Tracker");
}

void loop() {
  while (SerialGPS.available()) {
    gps.encode(SerialGPS.read());
  }

  if (gps.location.isValid()) {
    String message = "Latitude: " + String(gps.location.lat(), 6) + 
                     "\nLongitude: " + String(gps.location.lng(), 6);
    bot.sendMessage(CHAT_ID, message, "");
  }

  delay(10000);
}

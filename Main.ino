#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define RXD2 16
#define TXD2 17
#define RXD3 15
#define TXD3 14

#define BOT_TOKEN "bot_token"
#define CHAT_ID "chat_id"

const char* ssid = "ssid";
const char* password = "password";

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

SoftwareSerial SerialGPS(RXD2, TXD2);//Pin bisa diubah ke Digital
SoftwareSerial SIM800L(RXD3, TXD3);
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600);
  SIM800L.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Initializing SIM800L");
  SIM800L.println("AT");
  delay(1000);
  SIM800L.println("AT+CSQ");
  delay(1000);
  SIM800L.println("AT+CREG?");
  delay(1000);
  SIM800L.println("AT+COPS?");
  delay(1000);
  SIM800L.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
  SIM800L.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(1000);
  SIM800L.println("AT+SAPBR=1,1");
  delay(1000);
  SIM800L.println("AT+HTTPINIT");
  delay(1000);
  SIM800L.println("AT+HTTPPARA=\"CID\",1");
  delay(1000);
  Serial.println("SIM800L initialized");
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
``

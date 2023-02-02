#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define RXD2 16
#define TXD2 17

SoftwareSerial SerialGPS(RXD2, TXD2);
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600);
  Serial.println("GPS Tracker");
}

void loop() {
  while (SerialGPS.available()) {
    gps.encode(SerialGPS.read());
  }

  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  }

  delay(1000);
}

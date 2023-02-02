#define BLYNK_PRINT Serial   
#define BLYNK_TEMPLATE_ID   "xxxxxxx"     //TEMPLATE_ID dari blynk IoT
#define BLYNK_DEVICE_NAME "xxxxxxx" // dari blynk IoT
#include <ESP8266WiFi.h>        
#include <BlynkSimpleEsp8266.h> 
       
char auth[] = "xxxxxxx";      
char ssid[] = "xxxxxxx"; //WIFI NAME        
char pass[] = "xxxxxxx"; //PASSWORD  
      
void setup()        
{        
 Serial.begin(9600);        
 Blynk.begin(auth, ssid, pass);  
 //Blynk.begin(auth, ssid, pass,  "iot.serangkota.go.id", 8080); 
 pinMode(D4, LOW);  
 pinMode(D1, LOW);
 pinMode(D2, LOW);
 pinMode(D3, LOW);
}        

void loop()        
{        
  Blynk.run();    
}  

#include <SoftwareSerial.h>
#include <String.h>
#include <DHT.h> 
 
#define DHTPIN 5

SoftwareSerial SIM800L(6,7);                //Serial SIM800L pin
DHT dhtSensor(DHTPIN, DHT22); 
String Write_API_key = "AAAAAAAAAAVTZZZAHAHAA";  //Thingspeak Write API Key
String apn = "3gprs";   
float kelembaban;
float suhu; 
void setup(){
  Serial.begin(115200); 
  SIM800L.begin(9600);      
  dhtSensor.begin();
  Serial.println("SIM800L GPRS Test");
  delay(2000);
}
 
void loop(){
  SetupModule();
  SIM800L.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");
  delay(3000);
  ShowSerialData();
 
  SIM800L.println("AT+CIPSEND");
  delay(2000);
  Serial.println();
  ShowSerialData();
  ReadSensor();
  String str="GET https://api.thingspeak.com/update?api_key="+Write_API_key+"&field1=" + String(suhu) +"&field2="+String(kelembaban);
  Serial.println(str);  delay(2000);
  SIM800L.println(str); delay(4000);
  ShowSerialData();
 
  SIM800L.println((char)26); delay(4000); 
  SIM800L.println();
  ShowSerialData();
  SIM800L.println("AT+CIPSHUT");//close the connection
  delay(500); 
  ShowSerialData();
  str="";
  
  //total delay looping 50s
  delay(10000); //add 10s for 60s total delay looping 
} 

void ReadSensor(){
  kelembaban = dhtSensor.readHumidity();
  suhu = dhtSensor.readTemperature(); 
  delay(500); 
  Serial.println();    
  Serial.print("Temperature = ");Serial.print(suhu); Serial.print(" °C");
  Serial.print("\t");
  Serial.print("Humidity = ");Serial.print(kelembaban);Serial.println(" %");    
  
}

void SetupModule(){  
  if (SIM800L.available())Serial.write(SIM800L.read());
  SIM800L.println("AT"); delay(1000);
  SIM800L.println("AT+CPIN?"); delay(1000);
  SIM800L.println("AT+CREG?"); delay(1000);
  SIM800L.println("AT+CGATT?"); delay(1000);
  SIM800L.println("AT+CIPSHUT");delay(1000);
  SIM800L.println("AT+CIPSTATUS"); delay(2000);
  SIM800L.println("AT+CIPMUX=0");  delay(2000);

 //setting the APN,
  SIM800L.println("AT+CSTT=\""+apn+"\"");delay(1000);
  ShowSerialData();
  SIM800L.println("AT+CIICR");    delay(2000);
  ShowSerialData();
  
  //get local IP adress
  SIM800L.println("AT+CIFSR");    delay(2000);
  ShowSerialData();
  
  SIM800L.println("AT+CIPSPRT=0");delay(2000);
  ShowSerialData();
}

void ShowSerialData(){
  while(SIM800L.available()!=0)
  Serial.write(SIM800L.read());
  delay(2000); 
}

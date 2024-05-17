#include <ESP8266WiFi.h>
#include "MQ135.h"
#include "ThingSpeak.h"
#include "DHT.h"
#define DPIN 4
#define DTYPE DHT11

DHT dht(DPIN,DTYPE);


char ssid[] = "";    
char pass[] = "";   
int keyIndex = 0;            

WiFiClient  client;

unsigned long myChannelNumber = ;
const char * myWriteAPIKey = "";


void setup() {
  Serial.begin(9600);  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  ThingSpeak.begin(client);  
  dht.begin();
}



void sendData(){

  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();

  float temperature=dht.readTemperature(true);
  float humidity=dht.readHumidity();
  
  

  ThingSpeak.setField(1, air_quality);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, humidity);


 int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){
    Serial.println("Channel update successful.");
    Serial.print(F("CO2: "));
    Serial.print(air_quality);
    
    Serial.print(F("Temperature: "));
    Serial.print(temperature);
    
    Serial.print(F("Humidity: "));
    Serial.print(humidity);
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000);//beacause thingspeak takes 15s delay
}




void loop() {

char buffer[20]="";
if(Serial.available()>0){
  Serial.readBytesUntil('\n',buffer,20);
  Serial.println(buffer);

      // Check if the received text is "send"
    if (strcmp(buffer, "send") == 0) {
         sendData();
    }
}
}

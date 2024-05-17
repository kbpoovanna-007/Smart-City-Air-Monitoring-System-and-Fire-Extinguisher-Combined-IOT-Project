//Sending data from MQ135 to thingspeak
//-------------------------------------------------------------------

#include <ESP8266WiFi.h>
#include "MQ135.h"
#include "ThingSpeak.h"

char ssid[] = 
char pass[] = 
int keyIndex = 0;            

WiFiClient  client;

unsigned long myChannelNumber = ;
const char * myWriteAPIKey = "";


void setup() {
  Serial.begin(115200);  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  ThingSpeak.begin(client);  
}



void loop() {

  MQ135 gasSensor = MQ135(A0);
  float air_quality = gasSensor.getPPM();
  
  

  ThingSpeak.setField(1, air_quality);


 int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){
    Serial.println("Channel update successful.");
    Serial.print(F("CO2: "));
    Serial.print(air_quality);
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000);//beacause thingspeak takes 15s delay
}



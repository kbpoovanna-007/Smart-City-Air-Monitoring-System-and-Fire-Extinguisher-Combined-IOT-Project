#include "DHT.h"
#define DPIN 4
#define DTYPE DHT11

DHT dht(DPIN,DTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  delay(2000);
  float tc=dht.readTemperature(true); // reads temperature in F
  float hu=dht.readHumidity();

  Serial.print("Temp: ");
  Serial.print(tc);
  Serial.print("F");
  Serial.print("Hum: ");
  Serial.print(hu);
  Serial.print("%");


}

//Arduino

#include <IRremote.hpp>

#define MAX_HEX_LENGTH 9 // Including null terminator
#define DELAY_DEFAULT 10 // Default delay

IRrecv IR(7);            
decode_results results;
char receivedHex[MAX_HEX_LENGTH]; 

void setup()
{
    Serial.begin(9600);
    IR.enableIRIn();
}

void loop()
{
    if (IR.decode())
    {
        // Store received hex code in array
        sprintf(receivedHex, "%08lX", IR.decodedIRData.decodedRawData);

        Serial.println(receivedHex);

        // Check which button was pressed
        switch (strtoul(receivedHex, NULL, 16))
        {
        case 0xE31CFF00:
            Serial.print(receivedHex);
            delay(500);
            break;
        default:
            Serial.print(receivedHex);
            break;
        }
        delay(200);
        IR.resume();
    }
}

/*
NodeMCU


void setup(){
  Serial.begin(9600);
}


void loop(){
char buffer[20]="";
if(Serial.available()>0){
  Serial.readBytesUntil('\n',buffer,20);
  Serial.println(buffer);

      // Check if the received text is "send"
    if (strcmp(buffer, "E31CFF00") == 0) {
      Serial.println("I got the message");
    }
}
}

*/


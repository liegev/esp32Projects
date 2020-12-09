#include "heltec.h"
#include "images.h"
#define BAND    915E6

unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;
String incomingText = "";

void setup()
{
  Serial.begin(115200);
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Booting up...");
  Heltec.display->display();
  delay(500);
}

void loop()
{
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "Sending packet: ");
  Heltec.display->drawString(90, 0, String(counter));
  Heltec.display->display();
  // send packet
  LoRa.beginPacket();
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  
  if (Serial.available() > 0) {
    incomingText = Serial.readString();
      LoRa.println(incomingText);
  }
    
  LoRa.endPacket();
  counter++;
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(5000);                       // wait for 5 seconds
}

#include <SPI.h>
#include <SSD1306AsciiSpi.h>

#include "OWL.h"

#define OLED_DC 5
#define OLED_CS 3
#define OLED_RES 6

OWL o;
SSD1306AsciiSpi oled;

void setup() {
  pinMode(OLED_RES, OUTPUT);
  digitalWrite(OLED_RES,HIGH); 
  
  oled.begin(&Adafruit128x64, OLED_CS, OLED_DC);
  oled.setFont(Adafruit5x7);  
  oled.set1X();

  oled.clear();
  oled.println("Connecting");

  delay(1000);
  
  o.connect(9600);
  digitalWrite(13, HIGH);

  oled.clear();
  oled.println("Connected - sending request");

  o.sendCommand("tweets_with", "mystfit");
  while(!Serial.available()){}
  
  String s = "";
  while(Serial.available()){
      s = Serial.readStringUntil("\n");
  }
  
  oled.clear();
  oled.print("tweets:");
  oled.print(s);
  
}

void loop() {

  
  
  // put your main code here, to run repeatedly:
}

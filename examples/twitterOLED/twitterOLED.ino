#include <SPI.h>
#include <SSD1306AsciiSpi.h>

#include <serialTwitter.h>

//this assumes hardware SPI
//sck -> pin 13
//sda -> pin 11
#define OLED_DC 5
#define OLED_CS 3
#define OLED_RES 6

//this sets up the status pin which flashes
//the status of the twitter request
int twitter_status_pin = 2;

SerialTwitter twitter(twitter_status_pin);
SSD1306AsciiSpi oled;

void setup() {
  pinMode(OLED_RES, OUTPUT);
  digitalWrite(OLED_RES,HIGH);

  oled.begin(&Adafruit128x64, OLED_CS, OLED_DC);
  oled.setFont(Adafruit5x7);
  oled.set1X();

  oled.clear();
  oled.println("Connecting");

  twitter.connect();

  oled.clear();
  oled.println("Connected - sending request");

  int count = twitter.tweets_with("syria");

  oled.clear();
  oled.print("tweets:");
  oled.print(count);

}

void loop() {



  // put your main code here, to run repeatedly:
}

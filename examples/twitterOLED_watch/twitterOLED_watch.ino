#include <SPI.h>
#include <SSD1306AsciiSpi.h>

#include <SerialTwitter.h>

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
  oled.println("Connected - watching for 'syria'");

  twitter.watchForTweetsWith("syria");
}

void loop() {

  OWLCommand tweet = twitter.pollForWatchedTweets();

  if(!tweet.empty){
    //do something in here when new tweet arrives!
    oled.clear();
    oled.print("tweet:");
    oled.print(tweet.data);
  }

}

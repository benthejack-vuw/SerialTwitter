#include <SerialTwitter.h>

//pin for twitter to let you know it's current status
int twitter_status_pin = 2;

SerialTwitter twitter(twitter_status_pin);

void setup() {
 twitter.connect();

 //because "hi" is so common this will take a long time.
 //if you plug an LED into the twitter_status_pin it will
 //flash while it's waiting for the reply
 String tweet = twitter.latestTweetWith("hi").data;

 twitter.print("arduino heard: ");
 twitter.println(data);
}

void loop() {
}

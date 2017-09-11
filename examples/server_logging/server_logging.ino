#include <serialTwitter.h>

//pin for twitter to let you know it's current status
int twitter_status_pin = 2;

SerialTwitter twitter(twitter_status_pin);

void setup() {
 twitter.connect();
 
 //because "hi" is so common this will take a long time.
 //if you plug an LED into the twitter_status_pin it will 
 //flash while it's waiting for the reply
 int count = twitter.tweets_with("hi");
 
 //If you want to print out from the arduino for debugging DON'T use Serial.println() or Serial.print()
 //instead use twitter.println() and twitter.print() 
 //instead of looking at the arduino serial monitor (which will refuse to open)
 //look at the server script window 
 
 twitter.print("arduino heard: ");
 twitter.println(String(count));
}

void loop() {
}

#include <serialTwitter.h>

//pin for twitter to let you know it's current status
int twitter_status_pin = 2;
int button_pin = 3;

SerialTwitter twitter(twitter_status_pin);

void setup() {
 twitter.connect();
}

void loop() {

  int button = digitalRead(button_pin);
  
  if(button == HIGH){
    twitter.tweet("I PRESSED A BUTTON! #arduino");
    delay(2000); 
  }
  
}

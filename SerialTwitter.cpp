#include "serialTwitter.h"

SerialTwitter::SerialTwitter(int statusPin){
    _statusPin = statusPin;
    pinMode(_statusPin, OUTPUT);
}

void SerialTwitter::connect(){
  owl.connect(9600);
}


void SerialTwitter::print(String text){
  owl.sendCommand("log", text);
}

void SerialTwitter::println(String text){
  owl.sendCommand("println", text);
}

void SerialTwitter::tweet(String text){
  owl.sendCommand("post_tweet", text);
}

int SerialTwitter::tweets_with(String text){
  owl.sendCommand("tweets_with", text);
  String reply = wait_for_reply();
  return reply.toInt();
}

String SerialTwitter::wait_for_reply(){
  bool toggle = false;

  while(!Serial.available()){
    if(_statusPin >= 0){
        digitalWrite(_statusPin, toggle);
        toggle = !toggle;
    }
    delay(200);
  }

  if(_statusPin >= 0){
    digitalWrite(_statusPin, LOW);
  }

  String reply;
  while(Serial.available()){
      reply = Serial.readStringUntil("\n");
  }

  return reply;
}

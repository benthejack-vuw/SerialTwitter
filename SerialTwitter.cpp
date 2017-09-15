#include "serialTwitter.h"

SerialTwitter::SerialTwitter(int statusPin){
    _owl.statusPin(statusPin);
}

void SerialTwitter::connect(){
  _owl.connect(9600);
}


void SerialTwitter::print(String text){
  _owl.sendCommand("log", text);
}

void SerialTwitter::println(String text){
  _owl.sendCommand("println", text);
}

void SerialTwitter::tweet(String text){
  _owl.sendCommand("post_tweet", text);
}

int SerialTwitter::numberOfTweetsWith(String text){
  _owl.sendCommand("number_of_tweets_with", text);

  OWLCommand reply = _owl.awaitReply();
  return reply.data.toInt();
}

String SerialTwitter::latestTweetWith(String text){
  _owl.sendCommand("latest_tweet_with", text);
  OWLCommand reply = _owl.awaitReply();
  return reply.data;
}


void SerialTwitter::watchForTweetsWith(String text){
  _owl.sendCommand("watch_for_tweets_with", text);
}

OWLCommand SerialTwitter::pollForWatchedTweets(){
  return _owl.pollSerial();
}

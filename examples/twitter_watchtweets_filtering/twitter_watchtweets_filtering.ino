#include <SerialTwitter.h>


int new_tweet_pin = 3;

//this sets up the status pin which flashes
//the status of the twitter request
int twitter_status_pin = 2;

SerialTwitter twitter(twitter_status_pin);

void setup() {

  pinMode(new_tweet_pin, OUTPUT);

  twitter.connect();
  //tell the server to watch for tweets to @justinbieber with the text 'marry me'
  //if you are watching for tweets you currently can't do anything else with the server
  twitter.watchForTweetsWith("to:justinbieber marry me");
}

void loop() {

  //get the latest tweet that the server is watchig for
  OWLCommand tweet = twitter.pollForWatchedTweets();

  //test if there is a new tweet or not
  if(!tweet.empty){
    //do something in here when a new tweet arrives!
    digitalWrite(new_tweet_pin, HIGH);
    delay(500);
    digitalWrite(new_tweet_pin, LOW);
    delay(500);
  }

}

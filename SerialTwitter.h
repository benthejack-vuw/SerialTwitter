#include <Arduino.h>
#include "OWL.h"

class SerialTwitter{
  public:
    SerialTwitter(){};
    SerialTwitter(int statusPin);
    void connect();
    void print(String text);
    void println(String text);
    int tweets_with(String text);
    void tweet(String text);
    String wait_for_reply();
  private:
    int _statusPin = -1;
    OWL owl;
};

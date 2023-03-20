#include <Arduino.h>
#include "wifihandler.h"
#include "webserver.h"
#include "reader.h"
WiFiHandler* wifi;
Webserver* webserver;
Reader* reader;

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);
  wifi = new WiFiHandler();
  reader = new Reader(wifi);
  //webserver = new Webserver(reader);
  
}

void loop()
{
 reader->loop();
}
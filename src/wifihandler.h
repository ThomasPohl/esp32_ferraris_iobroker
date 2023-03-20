#pragma once
#include <WiFi.h>
class WiFiHandler {
public:
  WiFiHandler();
  void send(int ts);
private:
  int toBeSent;
  void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info);
  void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info);
  void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);

};

#include "wifihandler.h"
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "TODO";
const char *password = "TODO";
 

WiFiHandler::WiFiHandler()
{
    WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info){this->WiFiStationConnected(event, info);}, WiFiEvent_t::SYSTEM_EVENT_STA_CONNECTED);
    WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info){this->WiFiGotIP(event, info);}, WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
    WiFi.onEvent([this](WiFiEvent_t event, WiFiEventInfo_t info){this->WiFiStationDisconnected(event, info);}, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);
    toBeSent = 0;
    //WiFi.begin(ssid, password);
    //WiFi.setAutoReconnect(true);
    //Serial.println();
    //Serial.println();
    //Serial.println("Wait for WiFi... ");
}

void WiFiHandler::WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Connected to AP successfully!");
}

void WiFiHandler::WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

  if (toBeSent>0){
        String url = "http://192.168.178.32:8087/set/0_userdata.0.strom_sensor?value=" + String(toBeSent);
        Serial.println(url);
        HTTPClient http;
        http.begin(url);
        int httpCode = http.GET();
        if (httpCode != 200)
            Serial.println(httpCode);
        http.end();
        toBeSent=0;
    }
    WiFi.disconnect();
}
void WiFiHandler::send(int ts){
    Serial.println("Sending");
    WiFi.begin(ssid, password);
    toBeSent = ts;
}
void WiFiHandler::WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Disconnected from WiFi access point");
    Serial.print("WiFi lost connection. Reason: ");
    Serial.println(info.disconnected.reason);
}



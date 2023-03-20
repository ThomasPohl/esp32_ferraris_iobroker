#include "webserver.h"
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"

Webserver::Webserver(Reader *reader)
{
    this->reader = reader;
    initFilesystem();
    server.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request)
              { 
                bool withDetails = request->hasParam("details");
                unsigned long *redEvents = this->reader->getRedEvents();
                unsigned long count = this->reader->getCount();

                String json = "{\"redEvents\":";
                String array = "[";
                array+=redEvents[0];
                for (int i=1;i<5;i++){
                    array+=",";
                    array+=redEvents[i];
                }
                array+="]";
                json+=array;
                if (withDetails){
                   unsigned int *vals = this->reader->getVals();

                    json+=",\"vals\":";

                    array="[";
                    array+=vals[0];
                    for (int i=1;i<100;i++){
                        array+=",";
                        array+=vals[i];
                    }
                    array+="]";
                    json+=array;
                }
                json+=", \"end\":";
                json+=count;
                json+="}";
                request->send(200, "application/json", json); });
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html", false); });
    server.serveStatic("/", SPIFFS, "/");
    server.begin();
    Serial.println("Initialized webserver");
}

void Webserver::initFilesystem()
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An error has occurred while mounting SPIFFS");
    }
    Serial.println("SPIFFS mounted successfully");
}
#pragma once
#include "wifihandler.h"
class Reader {

private:
    static const unsigned int numReadings = 100;
    static const unsigned int numMovingAverage = 5;
    static const unsigned int minRedCount = 5;
    
    unsigned int redLevel = 40;
    unsigned int movingAverageVals[numMovingAverage];
    unsigned int analogVals[numReadings];
    unsigned int reorderedVals[numReadings];
    unsigned long lastRedEvents[5];
    unsigned int i = 0;
    unsigned long count = 0;
    unsigned int redCount = 0;

public:
    Reader(WiFiHandler * wifiHandler);
    void loop();
    unsigned int* getVals();
    unsigned long* getRedEvents();
    unsigned long getCount();
private:
    void newReading(int val);
    void startOfRed();
    void endOfRed();
    WiFiHandler * wifihandler;
};
#include "reader.h"
#include <Arduino.h>

Reader::Reader(WiFiHandler * wifiHandler){
    this->wifihandler = wifiHandler;
}

void Reader::loop()
{

    static uint32_t tStart = millis();   // ms; start time
    const uint32_t DESIRED_PERIOD = 100; // ms
    uint32_t tNow = millis();            // ms; time now
    if (tNow - tStart >= DESIRED_PERIOD)
    {
        tStart += DESIRED_PERIOD; // update start time to ensure consistent and near-exact period

        newReading(analogRead(A0));
    }
}

unsigned int *Reader::getVals()
{
    for (int j = 0; j < numReadings; j++)
    {
        reorderedVals[j] = this->analogVals[j + i < numReadings ? j + i : j + i - numReadings];
    }
    return &reorderedVals[0];
}

unsigned long Reader::getCount()
{
    return count;
}

void Reader::newReading(int val)
{
    int sumVals = 0;

    for (int j = 0; j < numMovingAverage - 1; j++)
    {
        movingAverageVals[j] = movingAverageVals[j + 1];
        sumVals += movingAverageVals[j];
    }
    movingAverageVals[numMovingAverage - 1] = val;
    sumVals += val;

    analogVals[i] = sumVals / numMovingAverage;
    if (analogVals[i]>redLevel){
        redCount++;
        if (redCount==minRedCount){
            startOfRed();
        }
    } else {
        redCount=0;
            endOfRed();
    }
    i++;
    count++;
    if (i >= numReadings)
    {
        i = 0; // reset to beginning of array, so you don't try to save readings outside of the bounds of the array
    }
}

    void Reader::startOfRed(){
        Serial.println("red");
        
        for (int j=0;j<4;j++){
            lastRedEvents[j] = lastRedEvents[j+1];
        }
        lastRedEvents[4] = count;
        if (lastRedEvents[3]>0){
            long duration = lastRedEvents[4]-lastRedEvents[3];
            int watt = 480000/duration;
            wifihandler->send(watt);
        }
    }
    void Reader::endOfRed(){

    }
    unsigned long* Reader::getRedEvents(){
        return &lastRedEvents[0];
    }
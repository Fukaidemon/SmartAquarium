#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>

//generate unique name from MAC addr
String macToStr(const uint8_t* mac){

    String result;

    for (int i = 0; i < 6; ++i) {
        result += String(mac[i], 16);

        if (i < 5){
            result += ':';
        }
    }

    return result;
}

char* getNameAndAddress(){
    // Generate client name based on MAC address and last 8 bits of microsecond counter
    String clientName;
    clientName += "esp8266-";
    uint8_t mac[6];
    WiFi.macAddress(mac);
    clientName += macToStr(mac);
    return (char*) clientName.c_str();
}

float interpolateFloat(const float &currentValue, const float &target, const float &step){
    if (currentValue < target){
        if ((currentValue + step) > target) return target;
        else return currentValue + step; 
    }
    else if (currentValue > target){
        if ((currentValue - step) < target) return target;
        else return currentValue - step; 
    }
}
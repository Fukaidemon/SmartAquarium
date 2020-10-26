#pragma once
#include <Arduino.h>

#define DEFAULT_WLS_PIN 8

class WaterLevelSensor{

private:

    uint8_t pin;
    uint8_t state;

protected: 

public:

    //  Default constructor
    WaterLevelSensor(){
        pin = DEFAULT_WLS_PIN;
        state = LOW;
    }
    // Custom constructor to set the pin
    WaterLevelSensor(const uint8_t &newPin){
        pin = newPin;
        state = LOW;
    }

    void setPin(const uint8_t &newPin){
        pin = newPin;
    }
    // Updates the state of the water level, to call in the loop
    void update(){
        uint8_t newState = digitalRead(pin);
        if (newState != state){
            state = digitalRead(pin);
        }  
    }

    uint8_t getState() const{return state;}
    
};

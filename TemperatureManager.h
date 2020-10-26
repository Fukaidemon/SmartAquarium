#include "include/TemperatureSensor.h"

TemperatureSensor* TS = new TemperatureSensor(A0, .3f);

float temperature = 0.f;
uint8_t TMP_Changed = 0;

void TemperatureLoop(){
    TS->update();
    float value = TS->getTempInCelcius();
    if(abs(temperature - value) >= TS->thershold){
        temperature = value;
        TMP_Changed = 1;
    }
}
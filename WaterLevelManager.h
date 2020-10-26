#include "include/WaterLevelSensor.h"

#define WATER_LEVEL_PIN1 D0
#define WATER_LEVEL_PIN2 D1
#define WATER_LEVEL_PIN3 D2 

enum WaterLevel{
  High_Level,
  Mid_Level,
  Low_Level,
  VeryLow_Level
};

// Declare the 3 water level sensors
WaterLevelSensor* WLS_Level1 = new WaterLevelSensor(WATER_LEVEL_PIN1); // 8 is the pin connected to the Water Level Sensor
WaterLevelSensor* WLS_Level2 = new WaterLevelSensor(WATER_LEVEL_PIN2);
WaterLevelSensor* WLS_Level3 = new WaterLevelSensor(WATER_LEVEL_PIN3);

// WL represents the current water level (call the getter and setter)
WaterLevel WL = WaterLevel::High_Level;
uint8_t WL_Changed = 0;

// This event is called when the water level changes, to add the functionalities required here.
void OnChange(const WaterLevel &newWaterLevel){
    
}

void setWaterLevel(const WaterLevel& newWaterLevel){
    if (WL != newWaterLevel){
        WL = newWaterLevel;
        OnChange(newWaterLevel);
        WL_Changed = 1;
    }
}

WaterLevel getWaterLevel(){
    return WL;
}

String getWaterLevelAsString() {
    if (WL == WaterLevel::High_Level) return "High_Level";
    else if (WL == WaterLevel::Mid_Level) return "Mid_Level";
    else if (WL == WaterLevel::Low_Level) return "Low_Level";
    else if (WL == WaterLevel::VeryLow_Level) return "VeryLow_Level";
}

// This function has to be called in the main loop of the Arduino
void WaterLevelLoop(){
    // update the values of the water level
    WLS_Level1->update();
    WLS_Level2->update();
    WLS_Level3->update();

    if (WLS_Level1->getState() == LOW){
        setWaterLevel(WaterLevel::VeryLow_Level);
    }
    else if (WLS_Level2->getState() == LOW && WLS_Level1->getState() == HIGH){
        setWaterLevel(WaterLevel::Low_Level);
    }
    else if (WLS_Level3->getState() == LOW && WLS_Level2->getState() == HIGH){
        setWaterLevel(WaterLevel::Mid_Level);
    }
    else if (WLS_Level3->getState() == HIGH){
        setWaterLevel(WaterLevel::High_Level);
    }
}
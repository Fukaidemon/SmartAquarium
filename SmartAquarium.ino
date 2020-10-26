#pragma once

#include <Arduino.h>
#include "include/ConnectivityManager.h"
#include "include/TemperatureSensor.h"
#include "WaterLevelManager.h"

TemperatureSensor* TS = new TemperatureSensor(A0, .3f);
ConnectivityManager* CM = new ConnectivityManager("TOPNETE136FE54", "F57B95D1E6");

void ManageWaterLevelData(const uint8_t& sendMQTT, const uint8_t& debugSerial){
  // Checks if the Water level has changed
  if(WL_Changed){
    // Sends an MQTT message
    if (sendMQTT)
      CM->sendMQTTMessage("AQUAIOT", getWaterLevelAsString().c_str());
    // Sends on the serial
    if (debugSerial){
      Serial.print("Water level changed to : ");
      Serial.print(getWaterLevelAsString());
      Serial.println();
    }
    WL_Changed = false; // ReInitialize the status for an upcoming access
  }
}

void TemperatureLoop(const uint8_t& sendMQTT, const uint8_t& debugSerial){
    float oldValue = TS->getTempInCelcius();
    TS->update();
    float newValue = TS->getTempInCelcius();
    if ( abs(oldValue - newValue) > TS->thershold ){
        // Sends an MQTT message
      if (sendMQTT)
        CM->sendMQTTMessage("AQUAIOT", String(newValue).c_str());
      // Sends on the serial
      if (debugSerial){
        Serial.print("Temperature : ");
        Serial.print(String(newValue));
        Serial.println();
      }
    }
}

void setup() {
  // Init the Serial
  Serial.begin(115200);
  //Init the Connectivity Manager
  CM->connect();
  // 0.1 sec delay
  delay(100);
  // Connect to the MQTT server
  CM->connectToMQTT("AQUAIOT");
}

void loop() {
  // Water level sensors loop
  WaterLevelLoop();
  // Water level sensors Display/Send Data
  ManageWaterLevelData(true, true);
  // Temperature Sensor loop and Display/Send Data
  TemperatureLoop(true, true);  
}

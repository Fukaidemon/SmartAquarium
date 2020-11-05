#pragma once

#include <Arduino.h>
#include "include/ConnectivityManager.h"
#include "include/TemperatureSensor.h"
#include "WaterLevelManager.h"
#include "TemperatureManager.h"

ConnectivityManager* CM = new ConnectivityManager("TOPNETE136FE54", "F57B95D1E6");

void ManageWaterLevelData(const uint8_t& sendMQTT, const uint8_t& debugSerial){
  // Checks if the Water level has changed
  if(WL_Changed == 1){
    // Sends an MQTT message
    if (sendMQTT)
      CM->sendMQTTMessage("AQUAIOTSLEAM2020", getWaterLevelAsString().c_str());
    // Sends on the serial
    if (debugSerial){
      Serial.print("Water level changed to : ");
      Serial.print(getWaterLevelAsString());
      Serial.println();
    }
    WL_Changed = 0; // ReInitialize the status for an upcoming access
  }
}

void ManageTemperatureData(const uint8_t& sendMQTT, const uint8_t& debugSerial){
    if (TMP_Changed == 1){
      // Sends an MQTT message
      if (sendMQTT)
        CM->sendMQTTMessage("AQUAIOTSLEAM2020", String(temperature).c_str());
      // Sends on the serial
      if (debugSerial){
        Serial.print("Temperature : ");
        Serial.print(String(temperature));
        Serial.println();
      }
      TMP_Changed = 0;
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
  // CM->connectToMQTT("AQUAIOTSLEAM2020");
}

void loop() {

  //Init the Connectivity Manager
  CM->connect();
  // This is called due to some connectivity issues with the server
  CM->connectToMQTT("AQUAIOTSLEAM2020");

  // Water level sensors loop
  WaterLevelLoop();
  // Water level sensors Display/Send Data
  ManageWaterLevelData(true, true);
  // Temperature sensor loop
  TemperatureLoop();
  // Temperature sensor Display/Send Data 
  ManageTemperatureData(true, true);

  ESP.deepSleep(30e6);
}

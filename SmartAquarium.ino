#include <Arduino.h>
#include "include/ConnectivityManager.h"
#include "include/TemperatureSensor.h"
#include "WaterLevelManager.h"

TemperatureSensor* TS = new TemperatureSensor(A0);
ConnectivityManager* CM = new ConnectivityManager();

void ManageWaterLevelData(const uint8_t& sendMQTT, const uint8_t& debugSerial){
  if(WL_Changed){
    if (sendMQTT)
      CM->sendMQTTMessage("IOT_AQUA", getWaterLevelAsString().c_str());
    if (debugSerial){
      Serial.print("Water level changed to : ");
      Serial.print(getWaterLevelAsString());
      Serial.println();
    }
  }
}

void setup() {
  CM->connect();
  CM->runServer();
  CM->connectToMQTT("esp32", "IOT_AQUA");
}

void loop() {

  WaterLevelLoop();
  TS->update();

  Serial.print("Temperature : ");
  Serial.print(TS->getTempInCelcius());
  Serial.println();
  CM->sendMQTTMessage("IOT_AQUA", String(TS->getTempInCelcius()).c_str());
  
}


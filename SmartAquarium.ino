#include <Arduino.h>
#include "include/ConnectivityManager.h"
#include "include/TemperatureSensor.h"
#include "WaterLevelManager.h"

TemperatureSensor* TS = new TemperatureSensor(A0);
ConnectivityManager* CM = new ConnectivityManager();

void ManageWaterLevelData(const uint8_t& sendMQTT, const uint8_t& debugSerial){
  // Checks if the Water level has changed
  if(WL_Changed){
    // Sends an MQTT message
    if (sendMQTT)
      CM->sendMQTTMessage("IOT_AQUA", getWaterLevelAsString().c_str());
    // Sends on the serial
    if (debugSerial){
      Serial.print("Water level changed to : ");
      Serial.print(getWaterLevelAsString());
      Serial.println();
    }
    WL_Changed = false; // ReInitialize the status for an upcoming access
  }
}

void setup() {

  // Init the Serial
  Serial.begin(115200);

  //Init the Connectivity Manager
  CM->connect();
  CM->runServer();
  CM->connectToMQTT("esp32", "IOT_AQUA");

}

void loop() {

  // Water level sensors loop
  WaterLevelLoop();

  // Temperature Sensor loop
  TS->update();
  
  // Displays the Data of the Temperature 
  // TODO : Temperature sends data only when going above or lower a threshold compared to the last value sent
  Serial.print("Temperature : ");
  Serial.print(TS->getTempInCelcius());
  Serial.println();
  CM->sendMQTTMessage("IOT_AQUA", String(TS->getTempInCelcius()).c_str());
}


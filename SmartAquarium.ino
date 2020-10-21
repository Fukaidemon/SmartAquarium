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
      CM->sendMQTTMessage("IOTAQUA", getWaterLevelAsString().c_str());
    // Sends on the serial
    if (debugSerial){
      Serial.print("Water level changed to : ");
      Serial.print(getWaterLevelAsString());
      Serial.println();
    }
    WL_Changed = false; // ReInitialize the status for an upcoming access
  }
}

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

void setup() {

  // Init the Serial
  Serial.begin(115200);

  //Init the Connectivity Manager
  CM->connect();

  delay(500);

  // Generate client name based on MAC address and last 8 bits of microsecond counter
  String clientName;
  clientName += "esp8266-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);

  // Connect to the MQTT server
  CM->connectToMQTT(clientName, "IOTAQUA");
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


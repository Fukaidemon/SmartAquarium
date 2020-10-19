#include <Arduino.h>
#include "include/ConnectivityManager.h"
#include "include/WaterLevelSensor.h"
#include "include/TemperatureSensor.h"

ConnectivityManager* CM;

WaterLevelSensor* WLS_Level1;
WaterLevelSensor* WLS_Level2;
WaterLevelSensor* WLS_Level3;

TemperatureSensor* TS;

// enum WaterLevel{
//   High,
//   Mid,
//   Low
// }

void setup() {

  CM = new ConnectivityManager();
  CM->connect();
  CM->runServer();
  CM->connectToMQTT("esp32", "IOT_AQUA");

  WLS_Level1 = new WaterLevelSensor(8); // 8 is the pin connected to the Water Level Sensor
  WLS_Level2 = new WaterLevelSensor(9); 
  WLS_Level3 = new WaterLevelSensor(10); 

  TS = new TemperatureSensor(A0);
}

void loop() {
  
  WLS_Level1->update();
  WLS_Level2->update();
  WLS_Level3->update();

  TS->update();

  Serial.print("Temperature : ");
  Serial.print(TS->getTempInCelcius());
  Serial.println();
  // CM->sendMQTTMessage("IOT_AQUA", String(TS->getTempInCelcius()));
  
  Serial.print("WaterLevel 1 : ");
  Serial.print(WLS_Level1->getState());
  Serial.println();

  Serial.print("WaterLevel 2 : ");
  Serial.print(WLS_Level2->getState());
  Serial.println();

  Serial.print("WaterLevel 3 : ");
  Serial.print(WLS_Level3->getState());
  Serial.println();

}


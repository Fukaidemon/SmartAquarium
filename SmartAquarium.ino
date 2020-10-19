#include "include/ConnectivityManager.h"
#include "include/WaterLevelSensor.h"
#include "include/TemperatureSensor.h"

ConnectivityManager* CM;

WaterLevelSensor* WLS_Level1;
WaterLevelSensor* WLS_Level2;
WaterLevelSensor* WLS_Level3;
WaterLevelSensor* WLS_Level4;

TemperatureSensor* TS;

void setup() {

  CM = new ConnectivityManager();
  CM->connect();
  CM->runServer();

  WLS_Level1 = new WaterLevelSensor(8); // 8 is the pin connected to the Water Level Sensor
  WLS_Level2 = new WaterLevelSensor(9); 
  WLS_Level3 = new WaterLevelSensor(10); 
  WLS_Level4 = new WaterLevelSensor(11); 
  
  TS = new TemperatureSensor(A0);
}

void loop() {
  
  WLS_Level1->update();
  WLS_Level2->update();
  WLS_Level3->update();
  WLS_Level4->update();

  TS->update();
}
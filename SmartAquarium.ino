#include "include/ConnectivityManager.h"
#include "include/WaterLevelSensor.h"

WaterLevelSensor* WLS;
ConnectivityManager* CM;

void setup() {

  CM = new ConnectivityManager();
  CM->connect();
  CM->runServer();

  WLS = new WaterLevelSensor(8); // 8 is the pin connected to the Water Level Sensor
  
}

void loop() {
  
  WLS->update();

}
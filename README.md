# SmartAquarium
SmartAquarium is an academic project for a Smart Aquarium (IOT) using ESP3266 (Node MCU) as a base microcontroller.

## Functionalities
- Water Oxygenating
- Keeping track of the Temperature (DS18B20 Water-Proof Temperature Sensor Probe)
- Keeping track of the water level
- Transmitting everything via MQTT to the Node-red server

## Current implementations
The Node MCU will have 1 Temperature sensor and 3 water sensors connected to it.
### Sensors
The temperature sensor is meant to mesure the temperature of the water by sending an analogical value to the Arduino.
The 3 water sensors are put one on top of the other in order to define 4 water levels :
- Very low level (almost empty) (lower sensor isn't in the water)
- Low level (lower sensor is in the water, the middle sensor isn't)
- mid level (middle sensor is in the water, high sensor isn't)
- high level (higher sensor is in the water)
### Data
Now that we have all the data from the sensors, we are going to send it via MQTT to our Node-Red Flow.
The data is going to be inserted in the Database.
The data is also going to be on a gauge that shows the current value and a graph that parses the database data and displays how the state of the water level and temperature are since X time.

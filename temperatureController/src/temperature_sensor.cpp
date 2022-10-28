/*Temperature Sensor*/
#include "temperature_sensor.h"

/*	Init Sensor
*	Init sequence of sensor
*/
bool TemperatureSensor::initSensor(void) {
    bool status = false;

    //Init sensor according to configuration
    status = true;
    
    return status;
}

/*	Read Sensor
*	Reads the raw ADC value coming from the sensor and converts it to temperature.
*/
int TemperatureSensor::readSensor(void) {
    int temperature = 0;

    //Read Sensor
    temperature = 25;

    return temperature;
}
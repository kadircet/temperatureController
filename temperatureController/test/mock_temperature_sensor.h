#ifndef MOCK_TEMPERATURE_SENSOR_H
#define MOCK_TEMPERATURE_SENSOR_H

#include <iostream>
#include <memory>
#include "gmock/gmock.h"
#include "../src/temperature_sensor.h"

using namespace std;

class MockTemperatureSensor {
    public:	
    MockTemperatureSensor(unique_ptr<TemperatureSensor> upTempS) : upTempSensor(move(upTempS)) {}
	
    //MOCK_METHOD(int, readSensor, ());

    private:
    unique_ptr<TemperatureSensor> upTempSensor;
    protected:
};

#endif /* MOCK_TEMPERATURE_SENSOR_H */
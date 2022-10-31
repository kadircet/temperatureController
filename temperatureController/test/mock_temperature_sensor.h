#ifndef MOCK_TEMPERATURE_SENSOR_H
#define MOCK_TEMPERATURE_SENSOR_H

#include <iostream>
#include <memory>
#include "gmock/gmock.h"
#include "../src/temperature_sensor.h"

using namespace std;

class MockTemperatureSensor : public TemperatureSensor {
    public:	
	
    //MOCK_METHOD(int, readSensor, ());

    private:
    protected:
};

#endif /* MOCK_TEMPERATURE_SENSOR_H */
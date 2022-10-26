#ifndef MOCK_TEMPERATURE_SENSOR_H
#define MOCK_TEMPERATURE_SENSOR_H

#include <iostream>
#include "gmock/gmock.h"
#include "temperature_sensor.h"

class MockTemperatureSensor : public TemperatureSensor {
    public:
    MOCK_METHOD(bool, initSensor, (), (override));
    //MOCK_METHOD(uint16_t, readSensor, (), (override));

    private:
    protected:
};

#endif /* MOCK_TEMPERATURE_SENSOR_H */
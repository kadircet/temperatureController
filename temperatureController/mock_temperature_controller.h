#ifndef MOCK_TEMPERATURE_CONTROLLER_H
#define MOCK_TEMPERATURE_CONTROLLER_H

#include <iostream>
#include "gmock/gmock.h"
#include "temperature_controller.h"
#include "temperature_sensor.h"
#include "fan_speed.h"

class MockTemperatureController : public TemperatureController {
    public:
	MockTemperatureController(FanSpeed* const pFanSpeed, TemperatureSensor* const pTemperatureSensor) : TemperatureController(pFanSpeed, pTemperatureSensor) {}
	
//    MOCK_METHOD(void, setSetTemperature, (uint16_t), (override));
//    MOCK_METHOD(uint16_t, getSetTemperature, (), (override));
	
    private:
		stUserSettings userSettings; 
		TemperatureSensor* temperatureSensor;
		FanSpeed* fanSpeed;
    protected:
};

#endif /* MOCK_TEMPERATURE_CONTROLLER_H */
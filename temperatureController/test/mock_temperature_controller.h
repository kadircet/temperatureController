#ifndef MOCK_TEMPERATURE_CONTROLLER_H
#define MOCK_TEMPERATURE_CONTROLLER_H

#include <iostream>
#include <memory>
#include "gmock/gmock.h"
#include "../src/temperature_controller.h"
#include "../src/temperature_sensor.h"
#include "../src/fan_speed.h"

using namespace std;

class MockTemperatureController : public TemperatureController {
    public:
	MockTemperatureController(const shared_ptr<FanSpeed> &pFanSpeed, const shared_ptr<TemperatureSensor> &pTemperatureSensor) : TemperatureController(pFanSpeed, pTemperatureSensor) {}

    private:
		stUserSettings userSettings; 
		shared_ptr<TemperatureSensor> temperatureSensor;
		shared_ptr<FanSpeed> fanSpeed;
    protected:
};

#endif /* MOCK_TEMPERATURE_CONTROLLER_H */
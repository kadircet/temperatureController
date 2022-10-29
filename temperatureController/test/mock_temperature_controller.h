#ifndef MOCK_TEMPERATURE_CONTROLLER_H
#define MOCK_TEMPERATURE_CONTROLLER_H

#include <iostream>
#include <memory>
#include "gmock/gmock.h"
#include "../src/temperature_controller.h"
#include "../src/temperature_sensor.h"
#include "../src/fan_speed.h"
#include "../test/mock_fan_speed.h"
#include "../test/mock_temperature_sensor.h"

using namespace std;
#if 0
class MockTemperatureController {
    public:	
    MockTemperatureController(unique_ptr<TemperatureController> upTempCtrl) {
		
        unique_ptr<MockFanSpeed> upFanS = std::make_unique<MockFanSpeed>();
        unique_ptr<MockTemperatureSensor> upTempS = std::make_unique<MockTemperatureSensor>();
		
		upTempControl(move(upFanS), move(upTempS));
	}
		
    private:
	stUserSettings userSettings; 
    unique_ptr<TemperatureController> upTempControl;
    protected:
};


class MockTemperatureController : public TemperatureController {
    public:	
    MockTemperatureController(unique_ptr<TemperatureController> upTempCont) : upTempCtl(move(upTempCont)) {}
	
	
    MOCK_METHOD(void, setSetTemperature, (int), (override));
    MOCK_METHOD(int, getSetTemperature, (), (override));

    private:
    unique_ptr<TemperatureController> upTempCtl;
    protected:
};



class MockTemperatureController : public TemperatureController {
    public:	
    MockTemperatureController(	unique_ptr<TemperatureController> upTempCont, 
								unique_ptr<FanSpeed> upFan,
								unique_ptr<TemperatureSensor> upSens) 
		: upTempCtl(move(upTempCont)) , TemperatureController(move(upFan), move(upSens)) {}
	
	
	
    MOCK_METHOD(void, setSetTemperature, (int), (override));
    MOCK_METHOD(int, getSetTemperature, (), (override));

    private:
    unique_ptr<TemperatureController> upTempCtl;
    protected:
};




class MockTemperatureController : public TemperatureController {
    public:	
    MockTemperatureController(	unique_ptr<FanSpeed> upFan,
								unique_ptr<TemperatureSensor> upSens) 
		: TemperatureController(move(upFan), move(upSens)) {}
	
	
	
    MOCK_METHOD(void, setSetTemperature, (int), (override));
    MOCK_METHOD(int, getSetTemperature, (), (override));
	
	
    unique_ptr<TemperatureController> upTempCtl;

    private:
    protected:
};


#endif

class MockTemperatureController : public TemperatureController {
    public:	
    MockTemperatureController(unique_ptr<TemperatureController> upTempCont) : upTempCtl(move(upTempCont)) {}
	
    MOCK_METHOD(void, setSetTemperature, (int), (override));
    MOCK_METHOD(int, getSetTemperature, (), (override));

    private:
    unique_ptr<TemperatureController> upTempCtl;
    protected:
};


#endif /* MOCK_TEMPERATURE_CONTROLLER_H */
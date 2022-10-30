#ifndef MOCK_FAN_SPEED_H
#define MOCK_FAN_SPEED_H

#include <iostream>
#include <memory>
#include "gmock/gmock.h"
#include "../src/fan_speed.h"

using namespace std;

class MockFanSpeed {
    public:	
    MockFanSpeed(unique_ptr<FanSpeed> upFanS) : upFanSpeed(move(upFanS)) {}
	
    MOCK_METHOD(eFanSpeedSettings, getFanSpeed, ());

    private:
    unique_ptr<FanSpeed> upFanSpeed;
    protected:
};

#endif /* MOCK_FAN_SPEED_H */
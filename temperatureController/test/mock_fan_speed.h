#ifndef MOCK_FAN_SPEED_H
#define MOCK_FAN_SPEED_H

#include <iostream>
#include "gmock/gmock.h"
#include "../src/fan_speed.h"

class MockFanSpeed {
    public:	
    MockFanSpeed(unique_ptr<FanSpeed> upFanS) : upFanSpeed(move(upFanS)) {}

    private:
    unique_ptr<FanSpeed> upFanSpeed;
    protected:
};

#endif /* MOCK_FAN_SPEED_H */
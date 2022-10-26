#ifndef MOCK_FAN_SPEED_H
#define MOCK_FAN_SPEED_H

#include <iostream>
#include "gmock/gmock.h"
#include "fan_speed.h"

class MockFanSpeed : public FanSpeed {
    public:
    //MOCK_METHOD(void, setFanSpeed, (eCurrentStatus, uint16_t, uint16_t), (override));
    //MOCK_METHOD(eFanSpeedSettings, getFanSpeed, (), (override));

    private:
    protected:
};

#endif /* MOCK_FAN_SPEED_H */
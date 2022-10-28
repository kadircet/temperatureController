#include "temperature_controller.h"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    shared_ptr<TemperatureSensor> pTemperatureSensor(new TemperatureSensor());
    shared_ptr<FanSpeed> pFanSpeed(new FanSpeed());

    TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);

    while(true)
    {
        homeTempController.mainController();
    }
}
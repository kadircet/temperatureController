#include "../src/machine.h"
#include "../src/temperature_controller.h"
#include "mock_fan_speed.h"
#include "mock_temperature_sensor.h"
#include "gtest/gtest.h"

/*	Status Control & Fan Speed Control
 *	Since sensor implementation does not exist
 *	Fixed room temperature are read from sensor as 25
 *	Desired temperature changes
 *	Random tests are conducted.
 */
TEST(Air_Conditioner_Test,
     WhenSetTemperatureEqualsRoomTemperature_ThenReturnSystemOff) {

  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto fanptr = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
  eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;

  // Check normal conditions
  homeTempController.setSetTemperature(25);
  homeTempController.mainController();

  readFanSpeed = fanptr->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);
}

#include "gtest/gtest.h"
#include "../src/temperature_controller.h"
#include "../src/machine.h"
#include "../test/mock_fan_speed.h"
#include "../test/mock_temperature_sensor.h"

/*	Set Temperature
*	Desired temperature coming from the user is controlled.
*/
TEST(Air_Conditioner_Test, WhenSetTemperatureIsBetweenMaxAndMin_ThenReturnDesiredTemperature) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	int userTemp = 0;
	
	//Check normal conditions
	homeTempController.setSetTemperature(25);
	userTemp = homeTempController.getSetTemperature();
	EXPECT_EQ(25, userTemp);
	
	homeTempController.setSetTemperature(0);
	userTemp = homeTempController.getSetTemperature();
	EXPECT_EQ(0, userTemp);
	
	homeTempController.setSetTemperature(-15);
	userTemp = homeTempController.getSetTemperature();
	EXPECT_EQ(-15, userTemp);
}

TEST(Air_Conditioner_Test, WhenSetTemperatureAboveMax_ThenReturnMax) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	int userTemp = 0;
	
	//Check above max
	homeTempController.setSetTemperature(150);
	userTemp = homeTempController.getSetTemperature();
	EXPECT_EQ(MAX_TEMPERATURE, userTemp);
}

TEST(Air_Conditioner_Test, WhenSetTemperatureBelowMin_ThenReturnMin) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	int userTemp = 0;
	
	//Check below min
	homeTempController.setSetTemperature(-75);
	userTemp = homeTempController.getSetTemperature();
	EXPECT_EQ(MIN_TEMPERATURE, userTemp);
}

/*	Status Control & Fan Speed Control
*	Since sensor implementation does not exist
*	Fixed room temperature are read from sensor as 25
*	Desired temperature changes
*	Random tests are conducted.
*/
TEST(Air_Conditioner_Test, WhenSetTemperatureEqualsRoomTemperature_ThenReturnSystemOff) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
	eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;
	
	//Check normal conditions
	homeTempController.setSetTemperature(25);
	homeTempController.mainController();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);
}

TEST(Air_Conditioner_Test, WhenSetTemperatureHigherThanRoomTemperature_ThenReturnHeating) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
	eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;
	
	//Check normal conditions
	homeTempController.setSetTemperature(25);
	homeTempController.mainController();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);
	
	homeTempController.setSetTemperature(26);
	homeTempController.mainController();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
	
	homeTempController.setSetTemperature(29);
	homeTempController.mainController();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_MID, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
	
	//Check above max
	homeTempController.setSetTemperature(150);
	homeTempController.mainController();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
}

TEST(Air_Conditioner_Test, WhenSetTemperatureLowerThanRoomTemperature_ThenReturnCooling) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
	eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;
	
	//Check normal conditions
	homeTempController.setSetTemperature(25);
	homeTempController.mainController();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);
	
	homeTempController.setSetTemperature(0);
	homeTempController.mainController();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
	
	//Check minus
	homeTempController.setSetTemperature(-45);
	homeTempController.mainController();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
}

/*	Status Control & Fan Speed Control
*	Since sensor implementation does not exist
*	Room temperature set by tester
*	Constant desired temperature
*	Random tests are conducted.
*/
TEST(Air_Conditioner_Test, WhenRoomTemperatureIncreasedContinuosly_ThenReturnCooling) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
	eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;
	
	//Random tests with fixed set temperature and changing room temperature
	homeTempController.setSetTemperature(25);
	
	//Case 1
	homeTempController.setRoomTemperature(25);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);
	
	//Case 2
	homeTempController.setRoomTemperature(26);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
	
	//Case 3
	homeTempController.setRoomTemperature(27);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_MID, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
	
	//Case 4
	homeTempController.setRoomTemperature(30);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
}

TEST(Air_Conditioner_Test, WhenRoomTemperatureDecreasedContinuosly_ThenReturnHeating) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
	eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;
	
	//Random tests with fixed set temperature and changing room temperature
	homeTempController.setSetTemperature(25);
	
	//Case 1
	homeTempController.setRoomTemperature(25);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);
	
	//Case 2
	homeTempController.setRoomTemperature(24);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
	
	//Case 3
	homeTempController.setRoomTemperature(23);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_MID, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
	
	//Case 4
	homeTempController.setRoomTemperature(20);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
}

/*	Status Control & Fan Speed Control
*	Since sensor implementation does not exist
*	Room temperature set by tester
*	Constant desired temperature
*	Checks system status in case of temperature fluctuations around desired temperature.
*	Random tests are conducted.
*/
TEST(Air_Conditioner_Test, WhenRoomTemperatureChangesRandomly_ThenCheckStatus) {
    shared_ptr<MockTemperatureSensor> pTemperatureSensor(new MockTemperatureSensor());
    shared_ptr<MockFanSpeed> pFanSpeed(new MockFanSpeed());
	
	TemperatureController homeTempController(pFanSpeed, pTemperatureSensor);
	
	eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
	eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;
	
	//Random tests with fixed set temperature and changing room temperature
	homeTempController.setSetTemperature(25);
	
	//Case 1
	homeTempController.setRoomTemperature(25);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);
	
	//Case 2
	homeTempController.setRoomTemperature(26);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
	
	//Case 3
	homeTempController.setRoomTemperature(25);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
	
	//Case 4
	homeTempController.setRoomTemperature(24);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
	
	//Case 5
	homeTempController.setRoomTemperature(25);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
	
	//Case 6
	homeTempController.setRoomTemperature(26);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
	
	//Case 7
	homeTempController.setRoomTemperature(27);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_MID, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
	
	//Case 8
	homeTempController.setRoomTemperature(30);
	homeTempController.controlFan();
	
	readFanSpeed = pFanSpeed->getFanSpeed();
	EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);
	
	currentStatus = homeTempController.getCurrentStatus();
	EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
}
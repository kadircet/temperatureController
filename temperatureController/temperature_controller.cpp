/*Temperature Controller*/
#include "temperature_controller.h"

/*	Main Controller
*	Should be called periodically.
*	Reads the current room temperature, controls fan speed.
*/
void TemperatureController::mainController(void) {
	getRoomTemperature();
	controlFan();
}

/*	Fan Controller
*	Compares the current room temperature with desired temperature and sets the state.
*/
void TemperatureController::controlFan(void) {
	if(currentStatus == HEATING_IN_PROGRESS) {
		if(roomTemp >= (userSettings.setTemperature + DEFAULT_TEMPERATURE_HYSTERESIS)) {
			currentStatus = COOLING_IN_PROGRESS;
		}
		else {
			currentStatus = HEATING_IN_PROGRESS;
		}
	}
	else if(currentStatus == COOLING_IN_PROGRESS) {
		if(roomTemp <= (userSettings.setTemperature - DEFAULT_TEMPERATURE_HYSTERESIS)) {
			currentStatus = HEATING_IN_PROGRESS;
		}
		else {
			currentStatus = COOLING_IN_PROGRESS;
		}
	}
	else {
		if(roomTemp > userSettings.setTemperature) {
			currentStatus = COOLING_IN_PROGRESS;
		}
		else if(roomTemp < userSettings.setTemperature) {
			currentStatus = HEATING_IN_PROGRESS;
		}
		else {
			currentStatus = SYSTEM_OFF;
		}
	}
	
	fanSpeed->setFanSpeed(currentStatus, roomTemp, userSettings.setTemperature);
}

/*	Set Set Temperature
*	Checks the temperature coming from the user according to limits and sets it. 
*/
void TemperatureController::setSetTemperature(int temp) {
	if(temp > MAX_TEMPERATURE) {
		userSettings.setTemperature = MAX_TEMPERATURE;
	}
	else if(temp < MIN_TEMPERATURE) {
		userSettings.setTemperature = MIN_TEMPERATURE;
	}
	else {
		userSettings.setTemperature = temp;
	}
}
  
/*	Get Set Temperature
*	Returns the desired temperature coming from the user. 
*/  
int TemperatureController::getSetTemperature(void) {
	return userSettings.setTemperature;
}

/*	Set Room Temperature
*	Used for test purposes. It sets the room temperature coming from the tester.
*/
void TemperatureController::setRoomTemperature(int temp) {
	roomTemp = temp;
}
 
/*	Get Room Temperature
*	Reads the temperature sensor.
*/ 
void TemperatureController::getRoomTemperature(void) {
	roomTemp = temperatureSensor->readSensor();
}
 
/*	Get Current Status
*	Returns the current status of system.
*/    
eCurrentStatus TemperatureController::getCurrentStatus(void) {
	return currentStatus;
}
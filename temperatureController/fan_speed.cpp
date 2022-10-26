/*Fan Speed*/
#include "fan_speed.h"

/*	Set Fan Speed
*	Fan speed adjusted according to diffence between set temperature and room temperature.
*	When the temperature difference decreases, fan speed also decreases.
*/
void FanSpeed::setFanSpeed(eCurrentStatus currentStatus, int currentTemperature, int setTemperature) {
	if(currentStatus != SYSTEM_OFF) {
		if((currentTemperature < setTemperature + eFAN_TEMP_LOW) &&
			(currentTemperature > setTemperature - eFAN_TEMP_LOW)) {
			fanSpeed = eFAN_SPEED_LOW;
		}
		else if((currentTemperature < setTemperature + eFAN_TEMP_MID) &&
				(currentTemperature > setTemperature - eFAN_TEMP_MID)) {
			fanSpeed = eFAN_SPEED_MID;
		}
		else {
			fanSpeed = eFAN_SPEED_HIGH;
		}
	}
	else {
		fanSpeed = eFAN_SPEED_OFF;
	}
}

/*	Get Fan Speed	*/
eFanSpeedSettings FanSpeed::getFanSpeed(void) { 
	return fanSpeed;
}
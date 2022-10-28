#ifndef TEMPERATURE_CONTROLLER_H
#define TEMPERATURE_CONTROLLER_H

#include <iostream>
#include <memory>
#include "machine.h"
#include "temperature_sensor.h"
#include "fan_speed.h"

using namespace std;

struct stUserSettings {
  int setTemperature;
  uint16_t temperatureHysteresis;
};

class TemperatureController {
    public:

    //Default Constructor
    TemperatureController(const shared_ptr<FanSpeed> &pFanSpeed, const shared_ptr<TemperatureSensor> &pTemperatureSensor) : temperatureSensor(pTemperatureSensor), fanSpeed(pFanSpeed) {
		if(temperatureSensor == nullptr){
            throw std::invalid_argument("temperatureSensor must not be null");
        }
		if(fanSpeed == nullptr){
            throw std::invalid_argument("fanSpeed must not be null");
        }
        userSettings.setTemperature = DEFAULT_TEMPERATURE;
        userSettings.temperatureHysteresis = DEFAULT_TEMPERATURE_HYSTERESIS;
    }

    //Destructor
    virtual ~TemperatureController() {
        ;
    }

    /**
     * @brief: Main Controller Algorithm
     * @param:
     * @return:  
     */ 
    virtual void mainController(void);

    /**
     * @brief: Compare temperature of room and set temperature and control fan
     * @param:
     * @return:  
     */ 
    virtual void controlFan(void);
    
    /**
     * @brief: Set Set Temperature from the user
     * @param: temp (Desired temperature coming from the user)
     * @return:  
     */ 
    virtual void setSetTemperature(int temp);
    
    /**
     * @brief: Get Set Temperature from the user
     * @param:
     * @return:  Desired temperature of user
     */ 
    virtual int getSetTemperature(void);
    
    /**
     * @brief: For test purposes only! Set Room Temperature coming from the tester
     * @param: temp (Desired temperature coming from the tester)
     * @return:  
     */ 
    virtual void setRoomTemperature(int temp);
    
    /**
     * @brief: Get Room Temperature from the sensor
     * @param:
     * @return:
     */ 
    virtual void getRoomTemperature(void);
    
    /**
     * @brief: Get Status
     * @param:
     * @return:  Status (Heating, Cooling or OFF)
     */ 
    virtual eCurrentStatus getCurrentStatus(void);

    private:
		stUserSettings userSettings;
		shared_ptr<TemperatureSensor> temperatureSensor;
		shared_ptr<FanSpeed> fanSpeed;
		int roomTemp;
		eCurrentStatus currentStatus;
		
    protected:
};

#endif /* TEMPERATURE_CONTROLLER_H */
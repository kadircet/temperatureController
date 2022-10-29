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
    TemperatureController(unique_ptr<FanSpeed> upFanSpeed, unique_ptr<TemperatureSensor> upTemperatureSensor)
		: upSensor(move(upTemperatureSensor)), upFan(move(upFanSpeed)) {
        userSettings.setTemperature = DEFAULT_TEMPERATURE;
        userSettings.temperatureHysteresis = DEFAULT_TEMPERATURE_HYSTERESIS;
    }
/*
    //Destructor
    virtual ~TemperatureController() {
        ;
    }
*/
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
		unique_ptr<FanSpeed> upFan;
		unique_ptr<TemperatureSensor> upSensor;
		int roomTemp;
		eCurrentStatus currentStatus;
		
    protected:
};

#endif /* TEMPERATURE_CONTROLLER_H */
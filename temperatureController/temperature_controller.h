#ifndef TEMPERATURE_CONTROLLER_H
#define TEMPERATURE_CONTROLLER_H

#include <iostream>
#include "machine.h"
#include "temperature_sensor.h"
#include "fan_speed.h"

struct stUserSettings {
  int setTemperature;
  uint16_t temperatureHysteresis;
};

class TemperatureController : public TemperatureSensor , public FanSpeed {
    public:

    //Default Constructor
    TemperatureController(FanSpeed* const pFanSpeed, TemperatureSensor* const pTemperatureSensor) : temperatureSensor(pTemperatureSensor), fanSpeed(pFanSpeed) {
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
      TemperatureSensor* temperatureSensor;
      FanSpeed* fanSpeed;
      int roomTemp;
      eCurrentStatus currentStatus;
		
    protected:
};

#endif /* TEMPERATURE_CONTROLLER_H */
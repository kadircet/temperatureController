#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <iostream>

class TemperatureSensor {
    public:

    //Default Constructor
    TemperatureSensor() {
        ;
    }

    //Destructor
    ~TemperatureSensor() {
        ;
    }

    /**
     * @brief: Initialization of Sensor
     * @param: 
     * @return: status (Success, Fail) 
     */ 
    virtual bool initSensor(void);

    /**
     * @brief: Reading of Sensor
     * @param: 
     * @return: Temperature value coming from the sensor 
     */ 
    virtual int readSensor(void);

    private:
    protected:
};

#endif /* TEMPERATURE_SENSOR_H */
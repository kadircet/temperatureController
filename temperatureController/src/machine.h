#ifndef MACHINE_H
#define MACHINE_H

enum class eCurrentStatus { SYSTEM_OFF = 0, 
							COOLING_IN_PROGRESS, 
							HEATING_IN_PROGRESS};

#define DEFAULT_TEMPERATURE             25
#define MAX_TEMPERATURE                 30
#define MIN_TEMPERATURE                 -30
#define DEFAULT_TEMPERATURE_HYSTERESIS  1

#endif
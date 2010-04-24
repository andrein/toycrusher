#ifndef SENSORS_H
#define SENSORS_H

#include "global.h"

typedef enum{
  REAR_LEFT   = 2,
  FRONT_RIGHT = 4,
  FRONT_LEFT  = 8,
  REAR_RIGHT  = 16
}line_sensor;

typedef enum{
  FRONT_TARGET_LEFT  = 32,
  FRONT_TARGET_RIGHT = 64
}front_sensor;

void sensors_setup(void);
int read_adc(uint8_t);
int read_sonar(void);
uint8_t read_line_sensors(void);
uint8_t read_front_sensors(void);
#endif // SENSORS_H

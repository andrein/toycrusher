#ifndef SENSORS_H
#define SENSORS_H

#include "global.h"

typedef enum{
  FRONT_LEFT=1,
  FRONT_RIGHT=2,
  REAR_LEFT=3,
  REAR_RIGHT=4
}line_sensor;

void sensors_setup(void);
int read_adc(uint8_t);
int read_sonar(void);
#endif // SENSORS_H
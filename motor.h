#ifndef MOTOR_H
#define MOTOR_H

#include "global.h"

typedef enum{
  MOTOR_FORWARD,
  MOTOR_REVERSE,
  MOTOR_BRAKE,
  MOTOR_COAST
}motor_command;

typedef enum{
  MOTOR_LEFT,
  MOTOR_RIGHT
}motor_side;

void motor_setup(void);
void motor_set_speed(motor_side, motor_command, uint8_t);

#endif // MOTOR_H

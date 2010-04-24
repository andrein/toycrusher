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

void go_forward(uint8_t);
void go_reverse(uint8_t);
void spin_right(uint8_t);
void spin_left(uint8_t);
void steer_right(uint8_t);
void steer_left(uint8_t);
void brake(void);
#endif // MOTOR_H

#ifndef GLOBAL_H
#define GLOBAL_H

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>

typedef enum{
  STOP=0,
  SEEK,
  TARGET,
  ATTACK,
  EVADE
}robot_state;

#endif // GLOBAL_H

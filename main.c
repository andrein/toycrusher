#include "global.h"

#include "motor.h"
#include "usart.h"
#include "button.h"
#include "sensors.h"

void setup(void){
  motor_setup();
  usart_setup();
  button_setup();
  sensors_setup();
}

int main(void){
  setup();
  uint8_t left, right;

  while (1){
    switch(state){
      case SEEK:
	break;
      case TARGET:
	break;
      case ATTACK:
	break;
      case EVADE:
	break;
      case STOP:
	break;
    }
  }
  return 0;
}

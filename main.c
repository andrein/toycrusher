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
  uint8_t speed;
  while (1){
    speed = read_sonar();
    //motor_set_speed(MOTOR_LEFT, MOTOR_FORWARD, speed);
    _delay_ms(100);
  }
  return 0;
}

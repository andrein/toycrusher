#include "motor.h"

void motor_setup(){
  // left motor
  DDRD |= _BV(DDD5); // PWM 
  DDRC |= _BV(DDC1) | _BV(DDC0); // fwd/rev
  // right motor
  DDRD |= _BV(DDD4); // PWM
  DDRC |= _BV(DDC3) | _BV(DDC2); // fwd/rev
  
  // PWM mode
  TCCR1A |= _BV(WGM10); // Phase Correct Mode, 8-bit precision
  TCCR1B |= _BV(CS11) | _BV(CS10);  // Prescaler = 64, frequency = 490 Hz
  TCCR1A |= _BV(COM1A1) | _BV(COM1A0); // set inverted PWM mode
  TCCR1A |= _BV(COM1B1) | _BV(COM1B0);
  
  // don't start the motors (yet);
  OCR1A = 0;
  OCR1B = 0;
}


void motor_set_speed(motor_side side, motor_command state, uint8_t speed){
  printf("DEBUG: motor_set_speed(): side=%u, state=%u, speed=%u\n", side, state, speed);
  switch(side){
    case MOTOR_LEFT:
      switch (state){
	case MOTOR_FORWARD:
	  PORTC |=  _BV(PC1); // fwd high
	  PORTC &= ~_BV(PC0); // rev low
	  OCR1A = speed;
	  break;
	case MOTOR_REVERSE:
	  PORTC &= ~_BV(PC1); // fwd low
	  PORTC |=  _BV(PC0); // rev high
	  OCR1A = speed;
	  break;
	case MOTOR_BRAKE:
	  PORTC |= _BV(PC1); // fwd high
	  PORTC |= _BV(PC0); // rev high
	  OCR1A = speed;
	  break;
	case MOTOR_COAST:
	  PORTC &= ~_BV(PC1); // fwd low
	  PORTC &= ~_BV(PC0); // rev low
	  OCR1A = 0;
	  break;
      }
      break;
    case MOTOR_RIGHT:
      switch (state){
	case MOTOR_FORWARD:
	  PORTC |=  _BV(PC3); // fwd high
	  PORTC &= ~_BV(PC2); // rev low
	  OCR1B = speed;
	  break;
	case MOTOR_REVERSE:
	  PORTC &= ~_BV(PC3); // fwd low
	  PORTC |=  _BV(PC2); // rev high
	  OCR1B = speed;
	  break;
	case MOTOR_BRAKE:
	  PORTC |= _BV(PC3); // fwd high
	  PORTC |= _BV(PC2); // rev high
	  OCR1B = speed;
	  break;
	case MOTOR_COAST:
	  PORTC &= ~_BV(PC3); // fwd low
	  PORTC &= ~_BV(PC2); // rev low
	  OCR1B = 0;
	  break;
      }
      break;
  }
}

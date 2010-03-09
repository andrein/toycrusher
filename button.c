#include "button.h"
#include "motor.h"

// 62*252 = 15624
// prescaler = 1024

void button_setup(){
  DDRD  &= ~_BV(DDD2); // set PD2/INTO pin as input
  PORTD |= _BV(PD2);   // enable pull-up
  MCUCR |= _BV(ISC01); // Interrupt on falling edge of INT0
  GICR  |= _BV(INT0);  // enable INT0
  sei();
}

ISR(INT0_vect)
{
  GICR &= ~_BV(INT0); // disable INT0 to prevent bouncing
  
  TCCR0 |= _BV(WGM01); // set timer0 in CTC mode
  TIMSK |= _BV(OCIE0); // enable Output Compare Match Interrupt
  TCCR0 |= _BV(CS02) | _BV(CS00); // set prescaler = 1024
  
  OCR0 = 252;
}

int i=0;
ISR(TIMER0_COMP_vect){ 
  if (i>=61*5){
    printf("5s elapsed!\n");
    TIMSK &= ~_BV(OCIE0); // disable Output Compare Match Interrupt
    TCCR0 = 0; //disable timer0
    GICR  |= _BV(INT0);  // re-enable INT0
  }
}
#include "sensors.h"

#define MUX _BV(REFS0) // use AVCC as referecve voltage
#define SONAR_SCALE 100/39 // the ADC returns the distance in inches, we must convert it to cm.

void sensors_setup(){
//  DDRA = 0x0;
//  PORTA = 0xff;
  //ADC initialization
  ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // prescaler = 128, ADC frequency = 125 KHz
  ADCSRA |= _BV(ADEN);  // enable ADC
  ADCSRA |= _BV(ADSC); // start a conversion to fully initialize the ADC circuitry
  loop_until_bit_is_clear(ADCSRA, ADSC); // wait for the conversion to finish
  
  //38kHz carrier for IR sensors
  DDRD |= _BV(DDD7); // set PD7 as output
  TCCR2 |= _BV(WGM21); // set timer2 in CTC mode
  TCCR2 |= _BV(COM20); // set to toggle OC2 on compare match
  TCCR2 |= _BV(CS20); // set prescaler to 1
  OCR2 = 209;
}

int read_adc(uint8_t channel){
  ADMUX = MUX | channel; // select ADC channel
  ADCSRA |= _BV(ADSC); // start the conversion
  loop_until_bit_is_clear(ADCSRA, ADSC); // wait for the conversion to finish
  printf("DEBUG: read_adc(%u) = %u\n", channel, ADC);
  return ADC;
}

int read_sonar(){
  int distance;
  distance = (read_adc(0) >> 1) * SONAR_SCALE;
  printf("DEBUG: distance in cm=%d\n", distance);
  return distance;
}

uint8_t read_line_sensors(){
  volatile uint8_t reading = 0;

//  reading |= PINA & _BV(PA1);
  reading |= PINA & _BV(PA2);
  reading |= PINA & _BV(PA3);
//  reading |= PINA & _BV(PA4);
//  printf("DEBUG: read_line_sensors() = %u\n", reading);
  return reading;
}

uint8_t read_front_sensors(){
  volatile uint8_t reading = 0;
  printf("pin5: %u\n", PINA & _BV(PA5));
  printf("pin6: %u\n", PINA & _BV(PA6));

  reading |= PINA & _BV(PA5);
  reading |= PINA & _BV(PA6);
  printf("DEBUG: read_front_sensors() = %u\n", reading);
  return reading;
}

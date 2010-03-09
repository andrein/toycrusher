#include "sensors.h"

#define MUX _BV(REFS0) // use AVCC as referecve voltage
#define SONAR_SCALE 100/39 // the ADC returns the distance in inches, we must convert it to cm.

void sensors_setup(){
  ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // prescaler = 128, ADC frequency = 125 KHz
  ADCSRA |= _BV(ADEN);  // enable ADC
  ADCSRA |= _BV(ADSC); // start a conversion to fully initialize the ADC circuitry
  loop_until_bit_is_clear(ADCSRA, ADSC); // wait for the conversion to finish
}

int read_adc(uint8_t channel){
  ADMUX = MUX | channel; // select ADC channel
  ADCSRA |= _BV(ADSC); // start the conversion
  loop_until_bit_is_clear(ADCSRA, ADSC); // wait for the conversion to finish
//  printf("DEBUG: read_adc(%u) = %u\n", channel, ADC);
  return ADC;
}

int read_sonar(){
  int distance;
  distance = (read_adc(0) >> 1) * SONAR_SCALE;
  printf("DEBUG: distance in cm=%d\n", distance);
  return distance;
}
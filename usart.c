#include "usart.h"
#define BAUD 38400
#define BAUD_PRESCALE ((F_CPU / (BAUD* 16UL) -1))

#define BUF_SIZE 32

FILE usart_stream = FDEV_SETUP_STREAM(usart_send_byte, usart_receive_byte, _FDEV_SETUP_RW);

void usart_setup(){
  UCSRB |= _BV(TXEN) | _BV(RXEN); //enable RX and TX
  UCSRC |= _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1); //set frame format: 8 data bits
  UBRRL = BAUD_PRESCALE; // load lower 8-bits of the baud rate value 
			 // into the low byte of the UBRR register
  UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value 
				// into the high byte of the UBRR register
  stdin = stdout = &usart_stream;
}

int usart_send_byte(char c, FILE* stream){
  if (c == '\n') 
    usart_send_byte('\r', stream);
  
  loop_until_bit_is_set(UCSRA, UDRE); // wait for UDR to be ready for more data
  UDR = c; // send the byte
  return 0;
}

int usart_receive_byte(FILE* stream){
  char c;
  char* cp;
  static char buf[BUF_SIZE];
  static char *rxp;
  
  if (rxp == NULL)
    for (cp = buf; ; ){
      loop_until_bit_is_set(UCSRA, RXC); // wait until UDR has data available
      c = UDR; // get the byte
      
      if (c == '\r')
	c = '\n';
      if (c == '\n'){
	*cp = c;
	usart_send_byte(c, stream);
	rxp = buf;
	break;
      }
      
      if (c>=' ' && c<='\x7e') {
	if (cp == buf + BUF_SIZE - 1){
	  usart_send_byte('\a', stream);
	} else {
	  *cp++ = c;
	  usart_send_byte(c, stream);
	}
	continue;
      }
      
      switch (c){
	case '\b': // handle backspace
	case '\x7f': 
	  if (cp > buf){
	    usart_send_byte('\b', stream);
	    usart_send_byte(' ', stream);
	    usart_send_byte('\b', stream);
	    cp--;
	  }
	  break;
      }
    }
      
    c = *rxp++;
    if (c == '\n')
      rxp = 0;
      
    return c;
}

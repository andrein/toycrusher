#ifndef USART_H
#define USART_H

#include "global.h"

void usart_setup(void);
int usart_send_byte(char c, FILE* stream);
int usart_receive_byte(FILE* stream);

#endif // USART_H

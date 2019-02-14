/*
 * uart0.h
 *
 * Created: 13/02/2019 14:33:44
 *  Author: lucas
 */ 


#ifndef UART0_H_
#define UART0_H_

#include <avr/io.h>
void usart0_init(void);
void usart0_transmit(char);



#endif /* UART0_H_ */
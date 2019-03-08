/*
 * uart1.h
 *
 * Created: 14/02/2019 14:50:48
 *  Author: lucas
 */ 


#ifndef UART1_H_
#define UART1_H_

#include <avr/io.h>
void usart1_init(void);
void usart1_transmit(char);
char usart1_get_UDR();


#endif /* UART1_H_ */
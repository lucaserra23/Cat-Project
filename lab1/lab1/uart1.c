/*
 * uart1.c
 *
 * Created: 14/02/2019 14:50:13
 *  Author: lucas
 */ 

#include "uart1.h"

void usart1_init() {
	
	UCSR1B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UBRR1 = 103;
}

void usart1_transmit(char data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	
	/* Put data into buffer, sends the data */
	UDR1 = data;
}
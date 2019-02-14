/*
 * CFile1.c
 *
 * Created: 13/02/2019 14:33:52
 *  Author: lucas
 */ 


#include "uart0.h"

void usart0_init() {
	
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UBRR0 = 103;
}

void usart0_transmit(char data) {
	 /* Wait for empty transmit buffer */
	 while ( !( UCSR0A & (1<<UDRE0)) );
	 
	 /* Put data into buffer, sends the data */
	 UDR0 = data;
}
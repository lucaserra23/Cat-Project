/*
 * uart1.c
 *
 * Created: 14/02/2019 14:50:13
 *  Author: lucas
 */ 

#include "uart1.h"

void usart1_init() { 
	
	UCSR1B |= (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	UBRR1 = 103;
}

void usart1_transmit(char data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) );
	
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

char usart1_get_UDR() {
	char data;
	/* Wait for full received buffer */
	while ( UCSR1A & (1<<UDRE1));
	
	/* Put UDR1 into data, show the data */
	data=UDR1;
	return (data);
}


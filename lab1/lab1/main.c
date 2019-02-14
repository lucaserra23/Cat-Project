/*
 * lab1.c
 *
 * Created: 04/02/2019 14:27:32
 * Author : lucas
 */ 
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart0.h"


volatile uint8_t data;
volatile uint16_t adc_result;
uint8_t button2;

int main(void)
{
    DDRB |= (1 << DDRB3);
	DDRA &=~(1<<DDRA2);
	usart0_init();
	adc_init();
	sei();			// Enables global interrupts => CPU will listen to IO devices interrupt requests
	//cli();		// Disable -||-
	adc_start_conversion();
    while (1) 
    {	
		button2 = PINA & (1 << PINA2);
		
		if (button2>0){
			PORTB^=(1<<PORTB3);
		} 
		////usart0_transmit('F');
		//usart0_transmit(adc_result >> 2);
		//usart0_transmit(0xA);
		//
		//
		//if (data == 't') {
			//
			//PORTB ^= (1 << DDRB5);
			//data = 0;
			//
		//}
    }
}




ISR(USART0_RX_vect){
	
	data = UDR0;
	UDR0 = data;
	
	
}
ISR(ADC_vect){
	adc_result = ADC;
	adc_start_conversion();
	
}
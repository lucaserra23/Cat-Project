/*
 * lab1.c
 *
 * Created: 04/02/2019 14:27:32
 * Author : lucas
 */ 
#define F_CPU	16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart0.h"
#include "uart1.h"
#include "adc.h"
#include "sim808.h"

volatile uint8_t data0;
volatile uint8_t data1;
volatile uint16_t adc_result;
uint8_t button2, button2_old;
char ok[4];
char data;
int result_acceleration;

int main(void)
{
    DDRB |= (1 << 3);   //DDRB3
	DDRA &=~(1<< 2);  //DDRA2
	usart0_init();
	usart1_init();
	adc_init();
	sei();			// Enables global interrupts => CPU will listen to IO devices interrupt requests
	//cli();		// Disable -||-
	adc_start_conversion();
	//sim808_send_sms("Warning! Abnormal acceleration!", "0046706141167");
    while (1) 
    {	
		//button2 = PINC & (1 << PINC7);
		//
		//if (button2>button2_old){
			//PORTB^=(1<<PORTB3);
			//sim808_ok();
		//} 
		//
		//button2_old = button2;
		//test the accelerometer
		//usart0_transmit(big_acceleration(ADC >> 2));
		//usart0_transmit(0xD);
		//usart0_transmit(0xA);
		if(big_acceleration(ADC>>2) == '1'){
			sim808_send_sms("Warning! Abnormal acceleration!", "0046706141167");
		}
		_delay_ms(200);
		
		
		
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
	
	data0 = UDR0;
	usart1_transmit(data0);
	
	
}

ISR(USART1_RX_vect){
	data1=UDR1;
	usart0_transmit(data1);
}
ISR(ADC_vect){
	adc_result = ADC;
	adc_start_conversion();
	
}
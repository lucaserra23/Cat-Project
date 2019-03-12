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
volatile char gps_msg[100];
volatile int gps_request;
volatile int index;
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
	gps_request=0;
	sim808_send_gps_pos_request();
	gps_request=1; //gps_request =1 means the message returned by the SIM with the current location is not totally registered.
	index=0;
	
    while (1) 
    {	
		
		/*
		if(big_acceleration(ADC>>2) == '1'){
			sim808_send_sms("Warning! Abnormal acceleration!", "0046706141167");
		}
		_delay_ms(200);
		
		*/
		if(gps_request == 0){
			char* message0 = splice_array(gps_msg, 28, 38);
			char* message1 = splice_array(gps_msg, 40, 50);
			char* message = splice_array(gps_msg, 28, 50);
			
			char* message00 = move_dot_array(message0);
			char* message10 = move_dot_array(message1);
			sim808_send_alert_yat(message, "0046706141167");
			gps_request = 1;
		}
		
	
		
    }

}






ISR(USART0_RX_vect){
	
	data0 = UDR0;
	usart1_transmit(data0);
	
	
}

ISR(USART1_RX_vect){
	data1=UDR1;
	usart0_transmit(data1);
	if(gps_request==1){
		gps_msg[index] = UDR1;
		index++;
	}
	if((UDR1 == 0xD) & (gps_msg[index-3]!= 0x3D) & (gps_msg[index-4]!= 0x3D)){ //here we end the message gps_msg if (we have <CR>) & (it is not the <CR> of the beginning of the answer of the SIM, which is AT+CGPSINFO=0<CR>) 
		gps_request = 0;
		index = 0;
	}
}
ISR(ADC_vect){
	adc_result = ADC;
	adc_start_conversion();
	
}
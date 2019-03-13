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
volatile int pos;
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
	pos=0;
	
    while (1) 
    {	
		
		/*
		if(big_acceleration(ADC>>2) == '1'){
			sim808_send_sms("Warning! Abnormal acceleration!", "0046706141167");
		}
		_delay_ms(200);
		
		*/
		if(gps_request == 0){
			char* gps_tmp = gps_msg;
			char* message0 = splice_array(gps_tmp, 47, 56);
			char* message1 = splice_array(gps_tmp, 57, 66);
			char* message = splice_array(gps_tmp, 47, 66);
			char* link = "http://maps.google.com/maps?q=loc:";
			char* messageok = message;
			char* message2=concat(link,messageok);

			sim808_send_alert_yat(message2, "0046706141167");
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
		gps_msg[pos] = UDR1;
		pos++;
	}
	if((UDR1 == 0xD) && (gps_msg[pos-2]==0x2C)){ //here we end the message gps_msg if (we have <CR>) & (it is not the <CR> of the beginning of the answer of the SIM, which is AT+CGPSINFO=0<CR>) 
		gps_request = 0;
		pos = 0;
	}
}
ISR(ADC_vect){
	adc_result = ADC;
	adc_start_conversion();
	
}
//(!(0x40<gps_msg[index-2]<0x5B))&& (!(0x40<gps_msg[index-3]<0x5B))
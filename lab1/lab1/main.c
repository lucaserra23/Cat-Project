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
volatile int16_t adc_result;
volatile uint8_t temp;
volatile char gps_msg[100];
volatile int gps_request;
volatile int pos;
char data;
int result_acceleration;
volatile int adc_channel;
int adc_res;
volatile int16_t x_val;
volatile int16_t y_val;
volatile int16_t z_val;
volatile uint32_t sum_val;
volatile uint8_t alert;
volatile uint16_t num3000 =3000;

long long int strange = 0x12344567;

int main(void)
{
	usart0_init();
	usart1_init();
	adc_init();
	sei();			// Enables global interrupts => CPU will listen to IO devices interrupt requests
	adc_start_conversion();
	gps_request=0;
	sim808_send_gps_pos_request();
	gps_request=1; //gps_request =1 means the message returned by the SIM with the current location is not totally registered.
	pos=0;
	
    while (1) 
<<<<<<< HEAD
    {			
		if(big_acceleration(ADC>>2) == 0x30){ //Test if the accelerometer detects an acceleration. If yes, we send a message
			if(gps_request == 0){ //gps_request = 0 means the message returned by the SIM with the current location is totally registered.
				char* gps_tmp = gps_msg; //we copy gps_msg in a non volatile variable
				char* message = splice_array(gps_tmp, 47, 66);  //we only keep a certain portion of the message sent by the sim808
				char* link = "http://maps.google.com/maps?q=loc:";
				char* messageok = message;
				char* message2=concat(link,messageok);
				sim808_send_alert_yat(message2, "0046721570368");
				gps_request = 1;
			}
=======
    {		
		adc_res = ADC>>2;	
		if(alert==1){ //Test if the accelerometer detects an acceleration. If yes, we send a message
			alert=0;
			usart0_transmit(0x41);

			char* gps_tmp = gps_msg;
			//char* message0 = splice_array(gps_tmp, 47, 56);
			//char* message1 = splice_array(gps_tmp, 57, 66);
			char* message = splice_array(gps_tmp, 47, 66);
			char* link = "http://maps.google.com/maps?q=loc:";
			char* messageok = message;
			char* message2=concat(link,messageok);
			sim808_send_alert_yat(message2, "0046721570368");

>>>>>>> e88819cc31ae1b062b38187ebb3d6245fce9f361
		_delay_ms(200);
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
<<<<<<< HEAD
	// registering the message sent by the sim808
	if(gps_request==1){
		gps_msg[pos] = UDR1;
		pos++;
	}
	if((UDR1 == 0xD) && (gps_msg[pos-2]==0x2C)){ //here we end the message gps_msg if the last character is <CR> and if the second to last character is a coma
		gps_request = 0;
		pos = 0;
	}
=======
>>>>>>> e88819cc31ae1b062b38187ebb3d6245fce9f361
}

ISR(ADC_vect){
	
	adc_result = (ADC>>2) -125;
	switch (adc_channel){
		case 0: 
			x_val=adc_result;
			break;
		case 1: 
			y_val=adc_result;
			break;
		case 2:
			z_val=adc_result;
			break;
	}
	sum_val=x_val*x_val+y_val*y_val+z_val*z_val;
	if (sum_val>num3000){
		alert=1;
	}
	
	adc_channel ++;
	if (adc_channel == 3){
		adc_channel = 0;
	}
	temp=ADMUX & 0b11111100;
	ADMUX = temp | adc_channel;
	adc_start_conversion();
}
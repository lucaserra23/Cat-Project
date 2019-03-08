/*
 * adc.c
 *
 * Created: 14/02/2019 14:07:48
 *  Author: lucas
 */ 
#include "adc.h"

void adc_init(){
	ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADMUX |= (1<<REFS0)|(1 << MUX0); //MUX1 is for the Z axis, MUX0 for the Y axis and remove |(1 << MUX1) for the X axis
}

char big_acceleration(char data){
	if (abs((int)data-125)>5){
		return (0x31);
	}
	return (0x30);
}

void adc_start_conversion(){
	ADCSRA |= (1<<ADSC);
}
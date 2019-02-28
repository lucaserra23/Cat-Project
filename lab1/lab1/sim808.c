/*
 * sim808.c
 *
 * Created: 28/02/2019 14:02:51
 *  Author: lucas
 */ 
#include "sim808.h"

void sim808_ok() {
	usart1_transmit('A');
	usart1_transmit('T');
	usart1_transmit(0xD);
	usart1_transmit(0xA);
	
}

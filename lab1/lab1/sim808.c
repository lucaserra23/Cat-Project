/*
 * sim808.c
 *
 * Created: 28/02/2019 14:02:51
 *  Author: lucas
 */ 
#include "sim808.h"
#include <string.h>
#define F_CPU	16000000UL
#include <util/delay.h>

	
void sim808_command(char *command){  //calling this function will result in sending the desired command to the SIM808 instead of only one character at a time
	
	int i;
	int lenght = strlen(command);
	for(i=0; i<lenght; i++){
		
		usart1_transmit(command[i]); 
	}
}

/void sim808_initialize(){ //initializes the SIM808 
	sim808_command("AT"); //we send AT at the beginning of the connection 	
	usart1_transmit(0xD); //then <CR>
	
}


void sim808_send_sms(char *sms, char* tel_number){
	
	sim808_command("AT+CMGF=1"); //the command which set the sim to TEXT mode not PDU (data) mode. You must do this because otherwise you cannot
	                             //just type out the message.
	usart1_transmit(0xD);  // <CR>
	_delay_ms(50);
	char* beginning = "AT+CMGS=";
	char *quote = "\"";
	char *num1= concat(beginning, quote);
	char *num2= concat(num1, tel_number);
	char *num= concat(num2, quote);
	sim808_command(num); 
	usart1_transmit(0xD);  // <CR>
	_delay_ms(50);
	sim808_command(sms);
	usart1_transmit(0x1A); //CTRL+Z
	usart1_transmit(0xD); // <CR>	
	
}

//concatenation fonction
char* concat(const char *s1, const char *s2){
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}


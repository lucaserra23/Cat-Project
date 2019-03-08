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



void sim808_ok() {
	usart1_transmit('A');
	usart1_transmit('T');
	usart1_transmit(0xD);

}
	

/*int sim808_initialize(){ //initializes the SIM808 and returns 1 if the connection is OK, 0 otherwise
	sim808_command("AT"); //we send AT at the beginning of the connection 
	if(sim808_get_answer()!="OK"){
		return(0);
	}
	return(1);
// We assume that the sim is initialized for the rest of these functions	
	
}*/
void sim808_command(char *command){  //calling this function will result in sending the desired command to the SIM808
	
	int i;
	int lenght = strlen(command);
	for(i=0; i<lenght; i++){
		
		usart1_transmit(command[i]); //there might be problems with things like +
	}
}

/*char sim808_get_answer(){ // will return the answer of the sim808
	
	char data;
	// Wait for full received buffer
	while ( UCSR1A & (1<<UDRE1));
	
	// Put UDR1 into data, show the data 
	data=UDR1;	
	
	return data;
	
	}*/
	
/*int sim808_check_network(){  //returns 1 if the signal is strong enough, 0 otherwise
	sim808_command("AT+CSQ");
	if (((int)sim808_get_answer())>5){
		return(1);
		}
	return(0);*/
	

void sim808_send_sms(char *sms, char* tel_number){
	
	sim808_command("AT+CMGF=1"); //the command which set the sim to TEXT mode not PDU (data) mode. You must do this because otherwise you cannot
	                             //just type out the message.
	usart1_transmit(0xD);  // <CR>
	_delay_ms(50);
	char* beginning = "AT+CMGS=";
	char *quote = "\"";
	char *num1= concat(beginning, quote);
	char *num2= concat(num1, tel_number);
	char *num3= concat(num2, quote);
	sim808_command(num3); //send a text message! You will get a '>' prompt for typing. Type out your message and when you are done send a [Control-Z] on an empty line to send
	// the message has to be written in the '>' prompt
	usart1_transmit(0xD);  // <CR>
	_delay_ms(50);
	sim808_command(sms);
	usart1_transmit(0x1A);
	usart1_transmit(0x0D);	
	//_delay_ms(50);
	//sim808_command(end);
	_delay_ms(50);

}


char* concat(const char *s1, const char *s2){
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	// in real code you would check for errors in malloc here
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}


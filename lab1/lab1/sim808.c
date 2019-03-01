/*
 * sim808.c
 *
 * Created: 28/02/2019 14:02:51
 *  Author: lucas
 */ 
#include "sim808.h"
#include <string.h>

void sim808_ok() {
	usart1_transmit('A');
	usart1_transmit('T');
	usart1_transmit(0xD);
	usart1_transmit(0xA);
	
}
int sim808_initialize(){ //initializes the SIM808 and returns 1 if the connection is OK, 0 otherwise
	sim808_command("AT"); //we send AT at the beginning of the connection 
	if(sim808_get_answer()!="OK"){
		return(0);
	}
	return(1);
// We assume that the sim is initialized for the rest of these functions	
	
}
void sim808_command(char[] command){  //calling this function will result in sending the desired command to the SIM808
	int i;
	int lenght = strlen(command);
	for(i=0; i<lenght; i++){
		usart1_transmit(command[i]); //there might be problems with things like +
	}
	usart1_transmit(0xD);  // <CR>
	usart1_transmit(0xA);  // <LF>
	
}
char[] sim808_get_answer(){} // will return the answer of the sim808
int sim808_check_network(){  //returns 1 if the signal is strong enough, 0 otherwise
	sim808_command("AT+CSQ");
	/*if (int(sim808_get_answer())>5){
		return(1);}
	return(0) */
	
}
int sim808_send_sms(char[] sms, long sim_number){
	sim808_command("AT+CMGF=1"); //the command which set the sim to TEXT mode not PDU (data) mode. You must do this because otherwise you cannot
	                             //just type out the message.
	sim808_command("AT+CMGS=conversiontochar[](sim_number)"); //send a text message! You will get a '>' prompt for typing. Type out your message and when you are done send a [Control-Z] on an empty line to send
	// the message has to be written in the '>' prompt... How ?

}



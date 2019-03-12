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
void sim808_command_yat(char *command){  //function used to make some tests with yat
	
	int i;
	int lenght = strlen(command);
	for(i=0; i<lenght; i++){
		
		usart0_transmit(command[i]);
	}
}

void sim808_initialize(){ //initializes the SIM808 
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
void sim808_send_gps_pos_request(){
	sim808_command("AT+CGPSPWR=1"); //Turning on the GPS
	usart1_transmit(0xD);
	_delay_ms(50);
	sim808_command("AT+CGPSINF=0");
	usart1_transmit(0xD);

}
void sim808_send_alert_yat(char *gps_position, char* tel_number){
	char* sms = "Warning! Abnormal acceleration detected at the following coordinates: ";
	sim808_command_yat("AT+CMGF=1"); //the command which set the sim to TEXT mode not PDU (data) mode. You must do this because otherwise you cannot
	//just type out the message.
	usart0_transmit(0xD);  // <CR>
	_delay_ms(50);
	char* quote = "\"";
	char* beginning = "AT+CMGS=\"";
	char *num1= concat(beginning, tel_number);
	char *num2= concat(num1, quote);
	sim808_command_yat(num2);
	usart0_transmit(0xD);  // <CR>
	char* final_message = concat(sms, gps_position);
	sim808_command_yat(final_message);
	usart0_transmit(0x1A); //CTRL+Z
	usart0_transmit(0xD); // <CR>
	
	free(num1);
	free(num2);
	
}

//concatenation function
char* concat(const char *s1, const char *s2){
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

//splicing an array of character between i and j. 
char* splice_array(char* array, int i, int j){
	char* subset = malloc((j-i)*sizeof(char)); //Where i is the place you want to start your subset.
	int k;
	for(k=0;k<j-i;k++){
		subset[k] = array[k+i];
	}
	return(subset);
	free(subset);
}
//returns the good format for the coordinates
char* move_dot_array(char* array){
	char* copy1 = malloc(sizeof(array));
	int i;
	for(i=0;i<sizeof(array);i++){
		if(array[i]!= 0x2E){
			copy1[i]=array[i];
			}
	}
	char* copy2 = malloc(sizeof(array));	
	copy2[0]=array[0];
	copy2[1]=array[1];
	copy2[2]=0x2E;
	for(i=3;i<sizeof(array);i++){
		copy2[i]=copy1[i];
	}
	return(copy1);
	free(copy1);
	free(copy2);
}

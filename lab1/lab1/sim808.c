/*
 * sim808.c
 *
 * Created: 28/02/2019 14:02:51
 *  Author: lucas
 */ 
#include "sim808.h"
#include "uart0.h"
#include "uart1.h"
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


void sim808_send_sms(char *sms, char* tel_number){ //This function allows to send an sms to a phone
	
	sim808_command("AT+CMGF=1"); //the command which set the sim to TEXT mode not PDU (data) mode. You must do this because otherwise you cannot
	                             //just type out the message.
	usart1_transmit(0xD);  // <CR>
	_delay_ms(50);
	char* beginning = "AT+CMGS=";
	char *quote = "\"";
	char *num1= concat(beginning, quote);
	char *num2= concat(num1, tel_number);
	char *num= concat(num2, quote);
	sim808_command(num); //We send AT=CMGS="tel number" to enable the communication with the phone
	usart1_transmit(0xD);  // <CR>
	_delay_ms(50);
	sim808_command(sms); //We send the sms
	usart1_transmit(0x1A); //CTRL+Z
	usart1_transmit(0xD); // <CR>	These two commands allow to close the communication
	
}
void sim808_send_gps_pos_request(){ //This function allows to have the coordinate of the GPS
	sim808_command("AT+CGPSPWR=1"); //Turning on the GPS
	usart1_transmit(0xD);
	_delay_ms(50);
	sim808_command("AT+CGNSSEQ=\"RMC\""); //setting the right format
	usart1_transmit(0xD);
	_delay_ms(50);
	sim808_command("AT+CGNSINF"); //reading the coordinates
	usart1_transmit(0xD);
	

}
void sim808_send_alert_yat(char *gps_position, char* tel_number){ //This function sends the warning message to the phone
	char* sms = "Warning! Abnormal acceleration detected at the following coordinates: ";
	sim808_command("AT+CMGF=1"); //the command which set the sim to TEXT mode not PDU (data) mode. You must do this because otherwise you cannot
	//just type out the message.
	usart1_transmit(0xD);  // <CR>
	_delay_ms(100);
	char* quote = "\"";
	char* beginning = "AT+CMGS=\"";
	char *num1= concat(beginning, tel_number);
	char *num2= concat(num1, quote);
	sim808_command(num2);
	usart1_transmit(0xD);  // <CR>
	_delay_ms(100);
	char* please = splice_array(gps_position,0,strlen(gps_position)-1);
	char* final_message = concat(sms,please);
	sim808_command(final_message);
	usart1_transmit(0x1A); //CTRL+Z
	//_delay_ms(10);
	usart1_transmit(0x0D); // <CR>

	free(num1);
	free(num2);
	
}

char* concat(const char *s1, const char *s2){ // This function allows to concatenate two elements
	char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

//splicing an array of character between i and j
char* splice_array(char* array, int i, int j){
	char* subset = malloc((j-i)*sizeof(char)); //Where i is the place you want to start your subset.
	int k;
	for(k=0;k<j-i;k++){
		subset[k] = array[k+i];
	}
	return(subset);
	free(subset);
}

char* move_dot_array(char* array){ // This function returns the good format for the coordinates
	char* copy1=concat(splice_array(array, 0,2),0X2E); //xx.
	char* copy2=concat(copy1,splice_array(array,3,5)); // xx.xx
	char* copy3=concat(copy2,splice_array(array,5,10)); //xx.xxyyyyy
	
	return(copy3);
	free(copy1);
	free(copy2);
	free(copy3);
}

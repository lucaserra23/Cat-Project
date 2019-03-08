/*
 * sim808.h
 *
 * Created: 28/02/2019 14:03:14
 *  Author: lucas
 */ 


#ifndef SIM808_H_
#define SIM808_H_
#define SIM808_NUMBER	89460850127004686343

#include <avr/io.h>
#include <stdlib.h>
#include "uart1.h"
void sim808_ok(void);
int sim808_initialize(void);

//added functions
void sim808_command(char*);
int sim808_check_network(void);
char* sim808_get_answer(void);
void sim808_send_sms(char *sms, char *tel_number);
char* concat(const char*, const char*);

extern char ok[4];

#endif /* SIM808_H_ */
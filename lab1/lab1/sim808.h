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
void sim808_initialize(void);

//added functions
void sim808_command(char*);
void sim808_command_yat(char*);
void sim808_send_sms(char *, char *);
void sim808_alert_yat(char*, char *);
void sim808_send_gps_pos_request(void);

char* concat(const char*, const char*);
char* splice_array(char*, int, int);
char* move_dot_array(char*);




#endif /* SIM808_H_ */
/*
 * ddcmp_session.h
 *
 *  Created on: 11 мар. 2017 г.
 *      Author: frol
 */


#ifndef DDCMP_DDCMP_SESSION_H_
#define DDCMP_DDCMP_SESSION_H_

#include "USART.h"
#include "board.h"
#include "Write-Read.h"
#include "command_messages.h"
#include <string.h>


#define BUFFER_SIZE     260
#define IRREADANZ       256
#define IRDATAFIRST     0x01
#define IRDATAAGAIN     0x02
#define IRDATACOMPLETE  0x04

#define CONTROL_MESSAGES 		1
#define DATA_COMMAND_MESSAGES 	2
#define DATA_MESSAGE_HEADER 	9
#define DATA_COMMAND_RESPONSES 	4
#define DATA_BLOCKS 			5

#define START 					1
#define STACK 					2
#define ACK 					3
#define NACK 					4
#define WAY 					5
#define WAY_RESP 				6
#define READ_DATA 				7
#define READ_DATA_RESP 			8

#define OK						1
#define ERROR					0

char send_buffer[BUFFER_SIZE];    //Буфер передачи
unsigned char receive_buffer[BUFFER_SIZE];  //Буфер получения

static unsigned int crc;

int check_crc(unsigned char *buf, int cnt);
void set_crc(char *buf, int cnt);
int resend(int wcnt,UART_HandleTypeDef *Uart);
void initialization(UART_HandleTypeDef *Uart);

#endif /* DDCMP_DDCMP_SESSION_H_ */


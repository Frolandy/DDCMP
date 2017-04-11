/*
 * data_message.h
 *
 *  Created on: 1 апр. 2017 г.
 *      Author: frol
 */

#ifndef INC_DATA_MESSAGE_H_
#define INC_DATA_MESSAGE_H_

#include "ddcmp_session.h"
#include "USART.h"

#define BUFFER_SIZE     260

char send_buffer[BUFFER_SIZE];  
unsigned char receive_buffer[BUFFER_SIZE];  

static char accesstype;
static char list_name = 0x01;

static char securitycode[] = {0x00, 0x00};
static char passcode[] = {0x00, 0x00};
static char iruserid[] = {0x00, 0x00};

void set_data_header(int size);
int send_way(UART_HandleTypeDef *Uart);
int send_read_data(UART_HandleTypeDef *Uart);

#endif /* INC_DATA_MESSAGE_H_ */

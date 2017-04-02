/*
 * command_messages.h
 
 *  Created on: 30 мар. 2017 г.
 *      Author: frol
 */

#ifndef SRC_DDCMP_COMMAND_MESSAGES_H_
#define SRC_DDCMP_COMMAND_MESSAGES_H_
#include "ddcmp_session.h"
#include "board.h"
#include "USART.h"

//control messages
static char msgstart[] = {0x05, 0x06, 0x40, 0x00, 0x00, 0x01};
static char msgstack[] = {0x05, 0x07, 0x40, 0x00, 0x00, 0x01, 0x00, 0x00};
static char msgack[] =   {0x05, 0x01, 0x40, 0x00, 0x00, 0x01, 0x00, 0x00};
static char msgnack[] =  {0x05, 0x02, 0x40, 0x00, 0x00, 0x01, 0x00, 0x00};

static int statistiknack = 0;

int send_start(UART_HandleTypeDef *Uart);  //Отправить START
int send_ack();    //Отправить ACK
int send_nack(char msg, UART_HandleTypeDef *Uart); //Отправить NACK

#endif /* SRC_DDCMP_COMMAND_MESSAGES_H_ */

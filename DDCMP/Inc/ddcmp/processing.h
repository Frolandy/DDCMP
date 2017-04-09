/*
 * processing.h
 *
 *  Created on: 5 апр. 2017 г.
 *      Author: frol
 */

#ifndef INC_PROCESSING_H_
#define INC_PROCESSING_H_

#include "data_message.h"
#include "ddcmp_session.h"
#include "USART.h"

static int receive_message_type = 0;
static int receive_message = 0;

static unsigned char dataflag;

static int sent = 0;
static long reclaenge;
static long restreclaenge;
static int byteread;

void sent_control(int msg);
void parsing_message();
void answer(UART_HandleTypeDef *Uart);

void processing(UART_HandleTypeDef *Uart);


#endif /* INC_PROCESSING_H_ */

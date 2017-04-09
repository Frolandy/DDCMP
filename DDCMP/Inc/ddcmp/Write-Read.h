/*
 * Write-Read.h
 *
 *  Created on: 1 апр. 2017 г.
 *      Author: frol
 */

#ifndef INC_WRITE_READ_H_
#define INC_WRITE_READ_H_
#include "USART.h"
#include "ddcmp_session.h"
#include "processing.h"

static int _received_b = 0;


int get_count_received_bytes();
int read_on_port(UART_HandleTypeDef *Uart, int byte);
void write_on_port(UART_HandleTypeDef *Uart, int size);


#endif /* INC_WRITE_READ_H_ */


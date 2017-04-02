/*
 * Write-Read.h
 *
 *  Created on: 1 апр. 2017 г.
 *      Author: frol
 */

#ifndef INC_WRITE_READ_H_
#define INC_WRITE_READ_H_
#include "board.h"
#include "USART.h"
#include "ddcmp_session.h"

void write_on_port(UART_HandleTypeDef *Uart, int size);
int read_on_port(UART_HandleTypeDef *Uart);

#endif /* INC_WRITE_READ_H_ */

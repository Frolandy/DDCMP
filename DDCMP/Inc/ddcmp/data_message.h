/*
 * data_message.h
 *
 *  Created on: 1 апр. 2017 г.
 *      Author: frol
 */

#ifndef INC_DATA_MESSAGE_H_
#define INC_DATA_MESSAGE_H_

#include "ddcmp_session.h"

void set_data_header(int size);
void send_way(UART_HandleTypeDef *Uart);

#endif /* INC_DATA_MESSAGE_H_ */

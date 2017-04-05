/* ddcmp_session.h
 *
 *  Created on: 11 мар. 2017 г.
 *      Author: frol
 */


#ifndef DDCMP_DDCMP_SESSION_H_
#define DDCMP_DDCMP_SESSION_H_

#include "USART.h"
#include "board.h"
#include "resources.h"
#include "Write-Read.h"
#include "command_messages.h"
#include <string.h>


int check_crc(unsigned char *buf, int cnt);
void set_crc(char *buf, int cnt);
int resend(int wcnt,UART_HandleTypeDef *Uart);
void initialization(UART_HandleTypeDef *Uart);

#endif /* DDCMP_DDCMP_SESSION_H_ */


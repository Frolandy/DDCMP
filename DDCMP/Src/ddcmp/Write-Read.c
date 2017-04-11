#include "Write-Read.h"

void write_on_port(UART_HandleTypeDef *Uart, int size){
	for(int i=0; i<size; i++){
		USART_PutChar(Uart,send_buffer[i]);
	}
}
int read_on_port(UART_HandleTypeDef *Uart, int byte){
	if(byte == 9 && _received_b > 3){
		int rec, rest, byt;
		rec = ((receive_buffer[2] & 0x3f) << 8) | receive_buffer[1];
					rest = rec + 2;
					byt = (int) rest;
		byte = byt + 8;
	}
			if(USART_GetRxCount(Uart) > 0){
			receive_buffer[_received_b++] = USART_GetChar(Uart);
			if (_received_b == byte) {
				_received_b = 0;
				return byte;
			}
		}
			return 0;
}

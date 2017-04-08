#include "Write-Read.h"

void write_on_port(UART_HandleTypeDef *Uart, int size){
	for(int i=0; i<size; i++){
		USART_PutChar(Uart,send_buffer[i]);
	}
}
int read_on_port(UART_HandleTypeDef *Uart, int byte){
	int _is_readed = 0;

			if(USART_GetRxCount(Uart) > 0){
			receive_buffer[_received_b++] = USART_GetChar(Uart);
			if (_received_b == byte) {
				_is_readed = 1;
				_received_b = 0;
			}
		}
			return _is_readed;
}

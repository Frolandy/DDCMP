#include "Write-Read.h"

void write_on_port(UART_HandleTypeDef *Uart, int size){
	for(int i=0; i<size; i++){
		USART_PutChar(Uart,send_buffer[i]);
	}
}
int read_on_port(UART_HandleTypeDef *Uart){
	int size =0;
	do{
		receive_buffer[size] = USART_GetChar(Uart);
		size++;
	for(int i=0; i<100000; i++){

	}
	}while(USART_GetRxCount(Uart) > 0);
	return size;
}

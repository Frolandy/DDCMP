#include "data_message.h"

void set_data_header(int size){    //Установка заголовка
  send_buffer[0] = 0x81;
  send_buffer[1] = size & 0xff;
  send_buffer[2] = 0x40 | ((size >> 8) & 0xff);
  send_buffer[3] = receive_cnt - 1;
  send_buffer[4] = send_cnt;
  send_buffer[5] = 1;
  set_crc(send_buffer,6);
}

int send_way(UART_HandleTypeDef *Uart){  //Отправка Who are u
	set_data_header(16);

	send_buffer[8] = 0x77;
	send_buffer[9] = 0xE0;
	send_buffer[10] = 0x00;
	send_buffer[23] = accesstype;

	memcpy(&send_buffer[11],securitycode,2);
	memcpy(&send_buffer[13],passcode,2);
	memcpy(&send_buffer[21],iruserid,2);

	set_crc(&send_buffer[8],16);

	sent_control(WAY);

	return resend(26, Uart);
}

int send_read_data(UART_HandleTypeDef *Uart){ //Отправка READ DATA
	  set_data_header(9);

	  send_buffer[8] = 0x77;
	  send_buffer[9] = 0xe2;
	  send_buffer[10] = 0x00;
	  send_buffer[11] = list_name;
	  send_buffer[12] = 1;
	  send_buffer[13] = 0;
	  send_buffer[14] = 0;
	  send_buffer[15] = 0;
	  send_buffer[16] = 0;

	  set_crc(&send_buffer[8],9);

	  sent_control(READ_DATA);

	  return(resend(19, Uart));
}

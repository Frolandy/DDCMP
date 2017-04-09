#include "processing.h"
#include "USART.h"

extern UART_HandleTypeDef huart2;
void sent_control(int msg){
	sent = msg;
}

int type_of_message(char first_byte){ //Тип сообщения

	switch(first_byte){

		case 0x05:
		return CONTROL_MESSAGES;

		case 0x77:
		return DATA_COMMAND_MESSAGES;

		case 0x81:
		return DATA_MESSAGE_HEADER;

		case 0x88:
		return DATA_COMMAND_RESPONSES;

		case 0x99:
		return DATA_BLOCKS;
	}
	return 0;
}

int this_message_is(char second_byte, int message_type){ //Определение сообщения

	if(message_type==CONTROL_MESSAGES){
		switch(second_byte){

			case 0x06:
			return START;

			case 0x07:
			//if(check_crc(receive_buffer, 6)){
			return STACK;
			//}else break;

			case 0x01:
			//if(receive_buffer[3] == send_cnt && check_crc(receive_buffer, 6) == OK)
			return ACK;
			//else break;

			case 0x02:
			//if(receive_buffer[3] == send_cnt && check_crc(receive_buffer, 6) == OK)
			return NACK;
			//else break;
		}

	}else if(message_type==DATA_COMMAND_MESSAGES){

		switch(second_byte){

			case 0xE0:
			return WAY;

			case 0xE2:
			return READ_DATA;

		}

	}else if(message_type==DATA_COMMAND_RESPONSES){

		switch(second_byte){

			case 0xE0:
			return WAY_RESP;

			case 0xE2:
			return READ_DATA_RESP;

		}

	}else if(message_type == DATA_BLOCKS)
		return DATA_BLOCKS;
	return 0;
}

void parsing_message() { //Разбор сообщения

	receive_message_type = type_of_message(receive_buffer[0]);

	if(receive_message_type){

		if(receive_message_type == DATA_MESSAGE_HEADER){

			reclaenge = ((receive_buffer[2] & 0x3f) << 8) | receive_buffer[1];
			restreclaenge = reclaenge + 2;
			byteread = (int) restreclaenge + 6;

			if((unsigned) byteread > IRREADANZ){

				if(restreclaenge - IRREADANZ < 2)
					byteread = IRREADANZ - 1;
				else
					byteread = IRREADANZ;
		    }
		    	dataflag |= IRDATAFIRST;

		    	if (restreclaenge - byteread <= 0){
		    		receive_message = DATA_MESSAGE_HEADER;
		    	//receive_message_type = type_of_message(receive_buffer[8]);
		    	//receive_message = this_message_is(receive_buffer[9], receive_message_type);
		    	}else{
		    		if(sent == READ_DATA){
		    			receive_message = DATA_BLOCKS;
		    		}
		    	}
		}else
			receive_message = this_message_is(receive_buffer[1], receive_message_type);
	}
}

void answer(UART_HandleTypeDef *Uart){ //Ответ
		switch(sent) {

			case START:

				if(receive_message == STACK){
					send_way(Uart);
					bytes(8);
				}
				break;

			case WAY:

				if(receive_message == ACK){
					bytes(8);
					break;
				}if(receive_message == DATA_MESSAGE_HEADER){
					bytes(byteread);
					break;
				}if(receive_message == WAY_RESP){
					send_ack(Uart);
					send_read_data(Uart);
					bytes(8);
					break;
				} break;

			case READ_DATA:

				if(receive_message == ACK){
					bytes(8);
					break;
				}
				if(receive_message == DATA_MESSAGE_HEADER){
					bytes(byteread);
					break;
				}
				if(receive_message == READ_DATA_RESP){
					send_ack(Uart);
					bytes(8);
					break;
				}
				break;

			case ACK:
			if(receive_message == DATA_MESSAGE_HEADER){
				bytes(byteread);
				break;
			}
			if(receive_message == DATA_BLOCKS){
				if(restreclaenge >= byteread){


				restreclaenge -= byteread;

				if(restreclaenge > 0){
				send_ack(Uart);
				bytes(byteread);
				break;
				}

				dataflag |= IRDATACOMPLETE;
				send_ack(Uart);
				break;
				}
			}
			break;
		}
}

void processing(UART_HandleTypeDef *Uart) {
	parsing_message();
	//answer(Uart);
}


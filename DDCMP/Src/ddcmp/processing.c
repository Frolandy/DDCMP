/*

*/
#include "processing.h"

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
			waiting = STACK;
			return START;

			case 0x07:
			if(test_crc(receive_buffer, 6) == OK){
			waiting = WAY;
			return STACK;
			}
			break;

			case 0x01:
			if(receive_buffer[3] == send_cnt && test_crc(receive_buffer, 6) == OK)
			return ACK;
			break;

			case 0x02:
			if(receive_buffer[3] == send_cnt && test_crc(receive_buffer, 6) == OK)
			return NACK;
			break;
		}

	}else if(message_type==DATA_COMMAND_MESSAGES){

		switch(second_byte){

			case 0xE0:
			waiting = ACK;
			return WAY;

			case 0xE2:
			waiting = ACK;
			return READ_DATA;

		}

	}else if(message_type==DATA_COMMAND_RESPONSES){

		switch(second_byte){

			case 0xE0:
			waiting = ACK;
			return WAY_RESP;

			case 0xE2:
			waiting = ACK;
			return READ_DATA_RESP;

		}

	}
	return 0;
}

void parsing_message(){ //Разбор сообщения

	receive_message_type = type_of_message(receive_buffer[0]);

	if(receive_message_type){

		if(receive_message_type == DATA_MESSAGE_HEADER){

			if(check_crc(receive_buffer, 6) == OK
				&& receive_buffer[4] == receive_cnt){

			reclaenge = (receive_buffer[2] & 0x3f) << 8 | receive_buffer[1];
			restreclaenge = reclaenge + 2;
			byteread = (int) restreclaenge;

			if((unsigned) byteread > IRREADANZ){

				if(restreclaenge - IRREADANZ < 2)
					byteread = IRREADANZ - 1;
				else
					byteread = IRREADANZ;
		    }
		    	dataflag |= IRDATAFIRST;

		    	if (restreclaenge - byteread <= 0){
		    	receive_message_type = type_of_message(receive_buffer[8]);
		    	receive_message = this_message_is(receive_buffer[9], receive_message_type);
		    	}
			}
		}else
			receive_message = this_message_is(receive_buffer[1], receive_message_type);
	}
}

void answer(UART_HandleTypeDef *Uart){ //Ответ
		switch(sent){

			case START:

				if(waiting == STACK && receive_message == STACK){
					send_way(Uart);
					waiting = ACK;
				}
				break;

			case WAY:

				if(waiting == ACK && receive_message == ACK){
					waiting = WAY_RESP;
				}else if(waiting == WAY_RESP && receive_message == WAY_RESP){
					send_ack(Uart);
					waiting = 0;
				}
				break;

			case READ_DATA:

				if(waiting == ACK && receive_message == ACK){
					waiting = READ_DATA_RESP;
				}else if(waiting == READ_DATA_RESP && receive_message == READ_DATA_RESP)
					send_ack(Uart);
					waiting = DATA_BLOCKS;
				break;

			case ACK:

			if(waiting == DATA_BLOCKS && receive_message == DATA_BLOCKS){
				if(restreclaenge >= byteread && check_crc(receive_buffer,byteread-2) == OK){

				restreclaenge -= byteread;

				if(restreclaenge > 0 && check_crc(receive_buffer,byteread) == OK){
				send_ack(Uart);
				break;
				}

				dataflag |= IRDATACOMPLETE;
				send_ack(Uart);
				waiting = 0;
				break;
				}
			}
			break;
		}
}

int processing(UART_HandleTypeDef *Uart){
	parsing_message();
	return (answer(Uart));
}

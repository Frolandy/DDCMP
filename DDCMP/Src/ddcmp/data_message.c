#include "data_message.h"


void set_data_header(int size){
  send_buffer[0] = 0x81;
  send_buffer[1] = size & 0xff;
  send_buffer[2] = 0x40 | ((size >> 8) & 0xff);
  send_buffer[3] = receive_cnt - 1;
  send_buffer[4] = send_cnt;
  send_buffer[5] = 1;
  set_crc(send_buffer,6);
}

int sendctrl(char *buf, UART_HandleTypeDef *Uart){
  //long htimeout;

 // stopread();
  set_crc(buf,6); //316
//  irwritecnt = 8;
  write_on_port(Uart,8); //Запись строки

  //htimeout = TICKCNT;
 // for(;;){
   // errcode = oqsiz_a1(spno,&size); ////Возврат размера очереди вывода
   // if(!size) break;
 // }
  return 0;
}

static int send_finish(UART_HandleTypeDef *Uart){
	int a;
  //Посылка завершена
  irothstate = WT_ACKF;
  setdatahdr(2); //Длина без CRC !
  send_buffer[8] = 0x77;
  send_buffer[9] = 0xff;
  set_crc(&send_buffer[8],2);
  return(resend(12,8,0, Uart));
}

static int send_read_data(UART_HandleTypeDef *Uart){
	  set_data_header(9); //Длина без CRC !
	  send_buffer[8] = 0x77;
	  send_buffer[9] = 0xe2;
	  send_buffer[10] = 0;
	  //send_buffer[11] = listnum;
	  send_buffer[12] = 1; //recno
	  send_buffer[13] = 0; //byteoffset low
	  send_buffer[14] = 0; //byteoffset high
	  send_buffer[15] = 0; //segment length low (complete record)
	  send_buffer[16] = 0; //segment length high (complete record)
	  setcrc(&send_buffer[8],9);
	  irotstate = S_READRESP;
	  irothstate = WT_ACKD;
	  return(resend(19,8,0, Uart));
}

static int send_write_data(UART_HandleTypeDef *Uart){
  if(setfilesize()){
    //Больше ничего не писать
    irotstate = S_READY;
    return sendfinish();
  }
  set_data_header(6); //Laenge ohne CRC !
  send_buffer[8] = 0x77;
  send_buffer[9] = 0xe3;
  send_buffer[10] = 0;
 // send_buffer[11] = listnum;
  //send_buffer[12] = filesize & 0xff;   //recsize low
  //send_buffer[13] = filesize >> 8 & 0xff;  //recsize high
  setcrc(&send_buffer[8],6);
  irotstate = S_WRITERESP;
  irothstate = WT_ACKD;
  return(resend(16,8,0, Uart));
}

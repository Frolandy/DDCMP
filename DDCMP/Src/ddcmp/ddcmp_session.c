#include "ddcmp_session.h"

int check_crc(unsigned char *buf, int cnt) { //Проверка контрольной суммы

  unsigned char bitcnt;
  unsigned char flg;

  for(;cnt--;){
    crc ^= *(unsigned char*)buf++; //0xa001 (1 + x**2 + x**15 + x**16) */
    bitcnt = 8;

    do {
      flg = crc & 1;
      crc >>= 1;
      if (flg)
        crc ^= 0xa001;
    } while (--bitcnt);

  }

  if(*(unsigned char*)buf++ == (crc & 0xff) && *(unsigned char*)buf == (crc >> 8 & 0xff)){
    return(0); //crc ok
  }

  return(-1); //crc error
}

void set_crc(char *buf, int cnt){ //Установка контрольной суммы

  unsigned char     bitcnt;
  unsigned char     flg;

  for(crc = 0;cnt--;){
    crc ^= *(unsigned char*)buf++; // 0xa001 (1 + x**2 + x**15 + x**16) */
    bitcnt = 8;

    do {
      flg = crc & 1;
      crc >>= 1;
      if (flg)
        crc ^= 0xa001;
    } while (--bitcnt);

  }

  *buf++ = crc & 0xff;
  *buf = crc >> 8 & 0xff;
}

int resend(int wcnt,int rcnt,int rpos, UART_HandleTypeDef *Uart) {
  long htimeout;

  //stopread();
  bytessend = wcnt;

  if(wcnt){
	  write_on_port(Uart, wcnt);

    //htimeout = TICKCNT;

    //for(;;){
     // oqsiz_a1(spno,&size);  //Возврат размера очереди вывода
      //if(!size) break;
    //}
 }

  if(rcnt){
    bytestoread = rcnt;
    irreadcnt = 0;
    postoread = &receive_buffer[rpos];
    readrunning = 1;
    //stoptimeout();
    //starttimeout();
  }
  return(0);
}

void initialization(UART_HandleTypeDef *Uart){
	irotstate = S_START;
	irothstate = WT_STACK;
	send_cnt = 1;
	receive_cnt = 1;
	accesstype = 0x0c;
	Board_Init();
	send_start(Uart);
}

int processing(int toflag, UART_HandleTypeDef *Uart){
	switch(irothstate){


		  case WT_STACK: //Жди запуск ACK

		    crc = 0;

		    if(receive_buffer[0] != 0x05 || receive_buffer[1] != 0x07 ||
		      toflag || check_crc(receive_buffer,6)) {
		      return(resend(8,8,0, Uart));
		    }
	}
	switch(irotstate){


		  case S_START:  //Принял STACK, послал who are you

			set_data_header(16); //Длина без CRC
		    send_buffer[8] = 0x77;
		    send_buffer[9] = 0xe0;
		    send_buffer[10] = 0;
		    send_buffer[23] = accesstype;

		    memcpy(&send_buffer[11],securitycode,2);
		    memcpy(&send_buffer[13],passcode,2);
		    memcpy(&send_buffer[21],iruserid,2);

		    //timemde(&send_buffer[15]);
		    set_crc(&send_buffer[8],16);

		    irotstate = S_WAY;
		    irothstate = WT_ACKD;

		    return(resend(26,8,0, Uart));

	}
	if(irotstate==S_WAY){
		send_ack(Uart);
	}
	return 0;
}

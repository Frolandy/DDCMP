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
    return(OK); //crc ok
  }

  return(ERROR); //crc error
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

 int resend(int wcnt,UART_HandleTypeDef *Uart) {  //Отправка сообщения
  if(wcnt)
    write_on_port(Uart, wcnt);
  return 0;
}

void initialization(UART_HandleTypeDef *Uart){    //Инициализация, отправка СТАРТ
  waiting = STACK;
  sent = START;
  send_cnt = 1;
  receive_cnt = 1;
  accesstype = 0x0c;
  Board_Init();
  send_start(Uart);
}



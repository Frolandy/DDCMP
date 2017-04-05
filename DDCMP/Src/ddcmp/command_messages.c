#include "command_messages.h"

int send_start(UART_HandleTypeDef *Uart) { //Отправить START
  memcpy(send_buffer,msgstart,6);
  set_crc(send_buffer, 6);
  sent = START;
  return(resend(8, Uart));
}

int send_ack(UART_HandleTypeDef *Uart){   //Отправить АСК
  msgack[3] = receive_cnt++;
  memcpy(send_buffer,msgack,6);
  set_crc(send_buffer, 6);
  sent = ACK;
  return(resend(8, Uart));
}

int send_stack(UART_HandleTypeDef *Uart){ //Отправить STACK
   memcpy(send_buffer,msgstack,6);
   set_crc(send_buffer, 6);
   sent = STACK;
   return(resend(8, Uart));
}

int send_nack(UART_HandleTypeDef *Uart){  //Отправить NACK
  statistiknack++;
  msgnack[3] = receive_cnt - 1;
  memcpy(send_buffer, msgnack, 6);
  set_crc(send_buffer, 6);
  sent = NACK;
  return(resend(8, Uart));
}

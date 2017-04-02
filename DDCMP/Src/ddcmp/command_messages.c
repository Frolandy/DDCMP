#include "command_messages.h"

int send_start(UART_HandleTypeDef *Uart) {
  for(int i=0; i<6; i++){
    send_buffer[i]=msgstart[i];
  }
  set_crc(send_buffer, 6);
  return(resend(8, 8, 0, Uart));
}

int send_ack(UART_HandleTypeDef *Uart){
  //msgack[3] = receive_cnt++;
  for(int i=0; i<6; i++){
    send_buffer[i]=msgack[i];
  }
  set_crc(send_buffer, 6);
  return(resend(8, 8, 0, Uart));
}

int send_nack(char msg, UART_HandleTypeDef *Uart){
  statistiknack++;
  msgnack[2] = msg;
  msgnack[3] = receive_cnt - 1;
 // if(sendctrl(msgnack)) return -1;
  return(resend(0,8,0, Uart));
}

/*
 * ddcmp_session.h
 *
 *  Created on: 11 мар. 2017 г.
 *      Author: frol
 */


#ifndef DDCMP_DDCMP_SESSION_H_
#define DDCMP_DDCMP_SESSION_H_
#include "USART.h"
#include "command_messages.h"
#include "data_message.h"
#include "Write-Read.h"
#include <string.h>

#define BUFFER_SIZE     260

char send_buffer[BUFFER_SIZE];    //Буфер передачи
unsigned char receive_buffer[BUFFER_SIZE];  //Буфер получения

static int irotstate;           //Фаза передачи
static int irothstate;          //Частичная фаза передачи

#define BUFFER_SIZE     260


char send_buffer[BUFFER_SIZE];    //Буфер передачи
unsigned char receive_buffer[BUFFER_SIZE];  //Буфер получения

static int bytessend;
static int bytestoread;
static int irreadcnt;
static int postoread;
static int readrunning;

static unsigned char receive_cnt;        //Счетчик получения ddcmp
static unsigned char send_cnt;          //Счетчик передачи ddcmp
static unsigned int crc;


static char accesstype;
static long data_length;
static unsigned char block_cnt;

static char securitycode[] = {0x00, 0x00};
static char passcode[] = {0x00, 0x00};
static char iruserid[] = {0x00, 0x00};
static char sernummer[8] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};

static char doprogflag = 0;
static char doinpflag = 0;
static char doclearflag = 0;
static char dooutpflag = 0;
static char timestring[20];
static int binfnamesize = 0;
static int verbosecnts = 0;
static int verbosecntr = 0;
static int verbosecnte = 0;

#define WT_STACK        0       /* Жди запуск ACK */
#define WT_ACK          1       /* Жди ACK */
#define WT_ACKD         2       /* Жди ACK и затем DHDR */
#define WT_ACKF         3       /* Жди финально ACK (иногда отсутствует) */
#define WT_DHDR         4       /* Жди заголовок данных */
#define WT_DATA         5       /* Жди данные */
#define WT_START        6       /* Жди START */

#define S_START         0       /* START послано */
#define S_WAY           1       /* WAY   послано */
#define S_REFUSED       2       /* FINISH после отклонения управления посланий */
#define S_READRESP      3       /* READ-требование к посланию */
#define S_PROGRESP      4       /* PROG-требование к посланию */
#define S_WRITERESP     5       /* WRITE-Aтребование к посланию */
#define S_CLEARRESP     6       /* CLEAR-требование к посланию */
#define S_READ          7       /* Данные принимаются */
#define S_READY         8       /* FINISH Посылается после правильного переноса */
#define S_WRITE         9       /* Данные посылаются */


void set_crc(char *buf, int cnt);
int check_crc(unsigned char *buf, int cnt);
int readsend(void);
int resend(int wcnt,int rcnt,int rpos, UART_HandleTypeDef *Uart);
void initialization(UART_HandleTypeDef *Uart);

#endif /* DDCMP_DDCMP_SESSION_H_ */

/*
 * resources.h
 *
 *  Created on: 6 апр. 2017 г.
 *      Author: frol
 */

#ifndef INC_RESOURCES_H_
#define INC_RESOURCES_H_

#define BUFFER_SIZE     260
#define IRREADANZ       256
#define IRDATAFIRST     0x01
#define IRDATAAGAIN     0x02
#define IRDATACOMPLETE  0x04

#define CONTROL_MESSAGES        1
#define DATA_COMMAND_MESSAGES   2
#define DATA_MESSAGE_HEADER     3
#define DATA_COMMAND_RESPONSES  4
#define DATA_BLOCKS             5

#define START                   1
#define STACK                   2
#define ACK                     3
#define NACK                    4
#define WAY                     5
#define WAY_RESP 				        6
#define READ_DATA 				      7
#define READ_DATA_RESP 			    8

#define OK						          1
#define ERROR                   0

char send_buffer[BUFFER_SIZE];    //Буфер передачи
unsigned char receive_buffer[BUFFER_SIZE];  //Буфер получения

static long reclaenge;
static long restreclaenge;
static int bytesread;
static int bytessend;
static int bytestoread;
static int irreadcnt;
static int readrunning;
static int byteread;


static unsigned char receive_cnt;        //Счетчик получения ddcmp
static unsigned char send_cnt;          //Счетчик передачи ddcmp
static unsigned char block_cnt;
static unsigned int crc;
static unsigned char dataflag;


static char accesstype;

static char securitycode[] = {0x00, 0x00};
static char passcode[] = {0x00, 0x00};
static char iruserid[] = {0x00, 0x00};

static int receive_message_type = 0;
static int receive_message = 0;

static int waiting = 1;
static int sent = 0;

static char list_name = 0x01;

static int data_length;

#endif /* INC_RESOURCES_H_ */

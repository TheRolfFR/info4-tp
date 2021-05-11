/* 
 * File:   UART_LIN.h
 * Author: aravey
 *
 * Created on 12 april 2020, 13:42
 */

#ifndef UART_LIN_H
#define	UART_LIN_H

#include "stm32f4xx.h"


//Declaration to Link External Functions & Variables:

/*--- Lin message structures and flag ---*/

typedef struct
  {
  uint8_t ID;
  uint8_t length;
  uint8_t data[10];
} LINMSG;

typedef struct {
    uint8_t ID;
    uint8_t keepGetting;
    uint8_t dataLength;
} TypeMsg;

#define LIN_RCPBUFF_LEN 10

#define LIN_FLAG_NO_MESSAGE 0

//Variables with Global Scope  
extern  unsigned char DisplayData[];
extern  LINMSG Tx_Msg;
extern  LINMSG Rx_Msg;
extern int new_request;

/********** MASTER/SLAVE Switch *********/
void LIN_SetMaster();
void LIN_SetSlave();

/********** Slave Callback *********/
void LIN_SetReceiveCallback(void (*callback)(uint8_t));

//Functions :
void UART_Init (void);
void SendMessage(LINMSG *msg);
void SendRequest(uint8_t id);
void SendResponse(LINMSG *msg);
void UART_PutChar(uint8_t data);
uint8_t UART_GetChar();
void sync_break(void);
uint8_t checksum(uint8_t length, uint8_t *data);



#endif	/* UART_LIN_H */


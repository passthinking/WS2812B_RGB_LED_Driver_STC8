#ifndef _STC8_TIMER2_UART_H_
#define _STC8_TIMER2_UART_H_

#include "main.h"

#define BRTUART1 230400UL

#define Timer2Value ( 65536 - FOSC / BRTUART1 / 4 )


void Uaurt1_Send_String( char * p );
void UART1_Send(char ch);
void initTimer2_UART(void);

extern void Uart1_Receiver_Data_CallBuck(unsigned char ch);

#endif


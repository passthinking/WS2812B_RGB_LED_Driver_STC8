

#include "STC8_TIMER2_UART.h"

bit Uart1_busy = 0;

void initTimer2_UART(void)
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = Timer2Value;			//设定定时初值
	T2H = Timer2Value >> 8;	//设定定时初值
	AUXR |= 0x10;		//启动定时器2
	ES = 1;
	EA = 1;
}

void InterruptUart1() interrupt 4
{
	if(TI)
	{
		TI = 0;
		Uart1_busy = 0;
	}
	if(RI)
	{
		RI = 0;
		Uart1_Receiver_Data_CallBuck( SBUF );
	}
}


void UART1_Send(char ch)
{
	while(Uart1_busy);
	Uart1_busy = 1;
	SBUF = ch;
}

void Uaurt1_Send_String( char * p )
{
	while( *p )
	{
		UART1_Send( *p );
		p ++;
	}
}





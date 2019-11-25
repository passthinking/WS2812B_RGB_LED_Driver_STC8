

#include "STC8_TIMER2_UART.h"

bit Uart1_busy = 0;

void initTimer2_UART(void)
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = Timer2Value;			//�趨��ʱ��ֵ
	T2H = Timer2Value >> 8;	//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
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





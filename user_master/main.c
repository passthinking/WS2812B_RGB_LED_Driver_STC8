#include "main.h"
#include "WS2812B_RGB_Driver.h"
#include "STC8_TIMER2_UART.h"
#include "CircularQueue.h"
#include "TransmissionCommuicationProtcol.h"

unsigned char xdata circularQueueBuff[ CircularQueueLength ];

unsigned char xdata SendDataBuff[ 256 ];

void delayms( int t );

void main()
{
	unsigned int i = 0;
	unsigned int length = 0;
	unsigned char ch_value = 0;

	initTimer2_UART();
	initReceiver(); 
	P5M0 = 0xFF;
	P5M1 = 0x00;	
	
	Uaurt1_Send_String("start up ...");
	
	for( i = 0; i < 256; i ++ )
	{
		SendDataBuff[ i ] = 0;
	}
	
	while(1)
	{
		length = get_DataLength();
		if( length >= 3 * 32 + 2 )
		{
			for( i = 0; i < length; i ++ )
			{
				if( get_Data_CircularQueue( &ch_value ) > 0 )
				{
//				receiverLoop( ch_value );
//				UART1_Send( ch_value );
					
					SendDataBuff[i + 1] = ch_value;
					
				}
			}
			sendData( SendDataBuff, 3 * 32 + 2 );
		}
		
	}
}


void Uart1_Receiver_Data_CallBuck(unsigned char ch)
{
	add_Data_CircularQueue(ch);
}



void delayms( int t )
{
	int i = 0, j = 0; 
	for( i = 0; i < t; i ++ )
	{
		for( j = 0; j < 1000; j ++);
	}
}



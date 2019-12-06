#include "main.h"
#include "WS2812B_RGB_Driver.h"
#include "STC8_TIMER2_UART.h"
#include "CircularQueue.h"
#include "TransmissionCommuicationProtcol.h"

unsigned char xdata Line_1[3*32];
unsigned char xdata Line_2[3*32];

unsigned char xdata circularQueueBuff[ CircularQueueLength ];

void main()
{
	unsigned char Number = 0;

	unsigned char ch_value = 0;
	
	unsigned int i = 0;
	unsigned int length = 0;

	initTimer2_UART();
	initReceiver(); 
	P5M0 = 0xFF;
	P5M1 = 0x00;	
	
	for( Number = 0; Number < 3*32; Number ++ )
	{
		Line_1[ Number ] = 0xff;
		Line_2[ Number ] = 0xff;
	}
	Uaurt1_Send_String("start up ...");
	
	Number = 0;
	
	while(1)
	{
		waterfall_light( Line_1, Line_2, 3 * 32 );
		delay50us(5);															//@27.000MHz
		
		length = get_DataLength();
		for( i = 0; i < length; i ++ )
		{
			if( get_Data_CircularQueue( &ch_value ) > 0 )
			{
				receiverLoop( ch_value );
//				UART1_Send( ch_value );
			}
		}
		getReceiverData( Line_1, Line_2, 3 * 32 );
	}
}


void Uart1_Receiver_Data_CallBuck(unsigned char ch)
{
	add_Data_CircularQueue(ch);
}






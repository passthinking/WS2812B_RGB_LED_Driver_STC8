#include "main.h"
#include "WS2812B_RGB_Driver.h"
#include "STC8_TIMER2_UART.h"
#include "CircularQueue.h"

unsigned char xdata Line_1[3*16];
unsigned char xdata Line_2[3*16];

unsigned char xdata circularQueueBuff[CircularQueueLength];

void main()
{
	unsigned char Number = 0;
	unsigned char count3 = 0;
	unsigned char RGBBuff[3];

	unsigned char ch_value = 0;
	
	unsigned int i = 0;
	unsigned int length = 0;

	initTimer2_UART();
	P5M0 = 0xFF;
	P5M1 = 0x00;	
	
	for(Number = 0; Number < 3*16; Number ++)
	{
		Line_1[ Number ] = 0xff;
		Line_2[ Number ] = 0xff;
	}
	
	setRGB( Line_1 , 0, 0, 0  , 0   );
	setRGB( Line_2 , 1, 0  , 0, 0   );
	
	Uaurt1_Send_String("start up ...");
	
	while(1)
	{
		waterfall_light( Line_1, Line_2, 3 * 16 );
		delay50us(5);									//@27.000MHz
		
		length = get_DataLength();
		for( i = 0; i < length; i ++ )
		{
			if( get_Data_CircularQueue( &ch_value ) > 0 )
			{
			
				RGBBuff[count3] = ch_value;
				count3 ++;
				if(count3 >= 3)
				{
					count3 = 0;
				}
				
				for(Number = 0; Number < 16; Number ++)
				{
					setRGB( Line_1 , Number, RGBBuff[0], RGBBuff[1], RGBBuff[2] );
					setRGB( Line_2 , Number, RGBBuff[0], RGBBuff[1], RGBBuff[2] );
				} 
				
//				if(ch_value == "0")
//				{
//					for(Number = 0; Number < 3*16; Number ++)
//					{
//						Line_1[ Number ] = 0xff;
//						Line_2[ Number ] = 0xff;
//					}
//				}
//				else
//				{
//					for(Number = 0; Number < 3*16; Number ++)
//					{
//						Line_1[ Number ] = 0x00;
//						Line_2[ Number ] = 0x00;
//					}
//				}
				UART1_Send( ch_value );
			}
		}
	}
}


void Uart1_Receiver_Data_CallBuck(unsigned char ch)
{
	add_Data_CircularQueue(ch);
}






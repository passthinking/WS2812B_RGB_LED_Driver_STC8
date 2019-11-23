#include "main.h"
#include "WS2812B_RGB_Driver.h"

void main()
{
	unsigned char xdata Line_1[3*16];
	unsigned char xdata Line_2[3*16];
	unsigned char Number = 0;
	unsigned char bit_flag = 0;

	P5M0 = 0xFF;
	P5M1 = 0x00;	
	
	for(Number = 0; Number < 3*16; Number ++)
	{
		Line_1[ Number ] = 0xff;
		Line_2[ Number ] = 0xff;
	}
	
	setRGB( Line_1 , 0, 0, 0  , 0   );
	setRGB( Line_2 , 1, 0  , 0, 0   );
	
	while(1)
	{
		Number ++ ;
		
		if(bit_flag)
		{
//			setRGB( Line_1 , 0, 0  , 0  , 0   );
//			setRGB( Line_1 , 1, 255, 255, 255 );
//			setRGB( Line_1 , 2, 0  , 0  , 0   );
//			setRGB( Line_1 , 3, 255, 255, 255 );
//			setRGB( Line_1 , 4, 0  , 0  , 0   );
//			setRGB( Line_1 , 5, 255, 255, 255 );
//			setRGB( Line_1 , 6, 0  , 0  , 0   );
//			setRGB( Line_1 , 7, 255, 255, 255 );
//			setRGB( Line_1 , 8, 0  , 0  , 0   );
//			setRGB( Line_1 , 9, 255, 255, 255 );
//			setRGB( Line_1 ,10, 0  , 0  , 0   );
//			setRGB( Line_1 ,11, 255, 255, 255 );
//			setRGB( Line_1 ,12, 0  , 0  , 0   );
//			setRGB( Line_1 ,13, 255, 255, 255 );
//			setRGB( Line_1 ,14, 0  , 0  , 0   );
//			setRGB( Line_1 ,15, 255, 255, 255 );
		}
		else
		{
//			setRGB( Line_1 , 0, 255, 255, 255 );
//			setRGB( Line_1 , 1, 0  , 0  , 0   );
//			setRGB( Line_1 , 2, 255, 255, 255 );
//			setRGB( Line_1 , 3, 0  , 0  , 0   );
//			setRGB( Line_1 , 4, 255, 255, 255 );
//			setRGB( Line_1 , 5, 0  , 0  , 0   );
//			setRGB( Line_1 , 6, 255, 255, 255 );
//			setRGB( Line_1 , 7, 0  , 0  , 0   );
//			setRGB( Line_1 , 8, 255, 255, 255 );
//			setRGB( Line_1 , 9, 0  , 0  , 0   );
//			setRGB( Line_1 ,10, 255, 255, 255 );
//			setRGB( Line_1 ,11, 0  , 0  , 0   );
//			setRGB( Line_1 ,12, 255, 255, 255 );
//			setRGB( Line_1 ,13, 0  , 0  , 0   );
//			setRGB( Line_1 ,14, 255, 255, 255 );
//			setRGB( Line_1 ,15, 0  , 0  , 0   );
		}
		bit_flag = ~bit_flag;
		
//		setRGB( Line_1 , Number % 8, Number, Number, Number );
//		setRGB( Line_2 , Number % 8, 256 - Number, 256 -Number, Number );
		waterfall_light( Line_1, Line_2, 3 * 16 );
		delay50us(5);									//@27.000MHz
	}
}














#include "main.h"
#include "intrins.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WS2812_1  P54
#define WS2812_2  P55
 
//发送24位数据
void Send_2811_24bits(unsigned char *Line_1, unsigned char *Line_2, unsigned int n )
{
	unsigned char value_1,value_2,j;
	value_1 = Line_1[n];
	value_2 = Line_2[n];
	for(j = 0; j < 8; j ++)
	{
		//0码，高电平850ns 低电平400ns 误差正负150ns
		if( ( ( value_1 & 0x80 ) == 0x80 ) && ( ( value_2 & 0x80 ) == 0x80 ) )
		{
			EA = 0;
			WS2812_1 = 1;
			WS2812_2 = 1;
			_nop_();
			_nop_();
			WS2812_1 = 0;
			WS2812_2 = 0;
			EA = 1;
		}else if( ( ( value_1 & 0x80 ) != 0x80 ) && ( ( value_2 & 0x80 ) == 0x80 )  )
		{
			EA = 0;
			WS2812_1 = 1;
			WS2812_2 = 1;
			_nop_(); 
			_nop_(); 
			WS2812_2 = 0;
			_nop_(); 
			_nop_(); 
			_nop_();
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_();
			WS2812_1 = 0; 
			EA = 1;
		}else if( ( ( value_1 & 0x80 ) == 0x80 ) && ( ( value_2 & 0x80 ) != 0x80 )  )
		{
			EA = 0;
			WS2812_1 = 1;
			WS2812_2 = 1;
			_nop_(); 
			_nop_(); 
			WS2812_1 = 0;
			_nop_(); 
			_nop_(); 
			_nop_();
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_();
			WS2812_2 = 0; 
			EA = 1;
		}else
		{
			EA = 0;
			WS2812_1 = 1;
			WS2812_2 = 1;
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_();
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_(); 
			_nop_();
			WS2812_1 = 0;
			WS2812_2 = 0; 
			EA = 1;
		}
		value_1 <<= 1;
		value_2 <<= 1;
	}
}

//复位码
void RGB_Rst()
{
	WS2812_1 = 0;
	WS2812_2 = 0;
}

void delay50us(int t)		//@27.000MHz
{
	int i, j;
	for(i = 0; i < t; i ++)
	{
		for(j = 0; j < 144; j ++);
	}
}


void setRGB(unsigned char *p,int Number, unsigned char G, unsigned char R, unsigned char B)
{
	int value = 0;
	value = 3*Number; 
	p[ value + 0 ] = G;
	p[ value + 1 ] = R;
	p[ value + 2 ] = B;
}

void waterfall_light(unsigned char *Line_1, unsigned char *Line_2, int Number)
{
	int i;
	for(i = 0; i < Number; i ++)
	{
		Send_2811_24bits( Line_1, Line_2, i );
	}
	RGB_Rst();
}


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
			setRGB( Line_1 , 0, 0  , 0  , 0   );
			setRGB( Line_1 , 1, 255, 255, 255 );
			setRGB( Line_1 , 2, 0  , 0  , 0   );
			setRGB( Line_1 , 3, 255, 255, 255 );
			setRGB( Line_1 , 4, 0  , 0  , 0   );
			setRGB( Line_1 , 5, 255, 255, 255 );
			setRGB( Line_1 , 6, 0  , 0  , 0   );
			setRGB( Line_1 , 7, 255, 255, 255 );
			setRGB( Line_1 , 8, 0  , 0  , 0   );
			setRGB( Line_1 , 9, 255, 255, 255 );
			setRGB( Line_1 ,10, 0  , 0  , 0   );
			setRGB( Line_1 ,11, 255, 255, 255 );
			setRGB( Line_1 ,12, 0  , 0  , 0   );
			setRGB( Line_1 ,13, 255, 255, 255 );
			setRGB( Line_1 ,14, 0  , 0  , 0   );
			setRGB( Line_1 ,15, 255, 255, 255 );
		}
		else
		{
			setRGB( Line_1 , 0, 255, 255, 255 );
			setRGB( Line_1 , 1, 0  , 0  , 0   );
			setRGB( Line_1 , 2, 255, 255, 255 );
			setRGB( Line_1 , 3, 0  , 0  , 0   );
			setRGB( Line_1 , 4, 255, 255, 255 );
			setRGB( Line_1 , 5, 0  , 0  , 0   );
			setRGB( Line_1 , 6, 255, 255, 255 );
			setRGB( Line_1 , 7, 0  , 0  , 0   );
			setRGB( Line_1 , 8, 255, 255, 255 );
			setRGB( Line_1 , 9, 0  , 0  , 0   );
			setRGB( Line_1 ,10, 255, 255, 255 );
			setRGB( Line_1 ,11, 0  , 0  , 0   );
			setRGB( Line_1 ,12, 255, 255, 255 );
			setRGB( Line_1 ,13, 0  , 0  , 0   );
			setRGB( Line_1 ,14, 255, 255, 255 );
			setRGB( Line_1 ,15, 0  , 0  , 0   );
		}
		bit_flag = ~bit_flag;
		
//		setRGB( Line_1 , Number % 8, Number, Number, Number );
//		setRGB( Line_2 , Number % 8, 256 - Number, 256 -Number, Number );
		waterfall_light( Line_1, Line_2, 3 * 16 );
		delay50us(5);									//@27.000MHz
	}
}














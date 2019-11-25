
#include "WS2812B_RGB_Driver.h"



//复位码
void RGB_Rst()
{
	WS2812_1 = 0;
	WS2812_2 = 0;
}

 
//发送24位数据
void Send_2811_24bits(unsigned char *Line_1, unsigned char *Line_2, unsigned int n )
{
	unsigned char value_1,value_2,j;
	value_1 = Line_1[n];
	value_2 = Line_2[n];
	
	for(j = 0; j < 8; j ++)
	{
		EA = 0;
		//0码，高电平850ns 低电平400ns 误差正负150ns
		if( ( ( value_1 & 0x80 ) == 0x80 ) && ( ( value_2 & 0x80 ) == 0x80 ) )
		{
			WS2812_1 = 1;
			WS2812_2 = 1;
			_nop_();
			_nop_();
			WS2812_1 = 0;
			WS2812_2 = 0;
		}else if( ( ( value_1 & 0x80 ) != 0x80 ) && ( ( value_2 & 0x80 ) == 0x80 )  )
		{
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
		}else if( ( ( value_1 & 0x80 ) == 0x80 ) && ( ( value_2 & 0x80 ) != 0x80 )  )
		{
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
		}else
		{
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
		}
		value_1 <<= 1;
		value_2 <<= 1;
		EA = 1;
	}
	
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



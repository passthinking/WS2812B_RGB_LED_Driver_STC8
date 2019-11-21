#include "main.h"
#include "intrins.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 
#define WS2812  P55
 
//1码，高电平850ns 低电平400ns 误差正负150ns
void RGB_Set_Up()
{
	EA = 0;
	WS2812 = 1;
	_nop_(); _nop_();
	WS2812 = 0;
	EA = 1;
}
 
//1码，高电平400ns 低电平850ns 误差正负150ns
void RGB_Set_Down()
{
	EA = 0;
	WS2812 = 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	WS2812 = 0; 
	EA = 1;
}
 
//发送24位数据
void Send_2811_24bits(unsigned char *p, unsigned int n )
{
	unsigned int i;
	unsigned char value,j;
	for(i = 0; i < n; i ++)
	{
		value = p[i];
		for(j = 0; j < 8; j ++)
		{
			if((value & 0x80) == 0x80)
			{
				RGB_Set_Up();
			}
			else
			{
				RGB_Set_Down();
			}
			value <<= 1;
		}
	}
}

//复位码
void RGB_Rst()
{
	WS2812 = 0;
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

void waterfall_light(unsigned char *p, int Number)
{
	int i;
	for(i = 0; i < Number; i ++)
	{
		Send_2811_24bits(p,3*Number);
	}
	RGB_Rst();
}


void main()
{
	unsigned char xdata M[3*16] = { 
		0  , 0  , 0  , 
		0  , 255, 255,
		255, 255, 0  ,
		0  , 255, 255,
	};
	unsigned char Number = 0;

	P5M0 = 0xFF;
	P5M1 = 0x00;	
	
	while(1)
	{
		Number ++ ;
		setRGB(M, Number % 16, 256 - Number, Number, Number );
		waterfall_light( M, 16 );
		delay50us(5);									//@27.000MHz
	}
}














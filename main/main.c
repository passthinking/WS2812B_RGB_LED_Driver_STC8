#include "main.h"
#include "intrins.h"
#include <stdio.h>
#include <stdlib.h>

 
sbit WS2812 = P1^0;
 
//复位延时
void Delay50us()		//@25MHz
{
	unsigned char i, j;

	i = 2;
	j = 51;
	do
	{
		while (--j);
	} while (--i);
}


//1码，高电平850ns 低电平400ns 误差正负150ns
void RGB_Set_Up()
{
	EA = 0;
	WS2812 = 1;
	_nop_(); _nop_();_nop_();_nop_();
	WS2812 = 0;
	EA = 1;
	
}
 
//1码，高电平400ns 低电平850ns 误差正负150ns
void RGB_Set_Down()
{
	EA = 0;
	WS2812 = 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();_nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();_nop_(); _nop_();
	WS2812 = 0; 
	EA = 1;
}
 
//发送24位数据
void Send_2811_24bits(unsigned char *p, unsigned int n )
{
	unsigned int i,j;
	unsigned char value;
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
	Delay50us();
}


void Delay1000ms()		//@25MHz
{
	unsigned char i, j, k;

	i = 95;
	j = 255;
	k = 174;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay100ms()		//@25MHz
{
	unsigned char i, j, k;

	i = 10;
	j = 128;
	k = 218;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void setRGB(unsigned char *p,int Number, unsigned char R, unsigned char G, unsigned char B)
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
		if(i>0)
		{
			setRGB( p, i-1, 255, 255, 255);
		}
		setRGB( p, i, 0, 255, 255);
		RGB_Rst();
		Send_2811_24bits(p,3*30);
		Delay100ms();		//@25MHz
	}
	setRGB( p, 0, 255, 255, 255);
	setRGB( p, 1, 255, 255, 255);
	setRGB( p, 2, 255, 255, 255);
	setRGB( p, 3, 255, 255, 255);
	setRGB( p, 4, 255, 255, 255);
	setRGB( p, 5, 255, 255, 255);
	setRGB( p, 6, 255, 255, 255);
	setRGB( p, 7, 255, 255, 255);
}


void main()
{
	unsigned char xdata M[3*30] = { 
		0  , 255, 255, 
		255, 0  , 255,
		255, 255, 0  ,
		255, 255, 255,
		0  , 0  , 0  ,
		255, 0  , 0  ,
		0  , 255, 0  ,
		0  , 0  , 255,	
		};
	
	P1M0 = 0xFF;
	P1M1 = 0x00;	
		
//	srand(23);
	
	Delay1000ms();		//@25MHz
	
//	setRGB( M, 0, 0, 255, 255);
		
	while(1)
	{
		
		
		waterfall_light(M, 30);
		
//		M[0] = rand()%0xff;
//		M[1] = rand()%0xff;
//		M[2] = rand()%0xff;
//		M[3] = rand()%0xff;
//		M[4] = rand()%0xff;
//		M[5] = rand()%0xff;
//		M[6] = rand()%0xff;
//		M[7] = rand()%0xff;
//		M[8] = rand()%0xff;
//		M[9] = rand()%0xff;
//		M[10] = rand()%0xff;
//		M[11] = rand()%0xff;
//		M[12] = rand()%0xff;
//		M[13] = rand()%0xff;
//		M[14] = rand()%0xff;
//		M[15] = rand()%0xff;
//		M[16] = rand()%0xff;
//		M[17] = rand()%0xff;
//		M[18] = rand()%0xff;
//		M[19] = rand()%0xff;
//		M[20] = rand()%0xff;
//		M[21] = rand()%0xff;
//		M[22] = rand()%0xff;
//		M[23] = rand()%0xff;	

	}
}














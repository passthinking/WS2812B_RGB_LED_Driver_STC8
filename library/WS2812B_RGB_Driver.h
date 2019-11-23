#ifndef _WS2812B_RGB_DRIVER_H_
#define _WS2812B_RGB_DRIVER_H_

#include "main.h"

#define WS2812_1  P54
#define WS2812_2  P55



void waterfall_light(unsigned char *Line_1, unsigned char *Line_2, int Number);
void setRGB(unsigned char *p,int Number, unsigned char G, unsigned char R, unsigned char B);
void delay50us(int t);		//@27.000MHz
void Send_2811_24bits(unsigned char *Line_1, unsigned char *Line_2, unsigned int n );
void RGB_Rst();

#endif

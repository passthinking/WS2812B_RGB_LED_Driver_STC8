

/*
	传输协议：
		|__"SP"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|		
*/

#ifndef _TransmissionCommuicationProtcol_H_
#define _TransmissionCommuicationProtcol_H_



#include "main.h"

typedef struct TransmissionCommuicationProtcol
{
	int DataLength;  				//指令长度
	unsigned char *Data_p;	//指令指针
} Transmission_t;



#endif



/*
	传输协议：
		第一：传输指令
		|__"SP"__|__Comm_byte__|__"H:"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
		第二：传输数据
		|__"SP"__|__Comm_byte__|__"H:"__|__StartAddress__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
*/
#ifndef _TransmissionCommuicationProtcol_H_
#define _TransmissionCommuicationProtcol_H_



#include "main.h"
#include "CircularQueueStruct.h"


#endif


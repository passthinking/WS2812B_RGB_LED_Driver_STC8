
/*
	传输协议：
		第一：传输指令
		|__"SP"__|__Comm_byte__|__"T:"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
		第二：传输数据
		|__"SP"__|__Comm_byte__|__"T:"__|__StartAddress__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
*/

#include "TransmissionCommuicationProtcol.h"

unsigned char xdata dataBuff[256];
CircularQueue_t xdata dataBuff_Circular = { dataBuff, 256, 0, 0, 0 };


void receiverDataLoop( unsigned char ch )
{
	
}



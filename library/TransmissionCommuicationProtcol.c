
/*
	传输协议：
		第一：传输指令
		|__"SP"__|__Comm_byte__|__"T:"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
		第二：传输数据
		|__"SP"__|__Comm_byte__|__"T:"__|__StartAddress__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
*/

#include "TransmissionCommuicationProtcol.h"

unsigned char headCharFlag[2] = "SP";
unsigned char titleCharFlag[2] = "T:";
unsigned char dataCharFlag[2] = "D:";
unsigned char endCharFlag[2] = "ED";

//接收字节计数
int receiverByteCount = 0;
//接收的值指令还是数据
unsigned char Comm_Data_type = 0;
//接收指令字节计数
int receiverCommByteCount = 0;

Transmission_Comm_t Trans_Comm;

/**
 * 接收数据
 */
void receiver(unsigned char ch )
{
	if( receiverByteCount < 2 )   //判断是否获取headCharFlag
	{
		if( ch == headCharFlag[ receiverByteCount ] ) 
		{
			receiverByteCount ++;
		}
		else
		{
			receiverByteCount = 0;
		}
		
	}else if ( receiverByteCount == 2 ) //判断是指令函数数据
	{
		Comm_Data_type = ch;
		receiverCommByteCount = 0;		//清除指令字节接收

	}else if ( receiverByteCount < (2 + 1) + 2 )  //判断是否titleCharFlag
	{
		if ( ch == titleCharFlag[ receiverByteCount - (2 + 1) ] )
		{
			receiverByteCount ++;
		}else
		{
			receiverByteCount = 0;
		}
		
	}else
	{
		if( Comm_Data_type == 0 )   //指令传输
		{
			if( receiverCommByteCount == 0 )
			{
				Trans_Comm.DataLength = ch;		//接收传输数据
				receiverCommByteCount ++;
			}else if(receiverCommByteCount < (1 + 2) )
			{
				if( dataCharFlag[ receiverCommByteCount - 1] == ch )
				{
					receiverCommByteCount ++;
				}else
				{
					receiverCommByteCount = 0;
					receiverByteCount = 0;
				}
			}else if( receiverCommByteCount < ( 1 + 2) + Trans_Comm.DataLength )
			{
				Trans_Comm.Data_p[ receiverCommByteCount - ( 1 + 2 ) ] = ch;
			}else if ( receiverCommByteCount < ( 1 + 2) + Trans_Comm.DataLength + 2 )
			{
				if( endCharFlag[ receiverCommByteCount - (( 1 + 2) + Trans_Comm.DataLength)  ] == ch )
				{
					receiverCommByteCount ++;
				}else
				{
					receiverCommByteCount = 0;
					receiverByteCount = 0;
				}
			}
			
			
			
		}
	}
}





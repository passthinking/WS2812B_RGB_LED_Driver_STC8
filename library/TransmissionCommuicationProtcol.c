
/*
	传输协议：
		|__"SP"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|		
*/

#include "TransmissionCommuicationProtcol.h"

unsigned char code headCharFlag[2] = "SP";
unsigned char code dataCharFlag[2] = "D:";
unsigned char code endCharFlag[2]  = "ED";

//接收字节计数
int receiverByteCount = 0;
//累加和
unsigned char AddCheckValue = 0;

unsigned char xdata receiverDataBuff_ONE[ 256 ];
unsigned char xdata receiverDataBuff_TWO[ 256 ];

Transmission_t * ArrayTransBuff[2];

unsigned char countBuff = 0;

/**********************************************************
 * 初始化
 **********************************************************/
void initReceiver(Transmission_t *trans)
{
	trans->DataLength = 0;
	trans->Data_p = receiverDataBuff_ONE;
}

/**********************************************************
 * 接收数据
 **********************************************************/
void receiverLoop(unsigned char ch, Transmission_t *trans)
{
	if( receiverByteCount == 0 )			//headCharFlag[ 0 ] = S
	{
		if( headCharFlag[0] == ch )
		{
			receiverByteCount ++;
			AddCheckValue += ch;
		}
	}else if( receiverByteCount == 1 )
	{
		if( headCharFlag[1] == ch )     //headCharFlag[ 1 ] = P
		{
			receiverByteCount ++;
			AddCheckValue += ch;
		}else
		{
			receiverByteCount = 0;
			AddCheckValue = 0;
		}
	}else if( receiverByteCount == 2 )//trans->DataLength && 0x00FF<< 8;
	{
		trans->DataLength = ch;
		trans->DataLength <<= 8;
		receiverByteCount ++;
		AddCheckValue += ch;
	}else if( receiverByteCount == 3 )//trans->DataLength | 0x00FF;
	{
		trans->DataLength |= ch;
		receiverByteCount ++;
		AddCheckValue += ch;
	}else if( receiverByteCount == 4 )//dataCharFlag[ 0 ] = D
	{
		if(dataCharFlag[0] == ch )
		{
			receiverByteCount ++;
			AddCheckValue += ch;
		}else
		{
			receiverByteCount = 0; 
			AddCheckValue = 0;
		}
	}else if( receiverByteCount == 5 )//dataCharFlag[ 1 ] = :
	{
		if(dataCharFlag[1] == ch )
		{
			receiverByteCount ++;
			AddCheckValue += ch;
		}else
		{
			receiverByteCount = 0; 
			AddCheckValue = 0;
		}
	}else if( receiverByteCount < 5 + trans->DataLength )  //接收数据
	{
		trans->Data_p[ receiverByteCount - 6 ] = ch;
		receiverByteCount ++;
		AddCheckValue += ch;
	}else if( receiverByteCount == 5 + trans->DataLength )//endCharFlag[0] = E
	{
		if( endCharFlag[0] == ch )
		{
			receiverByteCount ++;
			AddCheckValue += ch;
		}else
		{
			receiverByteCount = 0; 
			AddCheckValue = 0;
		}
	}else if( receiverByteCount == 5 + trans->DataLength + 1 )//endCharFlag[0] = D
	{
		if( endCharFlag[1] == ch )
		{
			receiverByteCount ++;
			AddCheckValue += ch;
		}else
		{
			receiverByteCount = 0; 
			AddCheckValue = 0;
		}
	}else if( receiverByteCount == 5 + trans->DataLength + 2 )//AddCheckValue 
	{
		if( AddCheckValue == ch )
		{
			
		}
		receiverByteCount = 0; 
		AddCheckValue = 0;
	
	}
	
}

















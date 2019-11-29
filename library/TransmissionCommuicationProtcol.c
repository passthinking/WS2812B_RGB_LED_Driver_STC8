
/*
	传输协议：
		第一：传输指令
		|__"SP"__|__Comm_byte__|__"T:"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
		第二：传输数据
		|__"SP"__|__Comm_byte__|__"T:"__|__StartAddress__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
*/

#include "TransmissionCommuicationProtcol.h"


unsigned char code HaedFlagChar[2] = {'P','S'};
unsigned char code TitilFlagChar[2] = {'T',':'};
unsigned char code DataFlagChar[2] = {'D',':'};
unsigned char ReceiverModeCount = 0;
unsigned char CommondType = 0;

unsigned char DataLength = 0;
unsigned int  StartAddress = 0;

unsigned char CommCount = 0;
unsigned char DataCount = 0;

unsigned char reciverDateBuff[256];

void ReceiverDataLoop( unsigned char ch )
{
	switch( ReceiverModeCount )
	{
		case 0:
			if( ch == HaedFlagChar[0] )
			{
				ReceiverModeCount ++;
				CommondType = 0;
			}
			break;
		case 1:
			if( ch == HaedFlagChar[1] )
			{
				ReceiverModeCount ++;
			}
			else
			{
				if( ch == HaedFlagChar[0] )
				{
					ReceiverModeCount = 1;
				}
				else
				{
					ReceiverModeCount = 0;
				}
			}
			break;
		case 2:
			CommondType = ch;
			ReceiverModeCount ++;
			break;
		case 3:
			if(ch == TitilFlagChar[0] )
			{
				ReceiverModeCount ++;
			}
			else
			{
				ReceiverModeCount = 0;
			}
			break;
		case 4:
			if( ch == TitilFlagChar[1] )
			{
				ReceiverModeCount ++;
				CommCount = 0;
				DataCount = 0;
			}
			else
			{
				ReceiverModeCount = 0;
			}
			break;
		default:
			switch( CommondType )
			{
				case 1:
					CommType( ch , & ReceiverModeCount );
					break;
				case 2:
					DataType( ch , & ReceiverModeCount );
					break;
				default:
						ReceiverModeCount = 0;
					break;
			}
			break;	
	}
}



void CommType( unsigned char ch , unsigned char *count )
{
	if( CommCount == 0 )
	{
		DataLength = ch;
		CommCount ++;
	}
	else if( CommCount == 1 )
	{
		if( ch == DataFlagChar[0] )
		{
			CommCount ++;
		}
		else
		{
			*count = 0;
		}
	}
	else if( CommCount == 2 )
	{
		if( ch == DataFlagChar[1] )
		{
			CommCount ++;
		}
		else
		{
			*count = 0;
		}
	}
	else 
	{
		
	}

}


void DataType( unsigned char ch , unsigned char *count)
{

}






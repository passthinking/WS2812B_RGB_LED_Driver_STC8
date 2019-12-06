
/*
	����Э�飺
		|__"SP"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|		
*/

#include "TransmissionCommuicationProtcol.h"
#include "STC8_TIMER2_UART.h"

unsigned char code headCharFlag[2] = "SP";
unsigned char code dataCharFlag[2] = "D:";
unsigned char code endCharFlag[2]  = "ED";

//�����ֽڼ���
int receiverByteCount = 0;
//�ֽڳ���
unsigned int receiverDataLength = 0;
//�ۼӺ�
unsigned char AddCheckValue = 0;

unsigned char xdata receiverDataBuff_ONE[ 256 ];
unsigned char xdata receiverDataBuff_TWO[ 256 ];

Transmission_t trans;

unsigned char countBuff = 0;


/**********************************************************
 * ��ʼ��
 **********************************************************/
void initReceiver(void)
{
	trans.DataLength_ONE = 0;
	trans.DataLength_TWO = 0;
	trans.Data_p_ONE = receiverDataBuff_ONE;
	trans.Data_p_TWO = receiverDataBuff_TWO;
	trans.Receive_completion_flag = 0;
	trans.Receive_Count = 0;
}

/**********************************************************
 * ��������
 **********************************************************/
void receiverLoop(unsigned char ch)
{
	UART1_Send( receiverByteCount >> 8 );
	UART1_Send( receiverByteCount  );
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
		receiverDataLength = ch;
		receiverDataLength <<= 8;
		receiverByteCount ++;
		AddCheckValue += ch;
	}else if( receiverByteCount == 3 )//trans->DataLength | 0x00FF;
	{
		receiverDataLength |= ch;
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
	}else if( receiverByteCount < 5 + receiverDataLength )  //��������
	{
		if( trans.Receive_Count == 0 )
		{
			trans.Data_p_ONE[ receiverByteCount - 6 ] = ch;
		}else
		{
			trans.Data_p_TWO[ receiverByteCount - 6 ] = ch;
		}
		receiverByteCount ++;
		AddCheckValue += ch;
	}else if( receiverByteCount == 5 + receiverDataLength )//endCharFlag[0] = E
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
	}else if( receiverByteCount == 5 + receiverDataLength + 1 )//endCharFlag[0] = D
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
	}else if( receiverByteCount == 5 + receiverDataLength + 2 )//AddCheckValue 
	{
		if( AddCheckValue == ch )
		{
			if( trans.Receive_Count == 0 )
			{
				trans.DataLength_ONE = receiverDataLength;
				trans.Receive_Count = 1;
			}else
			{
				trans.DataLength_TWO = receiverDataLength;
				trans.Receive_Count = 0;
			}
			trans.Receive_completion_flag = 1;
		}
		receiverByteCount = 0;
		AddCheckValue = 0;
	}
}

/**********************************************************
 * ��ȡ����
 **********************************************************/
void getReceiverData( unsigned char *data_p_one, unsigned char *data_p_two, unsigned int dataLimt )
{
	int i = 0;
	int count = 0;
	if( trans.Receive_completion_flag == 1 )
	{
		if( trans.Receive_Count == 0 )
		{
			if( trans.DataLength_ONE < dataLimt )
			{
				count = trans.DataLength_ONE;
			}else
			{
				count = dataLimt;
			}
			if( trans.Data_p_ONE[0] == 0 )
			{
				for( i = 0; i < count; i ++ )
				{
					data_p_one[ i ] = trans.Data_p_ONE[ i ];
				}
			}else if( trans.Data_p_ONE[0] == 1 )
			{
				for( i = 0; i < count; i ++ )
				{
					data_p_two[ i ] = trans.Data_p_ONE[ i ];
				}
			}
		}else
		{
			if( trans.DataLength_TWO < dataLimt )
			{
				count = trans.DataLength_TWO;
			}else
			{
				count = dataLimt;
			}
			if( trans.Data_p_TWO[0] == 0 )
			{
				for( i = 0; i < count; i ++ )
				{
					data_p_one[ i ] = trans.Data_p_TWO[ i ];
				}
			}else if( trans.Data_p_TWO[0] == 1 )
			{
				for( i = 0; i < count; i ++ )
				{
					data_p_two[ i ] = trans.Data_p_TWO[ i ];
				}
			}
		}
		trans.Receive_completion_flag = 0;
	}
}














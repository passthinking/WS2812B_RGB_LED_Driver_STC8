
/*
	����Э�飺
		��һ������ָ��
		|__"SP"__|__Comm_byte__|__"T:"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
		�ڶ�����������
		|__"SP"__|__Comm_byte__|__"T:"__|__StartAddress__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
*/

#include "TransmissionCommuicationProtcol.h"

unsigned char headCharFlag[2] = "SP";
unsigned char titleCharFlag[2] = "T:";
unsigned char dataCharFlag[2] = "D:";
unsigned char endCharFlag[2] = "ED";

//�����ֽڼ���
int receiverByteCount = 0;
//���յ�ֵָ�������
unsigned char Comm_Data_type = 0;
//����ָ���ֽڼ���
int receiverCommByteCount = 0;

Transmission_Comm_t Trans_Comm;

/**
 * ��������
 */
void receiver(unsigned char ch )
{
	if( receiverByteCount < 2 )   //�ж��Ƿ��ȡheadCharFlag
	{
		if( ch == headCharFlag[ receiverByteCount ] ) 
		{
			receiverByteCount ++;
		}
		else
		{
			receiverByteCount = 0;
		}
		
	}else if ( receiverByteCount == 2 ) //�ж���ָ�������
	{
		Comm_Data_type = ch;
		receiverCommByteCount = 0;		//���ָ���ֽڽ���

	}else if ( receiverByteCount < (2 + 1) + 2 )  //�ж��Ƿ�titleCharFlag
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
		if( Comm_Data_type == 0 )   //ָ���
		{
			if( receiverCommByteCount == 0 )
			{
				Trans_Comm.DataLength = ch;		//���մ�������
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






/*
	����Э�飺
		��һ������ָ��
		|__"SP"__|__Comm_byte__|__"H:"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
		�ڶ�����������
		|__"SP"__|__Comm_byte__|__"H:"__|__StartAddress__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|
		
*/
#ifndef _TransmissionCommuicationProtcol_H_
#define _TransmissionCommuicationProtcol_H_



#include "main.h"

typedef struct TransmissionCommuicationProtcol_Comm
{
	int DataLength;  		//指令长度
	unsigned char *Data_p;	//指令指针
} Transmission_Comm_t;

typedef struct TransmissionCommuicationProtcol_Data
{
	int StartAddress;		//数据起始地址
	int Datalength;			//数据长度
	unsigned char *Data_p;	//数据指针
} Transmission_Data_t;


#endif


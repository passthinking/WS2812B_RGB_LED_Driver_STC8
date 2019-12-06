

/*
	传输协议：
		|__"SP"__|__DataLength__|__"D:"__|___...data...__|__ED__|__AddCheckValue__|		
*/

#ifndef _TransmissionCommuicationProtcol_H_
#define _TransmissionCommuicationProtcol_H_

#include "main.h"

typedef struct TransmissionCommuicationProtcol
{
	int DataLength_ONE;  				//指令长度
	unsigned char *Data_p_ONE;	//指令指针
	int DataLength_TWO;  				//指令长度
	unsigned char *Data_p_TWO;	//指令指针
	unsigned char Receive_completion_flag; //接收完成
	unsigned char Receive_Count;  //接收
} Transmission_t;


void initReceiver(void); 							//初始化
void receiverLoop(unsigned char ch); 	//接收数据
void getReceiverData( unsigned char *data_p_one, unsigned char *data_p_two, unsigned int dataLimt ); //获取数据
void sendData( unsigned char *ch_p, unsigned int dataLength ); //发送数据


#endif


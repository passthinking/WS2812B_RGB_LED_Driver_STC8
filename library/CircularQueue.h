#ifndef _CircularQueue_H_
#define _CircularQueue_H_



#define CircularQueueLength  256 

extern unsigned char xdata circularQueueBuff[CircularQueueLength];


char add_Data_CircularQueue(unsigned char ch);
char get_Data_CircularQueue(unsigned char *ch);
unsigned int get_DataLength();

#endif 



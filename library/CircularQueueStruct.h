#ifndef _CircularQueueStruct_H_
#define _CircularQueueStruct_H_


typedef struct CircularQueueStruct
{
	unsigned char * circularQueueBuff;
	unsigned int CircularQueueLength; 
	unsigned int DataLength;
	unsigned int StartPointer;
	unsigned int EndPointer;
} CircularQueue_t;

char add_Data_CircularQueue_Struct( CircularQueue_t *circular, unsigned char ch);
char get_Data_CircularQueue_Struct( CircularQueue_t *circular, unsigned char *ch);
unsigned int get_DataLength_Struct( CircularQueue_t *circular);

#endif 

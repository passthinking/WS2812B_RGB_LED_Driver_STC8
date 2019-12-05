
#include "CircularQueueStruct.h"


char add_Data_CircularQueue_Struct( CircularQueue_t *circular, unsigned char ch)
{
	if( ( circular->DataLength < circular->CircularQueueLength) && ( circular->DataLength >= 0 ) )
	{
		circular->circularQueueBuff[ circular->EndPointer ] = ch;
		circular->DataLength ++;
		circular->EndPointer ++;
		if( circular->EndPointer >= circular->CircularQueueLength )
		{
			circular->EndPointer = 0;
		}
		return 1;
	}
	else
	{
		return -1;
	}
}

unsigned int get_DataLength_Struct( CircularQueue_t *circular)
{
	return circular->DataLength ;
}

char get_Data_CircularQueue_Struct( CircularQueue_t *circular,unsigned char *ch)
{
	if( circular->DataLength > 0)
	{
		*ch = circular->circularQueueBuff[ circular->StartPointer ];
		circular->DataLength --;
		circular->StartPointer ++;
		if( circular->StartPointer  >= circular->CircularQueueLength )
		{
			circular->StartPointer = 0;
		}
		return 1;
	}
	else
	{
		return -1;
	};
}

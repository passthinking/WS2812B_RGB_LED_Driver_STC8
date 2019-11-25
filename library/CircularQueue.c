

#include "CircularQueue.h"

unsigned int DataLength = 0;
unsigned int StartPointer = 0;
unsigned int EndPointer = 0;

char add_Data_CircularQueue(unsigned char ch)
{
	if( (DataLength < CircularQueueLength) && ( DataLength >= 0 ) )
	{
		circularQueueBuff[ EndPointer ] = ch;
		DataLength ++;
		EndPointer ++;
		if( EndPointer >= CircularQueueLength )
		{
			EndPointer = 0;
		}
		return 1;
	}
	else
	{
		return -1;
	}
}

unsigned int get_DataLength()
{
	return DataLength ;
}

char get_Data_CircularQueue(unsigned char *ch)
{
	if( DataLength > 0)
	{
		*ch = circularQueueBuff[ StartPointer ];
		DataLength --;
		StartPointer ++;
		if( StartPointer  >= CircularQueueLength )
		{
			StartPointer = 0;
		}
		return 1;
	}
	else
	{
		return -1;
	};
}

#include<stdlib.h>
typedef struct iterator{
	iter* next;
	void* data;
	size_t dataSize;
} iterator;

#include<stdlib.h>
typedef struct iterator{
	iter* next;
	void* data;
	size_t dataSize;
} iterator;

//returns an iterator generated from a list
iterator iter(size_t dataTypeSize,size_t listLen,void* list);
iterator iter_from_func(size_t dataTypeSize,void* (*func)(void));
iterator copy_iter(iterator vals);
void map(size_t (*func)(void*),iterator* vals);
void mapKnow(size_t (*func)(void*,size_t),iterator* vals);
#ifdef pagwinSpecialStringLib
iterator iter_from_string(string str);
#endif

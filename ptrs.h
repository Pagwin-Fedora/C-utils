#include <stdlib.h>
#ifndef memincl
#define memincl
typedef struct unique_ptr{
	void* ptr;
	() free;
};
typedef struct shared_ptr{
	void* ptr;
	size_t* ref_count;
	() free;
}
void dropU(unique_ptr ptr);
void dropS(shared_ptr ptr);
#endif

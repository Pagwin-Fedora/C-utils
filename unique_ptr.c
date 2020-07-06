#include<ptrs.h>
void dropU(unique_ptr* ptr){
	ptr->free(ptr->ptr);
}
void dropS(shared_ptr* ptr){;
	if(!(--*(ptr->ref_count)))
		ptr->free(ptr->ptr);
}
shared_ptr copyShared(shared_ptr ptr){
	*ptr.ref_count++;
}
() sharedGenerator(() alloc, () free){
	
}
() uniqueGenerator(() alloc, () free){
	
}


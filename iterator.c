#include<iterator.h>
//returns an iterator generated from a list
iterator iter(size_t dataTypeSize,size_t listLen,void* list){
	iterator returnVal;
	iterator* current = &returnVal;
	for(size_t i = 0;i<listLen;i++){
		current[i].dataSize = datatypeSize;
		current[i].data = malloc(dataTypeSize);
		memcpy(current[i].data,list+i*dataTypeSize,dataTypeSize);
		current[i].next = malloc(sizeof(iterator));
		current = current.next
	}
	return return_val;
}
iterator iter_from_func(size_t dataTypeSize,void* (*func)(void)){
	
}
//returns a copy of the iterator
iterator copy_iter(iterator vals){
	iterator current;
	current.dataSize = vals.dataSize
	current.data = malloc(vals.dataSize);
	memcpy(current.data,vals.data,vals.dataSize);
	current.next = NULL;
	if(vals.next)
		current.next = &copy_iter(*vals.next);
	return current;
}
void map(size_t (*func)(void*),iterator* vals){
	while(vals){
		vals->dataSize = 	
	}
}
void mapKnow(size_t (*func)(void*,size_t)){
	
}


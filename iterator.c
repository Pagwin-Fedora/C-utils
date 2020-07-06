#include<iterator.h>
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
	void* currentVal = func();
	iterator returnVal;
	iterator* currentIter = &returnVal;
	while(currentVal){
		currentIter->data = currentVal;
		currentIter->dataSize = dataTypeSize;
		currentVal = func();
		if(currentVal){
			iterator next;
			currentIter->next = &next;
			currentIter = currentIter->next;
		}
	}
	currentIter.next = NULL;
	return returnVal;
}
#ifdef pagwinSpecialStringLib
iterator iter_from_string(string str){
	return iter(sizeof(char),str.len,str.raw);
}
#endif
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
		vals->dataSize = func(vals->data);
		vals=vals->next;
	}
}
void mapKnow(size_t (*func)(void*,size_t),iterator* vals){
	while(vals){
		vals->dataSize = =func(vals->data,vals->dataSize);
		vals=vals->next;
	}
}

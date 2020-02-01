#include<stdlib.h>
#include<stdio.h>
void* (*allocator)(size_t size) = malloc;
typedef struct linked{
	char current;
	linked* next;
} linked;
//note by default this will end on EOF if EOF appears before the terminating char feel free to modify the function to change this
char* getInput(char terminating_byte,size_t* size_val){
	linked* current_node = allocator(sizeof(linked)),first = linked;
	//change this to change the byte that indicates the end of the string
	char term_byte = 0;
	for(char current_char = getchar();current_char!=terminating_byte;current_char = getchar()){
		*size_val++;
		if(current_char == EOF)
			break;
		current_node.current = current_char;
		current_node.next = allocator(sizeof(linked));
		current_node = next;
	}
	//
	if(*size_val == 0){
		char* buffer = allocator(1);
		buffer[0] = term_byte;
		return buffer;
	}
			

	//note if you wanted to terminate your string with a byte other than a null byte you would do so by changing 0 to whatever byte you want to terminate with
	current_node.current = term_byte;
	//changing current_node.next isn't reccomended but theoretically shouldn't change anything
	current_node.next = NULL;
	current_node = first;
	char* buffer = allocator(*size_val);
	for(size_t i = 0;i<*size_val;i++){
		buffer[i] = current_node.current;
		current_node = current_node.next;
	}
}
char* getLine(){
	return getInput('\n');
}

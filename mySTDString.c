#include"mySTDString.h"
#include<string.h>//not sure if I need an ifndef somewhere here
#include<stdlib.h>//not sure if this is a good idea
void* (*allocator)(size_t) = malloc;
void use_custom_alloc(void* (*alloc)(size_t)){
	allocator = alloc;
}
string construct_string(passed_in_string_val from_val){
	if(from_val.string_struct.sanity_byte == 0x69){
		return from_val.string_struct;
	}
	else{
		string return_val;
		return_val.raw = from_val.raw_string;
		return_val.len = strlen(return_val.raw);
		return_val.sanity_byte = 0x69;
		return return_val;
	}
}
string concat_string(passed_in_string_val first, passed_in_string_val second){
	string first_internal, second_internal;
	//construct_string is used because it does the same thing that would be done here and this is more succinct
	first_internal = construct_string(first);
	second_internal = construct_string(second);
	//set up return val
	string return_val;
	return_val.len = first_internal.len+second_internal.len;
	return_val.raw = allocator(return_val.len+1);
	return_val.sanity_byte = 0x69;
	memcpy(return_val.raw,first_internal.raw,first_internal.len);
	memcpy(return_val.raw+first_internal.len,second_internal.raw,second_internal.len);
	return_val.raw[return_val.len-1] = 0;
	return return_val;
}
size_t firstSubstringLoc(passed_in_string text,passed_in_string substring){
	string main_text, subtext;
	main_text = construct_string(text);
	subtext = construct_string(substring);
	for(int i = 0;i<main_text.len;i++){
		for(int j = 0;j<subtext.len;j++){
			if(main_text[i+j]==subtext[j]){
				if(j==subtext.len-1)
					return i;
				continue;
			}
			else{
				break;	
			}
		}
	}
	//this is kinda dumb but neccesary because size_t is unsigned so I can't use -1(if this gets too annoying change the return time to long int and set this to -1) but technically this is a bad solution because if the len of the actual string is max(size_t) then this function will return 0
	return text.len+1; 
}
size_t* allSubstringLocs(passed_in_string text, passed_in_string subtext){
	struct size_t_linked{
		size_t_linked* prev;
		size_t val;
		size_t_linked* next;
	}
	string main_text,substring;
	main_text = construct(text);
	substring = construct(subtext);
	size_t_linked current;
	current.prev = NULL;
	size_t count = 0;
	for(size_t i = 0;i<main_text.len;i++){
		for(size_t j<substring.len;j++){
			if(main_text[i+j]==subtext[j]){
				if(subtext.len-1==j){
					current.val = i;
					size_t_linked temp;
					temp.prev = &current;
					current.next = &temp;
					current = temp;
					count++;
				}
				continue;
			}
			else{
				break;
			}
		}
	}
	if(count == 0)
		return NULL;
	else{
		size_t* return_val = malloc(size_of(size_t)*count);
		for(size_t i = 0;i<count;i++){
			return_val[i] = current;
			current = *current.prev
		}
		return return_val;
	}
}
char** stringArrayToRaw(string* strings,size_t amount){
	char** output_array allocator(8*amount);
	for(int i = 0;i<amount;i++){
		memcpy(output_array[i],strings[i].raw,strings[i].len);
	}
	return output_array;
}

#include<stddef.h>
//note while the string struct is reccomended it shouldn't be neccesary to pass it to any function in this lib(though if a function is called repeatedly with the same value a string struct is reccomended so the function doesn't have to recauculate the string struct every time) also if a char* is provided instead of a string memory safety/lack of segmentation fault is not garunteed
typedef struct string{
	char* raw;//a null terminated string for compatibility reasons(theoretically you could just pass a string struct to anything that would accept a char*)
	size_t len;
	char sanity_byte;//should always be set to 0x69 so any function to double check that it got passed a string struct and will have the correct length under len
} string;
typedef union passed_in_string_val{
	string string_struct;
	char* raw_string;
} passed_in_string_val;
#define pagwinSpecialStringLib 1

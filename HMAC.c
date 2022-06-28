#include <stdlib.h>
#include <stddef.h>
#include <string.h>
//this file is a mess and can 100% be improved on for readability
//HMAC takes the hash function, the hash function's block and digest sizes(I forget what those mean but they're needed to calculate things) the password to HMAC with the hash function the length of the password and some data to be put with the password and then spits out a
char* HMAC(void* (*hash_func)(void*,size_t),size_t hash_func_block_size,size_t hash_func_digest_size,char* password, size_t password_len, char* data, size_t data_len){
    //Function for getting the HMAC Block(inside the HMAC function to prevent user usage) Edit: past me doesn't know what header files are for, the reason it's inside this function is to make it clear it's only used here
    inline void* HMAC_BLOCK(void* input,size_t input_len, size_t block_size, size_t digest_size,void* (*hasher)(void*,size_t)){
			char* output = malloc(block_size);

			//zeros out the remaining values if the input isn't large enough
			if(input_len<block_size){
				memcpy(output,input,input_len);
				for(size_t i = input_len; i<block_size;i++){
					output[i] = 0;
				}
				return output;
			}
			//if the input is too large we hash and zero it till it reaches the block size
			if(input_len>block_size){
				void* hash = hasher(input,input_len);
				memcpy(output, hash, digest_size);
				free(hash);
				for(size_t i = digest_size;i<block_size;i++){
					output[i] = 0;
				}
				return output;
			}
			//if the input is the blocksize we can just return the input
			if(input_len==block_size){
				memcpy(output,input,input_len);
				return output;
			}
			//if you get back a NULL from this function it's unintended behavior and something fucky is going on
			return NULL;
    }

    //getting our HMAC block
    char* block = HMAC_BLOCK(password,password_len,hash_func_block_size,hash_func_digest_size,hash_func);
    //error checking
    if(block == NULL) return NULL;
    
    //generating the opadding
    char* opad_block = malloc(hash_func_block_size);
    for(size_t i = 0;i<hash_func_block_size;i++){
	opad_block[i] = 0x5c^block[i];
    }
    //generating the ipadding
    char* ipad_block = malloc(hash_func_block_size+data_len);
    for(size_t i = 0;i<hash_func_block_size;i++){
    	ipad_block[i] = 0x36^block[i];
    }
    //getting the final product with ipadding and hashing as an intermediate product towards the final HMAC
    memcpy((ipad_block+hash_func_block_size),data,data_len);
    void* ipad_output = (*hash_func)(ipad_block,hash_func_block_size+data_len);
    free(ipad_block);
    
    //gathering the hash input all toegether
    void* hash_input = malloc(hash_func_block_size+hash_func_digest_size);
    memcpy(hash_input,opad_block,hash_func_block_size);
    memcpy((hash_input+hash_func_block_size),ipad_output,hash_func_digest_size);
    
    //taking the final hash for our output Edit: I forget if output is actually a string or if I just didn't have a better data type for this but given I don't hexify it I'm gonna guess it's binary output
    char* output = (*hash_func)(hash_input,hash_func_block_size+hash_func_digest_size);

    //freeing all the memory we used and returning the output
    free(hash_input);
    free(opad_block);
    free(ipad_output);
    //IF YOU GET SOME WEIRD MEMORY GLITCH USING THIS FUNCTION LOOK HERE I DON'T REMEMBER IF I DEALLOCATED THIS SOMEWHERE ELSE BUT I THINK I DIDN'T
    free(block);
    return output;
}
//takes in binary data with it's length and spits out the hex
char* hexify(unsigned char* bin_data,size_t data_len){
	//yes there is a way to make this lookup table unnecessary but no you shouldn't do it
	char lookup[] = "0123456789ABCDEF";
	char* output = malloc(data_len*2);
	for(size_t i = 0;i<data_len;i++){
		char first = bin_data[i]/16%16;
		char second = bin_data[i]%16;
		first = lookup[first];
		second = lookup[second];
		output[2*i] = first;
		output[2*i+1] = second;
	}
	return output;
}

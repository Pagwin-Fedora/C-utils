#include "headers/HMACSHA1.h"
//this file is a mess and can 100% be improved on for readability
char* HMAC(void* (*hash_func)(void*,size_t),size_t hash_func_block_size,size_t hash_func_digest_size,char* password, size_t password_len, char* data, size_t data_len){
	void* HMAC_BLOCK(void* input,size_t input_len, size_t block_size, size_t digest_size,void* (*hasher)(void*,size_t)){
		char* output = malloc(block_size);
		if(input_len<block_size){
			memcpy(output,input,input_len);
			for(size_t i = input_len; i<block_size;i++){
				output[i] = 0;
			}
			return output;
		}
		if(input_len>block_size){
			void* hash = hasher(input,input_len);
			memcpy(output, hash, digest_size);
			free(hash);
			for(size_t i = digest_size;i<block_size;i++){
				output[i] = 0;
			}
			return output;
		}
		if(input_len==block_size){
			memcpy(output,input,input_len);
			return output;
		}
		//if you get back a NULL from this function it's unintended behavior and something fucky is going on
		return NULL;
	}
	char* block = HMAC_BLOCK(password,password_len,hash_func_block_size,hash_func_digest_size,hash_func);
	char* opad_block = malloc(hash_func_block_size);
	for(size_t i = 0;i<hash_func_block_size;i++){
		opad_block[i] = 0x5c^block[i];
	}
	char* ipad_block = malloc(hash_func_block_size+data_len);
	for(size_t i = 0;i<hash_func_block_size;i++){
		ipad_block[i] = 0x36^block[i];
	}
	memcpy((ipad_block+hash_func_block_size),data,data_len);
	void* ipad_output = (*hash_func)(ipad_block,hash_func_block_size+data_len);
	free(ipad_block);
	void* hash_input = malloc(hash_func_block_size+hash_func_digest_size);
	memcpy(hash_input,opad_block,hash_func_block_size);
	memcpy((hash_input+hash_func_block_size),ipad_output,hash_func_digest_size);
	char* output = (*hash_func)(hash_input,hash_func_block_size+hash_func_digest_size);
	free(hash_input);
	free(opad_block);
	free(ipad_output);
	return output;
}
char* hexify(unsigned char* bin_data,size_t data_len){
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
void* SHA1HMAC(void* password, size_t password_len, void* data, size_t data_len){
	return hexify(HMAC(SHA1Digest,64,20,password,password_len,data,data_len),20);
}
void* SHA1Digest(void* input, size_t input_len){
	void* output = malloc(20);
	SHA1((unsigned char*)input,input_len,(unsigned char*)output);
	return output;
}

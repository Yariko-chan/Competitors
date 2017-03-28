#include <stdbool.h>
#include <string.h>

#include "constants.h"

/*
returns next char from ADM_PASSW every call
if last char reached, starts from first again
@reset - if true, starts from first
*/
char get_key_char(bool reset) {
	int length = strlen(ADM_PASSW);
	static int cur_index;

	// reset or some error states
	if (reset || cur_index < 0 || cur_index > length - 1) {
		cur_index = 0; // default value
	}
	else {
		cur_index = (cur_index + 1) / length;
	}

	return ADM_PASSW[cur_index];
}

/*
encrypts @sourse with xor-encryption
key is string used in get_key_char()
@size - size of @sourse in bytes
*/
void encrypt(char* sourse, const size_t size) {

	// set to zero
	//sourse[0] = sourse[0] ^ get_key_char(true);
	//for (int i = 1; i < (int) size; i++) {
	//	sourse[i] = sourse[i] ^ get_key_char(false);
	//}
	for (int i = 0; i < (int)size; i++) {
		sourse[i] = sourse[i] ^ ADM_PASSW[i % strlen(ADM_PASSW)]; 
	}
}

/*
decrypts @sourse with xor-encryption
key is string used in get_key_char()
@size - size of @sourse in bytes
*/
char* decrypt(char* sourse, const size_t size) {

	// same as encrypt, but to functions to make it clear
	// and also for have opportunity to use other encryption later
	encrypt(sourse, size);
}
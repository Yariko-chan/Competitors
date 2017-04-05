#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "input.h"

/*
handling error
print @message to stderr
exit if error @critical for program
*/
void error(const char* message, const _Bool critical) {
	perror(message);
	if (critical) {
		fprintf(stderr, ERR_EXIT_CONFIRM);
		clean_stdin();
		getchar();
		exit(EXIT_FAILURE);
	}
}

/*
checks if symbol is sign for condition
*/
bool is_char_sign(const char c) {
	if (c == '>' || c == '<' || c == '=') {
		return true;
	}
	return false;
}

/* 
returns symbol according to number in arguments
*/
char get_char_sign(char sign) {
	switch (sign) {
	case -1: return '<';
	case  1: return '>';
	case  0: return '=';
	default: return '?';
	}
}

/*
function for checking sign of number
return 0 if 0; -1 if negative; +1 if positive
*/
int sign(const int x) {
	return (x > 0) - (x < 0);
}
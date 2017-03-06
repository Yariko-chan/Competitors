#include <stdio.h>
#include <stdbool.h>
#include "file.h"

// skip all characters from input entered previously 
// (they can be scanned instead of entered further)
void clean_scan(void) {
	const char NEWLINE = '\n';

	char ch = ' ';
	while ((ch = getchar()) != NEWLINE);
}

// get confirmation (or not) for query in arguments
bool ask_confirm(const char* str) {
	const char YES_ANS = 'y';
	const char NO_ANS = 'n';

	char ans = ' ';
	do
	{
		printf("%s (y/n): ", str);
		ans = getchar();
		clean_scan();
	} while (ans != YES_ANS && ans != NO_ANS);
	if ('n' == ans)
		return false;
	return true;
}

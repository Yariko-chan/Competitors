#include <stdio.h>
#include <stdbool.h>
#include "file.h"
#include "input.h"

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
		clean_scan();
		ans = getchar();
	} while (ans != YES_ANS && ans != NO_ANS);
	if ('n' == ans)
		return false;
	return true;
}

Account input_account(void)
{
	Account new_a;

	puts("Enter data for new account:");
	clean_scan();
	printf("   Login: ");
	scanf_s("%s", new_a.login, LOGIN_LENGTH);
	clean_scan();
	printf("Password: ");
	scanf_s("%s", new_a.passw, PASSWORD_LENGTH);
	return new_a;
}

#include <stdio.h>
#include <stdbool.h>

#include "file.h"
#include "input.h"
#include "constants.h"

// skip all characters from input entered previously 
// (they can be scanned instead of entered further)
void clean_scan(void) {
	const char NEWLINE = '\n';

	fseek(stdin, 0, SEEK_END);
	//if (!feof(stdin)) {
	//	char ch = ' ';
	//    while ((ch = getchar()) != NEWLINE  && ch != EOF);
	//}
	
	//while (!feof(stdin)) {
	//	getchar();
	//}
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

Account input_account(void) {
	Account new_a;

	puts("Enter data for new account:");

	printf("   Login: ");
	scanf_s("%s", new_a.login, LOGIN_LENGTH);
	printf("Password: ");
	scanf_s("%s", new_a.passw, PASSWORD_LENGTH);

	return new_a;
}

Player input_player() {
	Player new_p;

	puts("Enter data for new player:");

	printf("%11s: ", "Name");
	scanf_s("%s", new_p.name.name, NAME_LENGTH);
	printf("%11s: ", "Surname");
	scanf_s("%s", new_p.name.surname, NAME_LENGTH);
	printf("%11s: ", "Patronymic");
	scanf_s("%s", new_p.name.patronym, NAME_LENGTH);
	
	printf("%11s: ", "Number");
	scanf_s("%hu", &new_p.number);
	printf("%11s: ", "Age");
	scanf_s("%hu", &new_p.age);
	printf("%11s: ", "Height");
	scanf_s("%hu", &new_p.height);
	printf("%11s: ", "Weight");
	scanf_s("%hu", &new_p.weight);
	
	return new_p;
}

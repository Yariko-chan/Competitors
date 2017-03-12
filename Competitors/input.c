#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "file.h"
#include "input.h"
#include "constants.h"

// skip all characters from input entered previously 
// (they can be scanned instead of entered further)
void clean_stdin(void) {
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
		clean_stdin();
		ans = getchar();
	} while (ans != YES_ANS && ans != NO_ANS);
	if ('n' == ans)
		return false;
	return true;
}

Account input_account(void) {
	Account new_a;

	puts("\nEnter data for new account:");

	printf("   Login(%2d symbols): ", LOGIN_LENGTH);
	scanf_s("%s", new_a.login, LOGIN_LENGTH);
	printf("Password(%2d symbols): ", PASSWORD_LENGTH);
	scanf_s("%s", new_a.passw, PASSWORD_LENGTH);

	return new_a;
}

Player input_player() {
	Player new_p;

	puts("\nEnter data for new player:");

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

void edit_str(char* editable, const char* tag, const size_t length) {
	int pad = 15; // max size of tag and editable
	printf("%*s: %*s New:", pad, tag, pad, editable);

	char* tmp = (char*)calloc(length, sizeof(char));
	read_str_or_skip(tmp, length);
	if (strcmp("", tmp)) {
		strcpy_s(editable, length, tmp);
	}
	free(tmp);
}

void edit_short(unsigned short* editable, const char* tag) {
	int pad = 15; // max size of tag and editable
	printf("%*s: %*d New:", pad, tag, pad, *editable);

	read_hu_or_skip(editable);
}

//scan string of given length
//skips if enter pressed
void read_str_or_skip(char * str, const int length) {
	char ch;
	int i;

	i = 0;
	while ((ch = getchar()) != '\n' && length != i)
	{
		str[i] = ch;
		i++;
	}
}

//scan unsigned short
//skips if enter pressed
void read_hu_or_skip(unsigned short* hu) {
	char ch;
	while ((ch = getchar()) != '\n') // read first char
	{                                // if enter skip
		ungetc(ch, stdin);           // else push readed char back to input strem
		scanf_s("%hu", hu);           // read float
	}
}

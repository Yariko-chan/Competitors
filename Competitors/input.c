#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "file.h"
#include "input.h"
#include "output.h"
#include "constants.h"
#include "filter.h"

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
	printf("%11s: ", "Gender");
	scanf_s(" %c", &new_p.gender, 1);
	
	return new_p;
}

void edit_str(char* editable, const char* tag, const size_t length) {
	int pad = 15; // max size of tag and editable
	printf("%*s: %*s New: ", pad, tag, pad, editable);

	char* tmp = (char*)calloc(length, sizeof(char));
	read_str_or_skip(tmp, length);
	if (strcmp("", tmp)) {
		strcpy_s(editable, length, tmp);
	}
	free(tmp);
}

void edit_short(unsigned short* editable, const char* tag) {
	int pad = 15; // max size of tag and editable
	printf("%*s: %*d New: ", pad, tag, pad, *editable);

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

FilterSet get_filter_set(void) {
	const FilterSet EMPTY_FILTER_SET = {
		{ SIGN_DFLT, VALUE_DFLT },
		{ SIGN_DFLT, VALUE_DFLT },
		{ SIGN_DFLT, VALUE_DFLT },
		{ SIGN_DFLT, VALUE_DFLT },
		{ SIGN_DFLT, VALUE_DFLT },
		{ SIGN_DFLT, VALUE_DFLT },
		'b'
	};

	puts("Add required filter,");
	puts("for example: \"Age :> 20\" to get all players over 20 years\n");
	puts("Accepted signs: >  < =");
	puts("Values - positive integers");
	puts("Press Enter to skip filter\n");
	clean_stdin();

	FilterSet set = EMPTY_FILTER_SET;

	int pad = 15; // in every string ':' is (pad + 1)th symbol and all tags aligned to it
	
	printf("%*s %*s: ", pad, "Age", pad, "");
	set.age_c_1 = get_condition();
	if (!is_void_condition(set.age_c_1)) {
		printf("%*s %*s: ", pad, "Age", pad, "(additional)");
		set.age_c_2 = get_condition();
	}

	printf("%*s %*s: ", pad, "Weight", pad, "");
	set.weight_c_1 = get_condition();
	if (!is_void_condition(set.weight_c_1)) {
		printf("%*s %*s: ", pad, "Weight", pad, "(additional)");
		set.weight_c_2 = get_condition();
	}

	printf("%*s %*s: ", pad, "Height", pad, "");
	set.height_c_1 = get_condition();
	if (!is_void_condition(set.height_c_1)) {
		printf("%*s %*s: ", pad, "Height", pad, "(additional)");
		set.height_c_2 = get_condition();
	}

	printf("%*s %*s: ", pad, "Gender", pad, "(m/f)");
	set.gender = get_gender();

	// display all filters
	display_filter_set(set);

	return set;
}

Condition get_condition(void) {
	Condition c;
	c.sign = SIGN_DFLT;
	c.value = VALUE_DFLT;

	char ch;

	// find sign first
	while ((ch = getchar()) != '\n') {
		// save only first sign
		if (is_char_sign(ch) && c.sign == SIGN_DFLT) {
			switch (ch) {
				case '<': c.sign = -1; break;
				case '>': c.sign =  1; break;
				case '=': c.sign =  0; break;
				default: break;
		}
		} /* save only first value and only after saved sign*/
		else if (c.sign != SIGN_DFLT && isdigit(ch) && c.value == VALUE_DFLT) {
			ungetc(ch, stdin);
			scanf_s("%d", &c.value);
		}
	}
	return c;
}

char get_gender(void) {
	char res = 'b';

	char ch;

	while ((ch = getchar()) != '\n') {
		/* save only first proper letter */
		if ('b' == res && ('m' == ch || 'f' == ch)) {
			res = ch;
		}
	}
	return res;
}

bool is_char_sign(const char c) {
	if (c == '>' || c == '<' || c == '=') {
		return true;
	}
	return false;
}
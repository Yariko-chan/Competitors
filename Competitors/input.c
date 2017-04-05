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

	fseek(stdin, 0, SEEK_END);
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

	/* -1 because of '\0' at he end*/
	printf("   Login(%2d symbols): ", LOGIN_LENGTH - 1); 
	read_str(new_a.login, LOGIN_LENGTH);
	printf("Password(%2d symbols): ", PASSWORD_LENGTH - 1);
	read_str(new_a.passw, PASSWORD_LENGTH);

	return new_a;
}

Player input_player() {
	Player new_p;

	puts("\nEnter data for new player:");

	printf("%11s: ", "Surname");
	read_str(new_p.name.surname, NAME_LENGTH);
	printf("%11s: ", "Name");
	read_str(new_p.name.name, NAME_LENGTH);
	printf("%11s: ", "Patronymic");
	read_str(new_p.name.patronym, NAME_LENGTH);
	
	printf("%11s: ", "Number");
	read_hu(&new_p.number);
	printf("%11s: ", "Age");
	read_hu(&new_p.age);
	printf("%11s: ", "Height");
	read_hu(&new_p.height);
	printf("%11s: ", "Weight");
	read_hu(&new_p.weight);
	printf("%11s: ", "Gender");
	read_gender(&new_p.gender);
	
	return new_p;
}

// scan string of given length
// @length - length of string, including '\0'
void read_str(char * str, const int length) {
	char ch;

	clean_stdin();

	/* skip non-literal and non-digit chars */
	while (!isalnum(ch = getchar()));
	ungetc(ch, stdin);

	int i = 0;
	// str[length - 1] is for '\0'
	while ((ch = getchar()) != '\n' && i < (length - 1)) {  
		str[i] = ch;
		i++;
	}
	str[i] = '\0';
}

// scan unsigned short
void read_hu(unsigned short* hu) {
	char ch;
	int c;

	clean_stdin();
	do {
		while (!isdigit(ch = getchar()));
		ungetc(ch, stdin);
		c = scanf_s("%hu", hu);
	} while (c != 1); /* until one successfully readed*/
	
}

// scan only first 'f' or 'm'
void read_gender(char* ch) {

	clean_stdin();
	do {
		*ch = getchar();
	} while (*ch != 'f' && *ch != 'm');
}

/*
scan string of given length
skips if enter pressed
@length - length of string, including '\0'
*/
void read_str_or_skip(char * str, const int length) {
	char ch;
	int i;

	i = 0;
	while ((ch = getchar()) != '\n' && i < (length - 1))
	{
		str[i] = ch;
		i++;
	}
	str[i] = '\0';
}

/*
scan unsigned short
skips if enter pressed
*/
void read_hu_or_skip(unsigned short* hu) {
	char ch;
	clean_stdin();
	while ((ch = getchar()) != '\n')
	{
		if (isdigit(ch)) {
			ungetc(ch, stdin);
			int c = scanf_s("%hu", hu);
			if (1 == c) break;
		}
	}
}

void edit_str(char* editable, const char* tag, const size_t length) {
	int pad = 15; // max size of tag and editable
	printf("%*s: %*s New: ", pad, tag, pad, editable);

	char* tmp = (char*)calloc(length, sizeof(char));
	read_str_or_skip(tmp, length);
	if (strcmp("", tmp)) { /* tmp != " " */
		int res = strcpy_s(editable, length, tmp);
		if (0 != res) puts("\nError editing string, changes didn't saved.");
	}
	free(tmp);
}

void edit_short(unsigned short* editable, const char* tag) {
	int pad = 15; // max size of tag and editable
	printf("%*s: %*d New: ", pad, tag, pad, *editable);

	read_hu_or_skip(editable);
}

FilterSet input_filter_set(void) {
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

	int pad = 15; 
	// in every string ':' is (pad + 1)th symbol and all tags aligned to it
	
	printf("%*s %*s: ", pad, "Age", pad, "");
	set.age_c_1 = input_condition();
	if (!is_void_condition(set.age_c_1)) {
		printf("%*s %*s: ", pad, "Age", pad, "(additional)");
		set.age_c_2 = input_condition();
	}

	printf("%*s %*s: ", pad, "Weight", pad, "");
	set.weight_c_1 = input_condition();
	if (!is_void_condition(set.weight_c_1)) {
		printf("%*s %*s: ", pad, "Weight", pad, "(additional)");
		set.weight_c_2 = input_condition();
	}

	printf("%*s %*s: ", pad, "Height", pad, "");
	set.height_c_1 = input_condition();
	if (!is_void_condition(set.height_c_1)) {
		printf("%*s %*s: ", pad, "Height", pad, "(additional)");
		set.height_c_2 = input_condition();
	}

	printf("%*s %*s: ", pad, "Gender", pad, "(m/f)");
	set.gender = input_gender();

	// display all filters
	display_filter_set(set);

	return set;
}

Condition input_condition(void) {
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

char input_gender(void) {
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

//returns first letter from input
char input_sort_mode(void)
{
	char mode;
	do {
		print_sort_mode_menu();
		clean_stdin();
		mode = getchar();
	} while (!isalpha(mode));
	return mode;
}
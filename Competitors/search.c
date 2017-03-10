#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "search.h"
#include "input.h"
#include "output.h"

// linear search
int get_account_index(const Account* a_list, const int count, const char* key_login) {
	int i = 0;
	int res = 0;

	for (i = 0; i < count; i++) {
		res = strcmp(a_list[i].login, key_login);
		if (0 == res) return i;
	}
	return -1;
}

//get login for search
//search account in list
//return index of account 
int search_account(const Account *a_list, const long count)
{
	char login[LOGIN_LENGTH];
	int i;

	do {
		printf("Enter login:");
		do {
			scanf_s("%s", login, LOGIN_LENGTH);
		} while ('\n' == (char)login);
		
		//search
		i = get_account_index(a_list, count, login);

		//not found
		if (-1 == i)
		{
			puts("Not found.");
			if (!ask_confirm("Do you want to search another account ?"))
			{
				//if don't want, exit
				//else start while loop again
				return -1;
			}

		}
	} while (i == -1);

	printf("\n     FOUND: %s\n", a_list[i].login);
	return i;
}

// linear search in players list by number
// return index of found element
// or -1 if not found
int get_player_index_by_num(const Player * p_list, const int count, const unsigned short num) {

	for (int i = 0; i < count; i++) {
		int res = p_list[i].number - num;
		if (0 == res) return i;
	}
	return -1;
}

// linear search in players list by surname
// return index of found element
// or -1 if not found
int get_player_index_by_surname(const Player * p_list, const int count, const char * surname) {

	for (int i = 0; i < count; i++) {
		int res = strcmp(p_list[i].name.surname, surname);
		if (0 == res) return i;
	}
	return -1;
}

// get condition for search
// return index of found element
// or -1 if not found and shoild exit operation
int search_player(const Player * p_list, const long count) {
	char mode = 'q';
	int i = -1;

	do {
		mode = get_search_mode();

		//exit to main
		if ('q' == mode) return -1;

		if ('n' == mode) {
			printf("Number: ");
			int num = -1;
			scanf_s("%d", &num);
			i = get_player_index_by_num(p_list, count, num);
		}
		else if ('s' == mode) {
			printf("Surname: ");
			char surname[NAME_LENGTH];
			scanf_s("%s", surname, NAME_LENGTH);
			i = get_player_index_by_surname(p_list, count, surname);
		}

		//not found
		if (-1 == i)
		{
			puts("Not found.");
			if (!ask_confirm("Do you want to search another player ?"))
			{
				//if don't want, exit
				//else start while loop again
				return -1;
			}

		}
	} while (i == -1);

	printf("\n     FOUND: %d %s %c. %c.\n", 
		p_list[i].number, p_list[i].name.surname, p_list[i].name.name[0], p_list[i].name.patronym[0]);
	return i;
}

//returns 'n', 's' or 'q'
char get_search_mode(void)
{
	char mode;
	do {
		print_search_player_menu();
		clean_stdin();
		mode = getchar();
	} while ((mode != 's') && (mode != 'n') && (mode != 'q'));
	return mode;
}
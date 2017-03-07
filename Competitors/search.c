#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "search.h"
#include "input.h"

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
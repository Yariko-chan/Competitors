#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "search.h"
#include "input.h"
#include "output.h"

/*
get login for search from input
search account in @a_list
return index of account in @a_list
or -1 if not found
*/
int search_account(const Account *a_list, const long count)
{
	char login[LOGIN_LENGTH];
	int i;

	do {
		printf("Login: ");
		do {
			read_str(login, LOGIN_LENGTH);
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

	printf("\n     FOUND: %s\n\n", a_list[i].login);
	return i;
}

/*
linear search account by login
return index in @a_list
or -1 if not found
*/
int get_account_index(const Account* a_list, const int count, const char* key_login) {
	int i = 0;
	int res = 0;

	for (i = 0; i < count; i++) {
		res = strcmp(a_list[i].login, key_login);
		if (0 == res) return i;
	}
	return -1;
}

/*
get search mode and key from input
find all occurences
select one from all occurences by input
return index of element
return -1 if not found
*/
int search_one_player(const Player * p_list, const long count) {
	int occ_count = 0;
	int* occ_indices = search_all_matching_players(p_list, count, &occ_count);

	int res = -1;

	// if only one occurence
	if (occ_count == 1) {
		res = occ_indices[0];
	}
	// select one player from all found
	else if (occ_count > 1) {
		int i = -1;
		do {
			printf("Enter index in list to select player: ");
			clean_stdin();
			int s = scanf_s("%d", &i);
			if ((s != 1 || i < 1 || i > occ_count) && !ask_confirm("Can't read index. Try again? ")) {
				free(occ_indices);
				return -1;
			}
		} while (i < 1 || i > occ_count);
		res = occ_indices[i - 1];
	} else { /* if 0 occurences or some errors*/
		free(occ_indices);
		return -1;
	}

	// print found player
	printf("\n\n     %d %s %c. %c.\n",
		p_list[res].number, p_list[res].name.surname, p_list[res].name.name[0], p_list[res].name.patronym[0]);

	free(occ_indices);
	return res;
}

// TODO: return occ_count and occ_indices in arguments

/*
get search mode from input
get key for search from input
get list of indexes of matching elements in @p_list
print all matching elements
return list of indexes 
return null if not found
result need to be freed
*/
int* search_all_matching_players(const Player * p_list, const long count, int* occ_count) {
	char mode = 'q';
	int* occ_indices;
	*occ_count = 0; // by default

	do {
		mode = get_search_mode();

		//exit to main
		if ('q' == mode) return NULL;

		if ('n' == mode) {
			printf("Number: ");
			int num = -1;
			scanf_s("%d", &num);
			occ_indices = get_players_indexes_by_num(p_list, count, num, occ_count);
		}
		else if ('s' == mode) {
			printf("Surname: ");
			char surname[NAME_LENGTH];
			read_str(surname, NAME_LENGTH);
			occ_indices = get_players_indexes_by_surname(p_list, count, surname, occ_count);
		}

		//not found
		if (NULL == occ_indices || 0 == *occ_count)
		{
			puts("Not found.");
			if (!ask_confirm("Do you want to search another player ?"))
			{
				//if don't want, exit
				//else start while loop again
				free(occ_indices);
				return NULL;
			}

		}
	} while (occ_indices == NULL && *occ_count == 0);

	// print all occurences
	puts("\n     FOUND:\n");
	for (int i = 0; i < *occ_count; i++) {
		// 1. Surname N. P.
		int index = occ_indices[i];
		printf("     %d. %d %s %c. %c.\n",
			i + 1, p_list[index].number, p_list[index].name.surname, p_list[index].name.name[0], p_list[index].name.patronym[0]);
	}

	return occ_indices;
}

/*
get search mode from input
returns 'n', 's' or 'q'
*/
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

/* 
linear search in players list by number
return array of indexes of occurences in @p_list
need to free result pointer
@occ_count - count of occurences
if no occurences, occ_count = 0, return null
result need to be freed
*/
int* get_players_indexes_by_num(const Player * p_list, const int players_count, const unsigned short num, int* occ_count) {

	// temporary array for saving occurences
	// all elements false until key num found at that position
	bool* occ_tmp = (bool*)calloc(players_count, sizeof(int));
	for (int i = 0; i < players_count; i++) {
		occ_tmp[i] = false;
	}

	// count of occurences
	*occ_count = 0;

	// find all occurences
	for (int i = 0; i < players_count; i++) {
		int res = p_list[i].number - num;
		if (0 == res) { /* if p_list[i] matches key */
			occ_tmp[i] = true;
			(*occ_count)++;
		}
	}

	// if no occurences, return null
	if (0 == *occ_count) return NULL;

	int* occ_indices = (int*)calloc(*occ_count, sizeof(int));
	int j = 0;
	for (int i = 0; i < players_count && j < *occ_count; i++) {
		if (occ_tmp[i]) {
			// save index of true element to result array
			occ_indices[j] = i;
			j++;
		}
	}

	free(occ_tmp);
	return occ_indices;
}

/*
linear search in players list by surname
return array of indexes of occurences in @p_list
need to free result pointer
@occ_count - count of occurences
if no occurences, occ_count = 0, return null
result need to be freed
*/
int* get_players_indexes_by_surname(const Player * p_list, const int players_count, const char* surname, int* occ_count) {

	// temporary array for saving occurences
	// all elements false until key surname found at that position
	bool* occ_tmp = (bool*)calloc(players_count, sizeof(int));
	for (int i = 0; i < players_count; i++) {
		occ_tmp[i] = false;
	}

	// count of occurences
	*occ_count = 0;

	// find all occurences
	for (int i = 0; i < players_count; i++) {
		int res = strcmp(p_list[i].name.surname, surname);
		if (0 == res) { /* if p_list[i] matches key */
			occ_tmp[i] = true;
			(*occ_count)++;
		}
	}

	// if no occurences, return null
	if (0 == *occ_count) return NULL;

	int* occ_indices = (int*)calloc(*occ_count, sizeof(int));
	int j = 0;
	for (int i = 0; i < players_count && j < *occ_count; i++) {
		if (occ_tmp[i]) {
			// save index of true element to result array
			occ_indices[j] = i;
			j++;
		}
	}

	free(occ_tmp);
	return occ_indices;
}
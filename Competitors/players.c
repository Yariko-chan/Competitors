#include "file.h"
#include "constants.h"
#include "input.h"
#include "search.h"
#include "output.h"
#include "players.h"
#include "filter.h"
#include "sort.h"

void add_player(void) {
	Player p_new = input_player();

	// this code can be replaced by adding new player to the end of file
	// but because of crypting algorithm data should be encrypted integrated
	// TODO: may be some improvement in encrypting function
	// so it can encrypt from last used char in key, not only from beginning
	Player* p_list;
	int p_count = get_players_list(&p_list);
	p_list = realloc(p_list, ++p_count*sizeof(Player));
	p_list[p_count - 1] = p_new;
	save_players_changes(p_list, p_count);
}

void view_players_list(void) {
	Player* p_list = NULL; /* to have no errors with junk in the memory*/
	int count = get_players_list(&p_list);
	display_players_list(p_list, count);

	if (0 == count || NULL == p_list) return;
	char choice;
	do {
		print_view_menu();
		clean_stdin();
		choice = getchar();
		switch (choice) {
		case 'f': filter_players(p_list, count);  break;
		case 'e': search(p_list, count); break;
		case 's': sort_players_list(p_list, count); break;
		case 'q': break;
		default: printf("No such operation. Try again.\n"); break;
		}
	} while (choice != 'q');

	//free allocated array
	free(p_list);
}

void delete_player(void)
{
	puts("\n          *DELETE PLAYER*\n");
	Player * p_list = NULL; /* to have no errors with junk in the memory*/
	int count = get_players_list(&p_list);
	if (count == 0 || NULL == p_list) {
		free(p_list);
		puts("No player in list");
		return;
	}
	int i = search_one_player(p_list, count);

	//if found
	if (-1 < i) {
		if (ask_confirm("Do you want to delete this player from list?")) {
			for (i; i < (count - 1); i++) {
				// move all items in list after i to previous position
				p_list[i] = p_list[i + 1];
			}
			count--;
			save_players_changes(p_list, count);
		}
	}

	free(p_list);
}

void edit_player(void)
{

	puts("\n           *EDIT PLAYER*\n");
	Player * p_list = NULL; /* to have no errors with junk in the memory*/
	int count = get_players_list(&p_list);
	if (0 == count || NULL == p_list) {
		free(p_list);
		puts("No player in list");
		return;
	}
	int i = search_one_player(p_list, count);

	//if found
	if (-1 < i) {
		puts("Enter new values or press Enter to skip.\n");
		clean_stdin();
		edit_str(p_list[i].name.surname, "Surname", NAME_LENGTH);
		edit_str(p_list[i].name.name, "Name", NAME_LENGTH);
		edit_str(p_list[i].name.patronym, "Patronymic", NAME_LENGTH);
		
		edit_short(&p_list[i].number, "Number");
		edit_short(&p_list[i].age, "Age");
		edit_short(&p_list[i].height, "Height");
		edit_short(&p_list[i].weight, "Weight");

		save_players_changes(p_list, count);
	}

	free(p_list);
}

void filter_players(const Player* p_list, const int count) {

	FilterSet filters = input_filter_set();

	// count of players after filtration
	int p_f_count = 0;
	Player* p_filtered_list = filter_players_list(p_list, count, filters, &p_f_count);

	display_players_list(p_filtered_list, p_f_count);

	free(p_filtered_list);
}

void search(const Player* p_list, const int count) {
	int* f_list; // just to match arguments
	search_all_matching_players(p_list, count, &f_list);
}

void sort_players_list(Player* p_list, const int p_count) {

	// select attribute for search
	char mode = input_sort_mode();

	// exit to view menu
	if ('q' == mode) return;

	sort_by_mode(p_list, p_count, mode);

	display_players_list(p_list, p_count);
}
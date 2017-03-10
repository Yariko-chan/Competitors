#include "file.h"
#include "constants.h"
#include "input.h"

void add_player(void) {
	FILE * fp;

	Player new_p = input_player();
	open_file(&fp, PLAYERS_FILE_NAME, "ab");

	// save player
	int writed_count = fwrite(&new_p, sizeof(Player), 1, fp);
	if (1 == writed_count) {
		puts("Player successfully added.");
	}
	else {
		printf("Error occured, player [%s %s] wasn't saved", new_p.name.name, new_p.name.surname);
	}

	close_file(fp);
}

void view_players_list(void) {
	Player* a;
	int count;

	a = get_players_list(&count);
	display_players_list(a, count);

	//free allocated array
	free(a);
}
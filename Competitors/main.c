#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "output.h"
#include "input.h"
#include "main.h"
#include "constants.h"
#include "file.h"
#include "accounts.h"
#include "players.h"

// 1 - admin, 0 - user(default)
int g_account = 0;

int main(void) {

	char choice = ' ';

	init_accounts_file();
	init_players_file();

	do {
		print_auth_menu();
		choice = getchar();
		switch (choice) {
		case 's': sign_in(); break;
		case 'q': printf("Exit\n"); break;
		default: printf("No such operation. Try again.\n"); break;
		}
		clean_stdin();
	} while (choice != 'q');
}

void sign_in(void) {
	const int STR_EQUALS = 0;

	char login[LOGIN_LENGTH];
	char correct_pass[PASSWORD_LENGTH];
	char entered_pass[PASSWORD_LENGTH];

	// get existing login
	bool is_existing_login = false;
	do {
		printf("%8s: ", "Login");
		read_str(login, LOGIN_LENGTH);
		get_pass_from_account(login, correct_pass);
		is_existing_login = (strlen(correct_pass) != 0);
		if (!is_existing_login) {
			if (!ask_confirm("No such account. Try again?"))
				exit(EXIT_SUCCESS);
		}
	} while (!is_existing_login);
	
	// get correct password
	bool is_pass_true = false;
	do {
		printf("%8s: ", "Password");
		read_str(entered_pass, PASSWORD_LENGTH);
		is_pass_true = (STR_EQUALS == strcmp(correct_pass, entered_pass));
		if (!is_pass_true) {
			clean_stdin();
			if (!ask_confirm("Incorrect password. Try again?")) 
				exit(EXIT_SUCCESS);
		}
	} while (!is_pass_true);

	// if account - admin, change role
	if (STR_EQUALS == strcmp(login, ADM_LOGIN)) {
		g_account = 1;
	}
	printf(WELCOME);
	main_menu();
}

void main_menu(void) {
	char choice = ' ';
	do {
		print_main_menu();
		clean_stdin();
		choice = getchar();
		if (g_account) {
			switch (choice) {
			case 'v': view_players_list(); break;
			case 'a': add_player(); break;
			case 'd': delete_player(); break;
			case 'u': manage_accounts(); break;
			case 'e': edit_player(); break;
			case 's': g_account = 0; return; /*sign out */
			case 'q': {
				printf("Exit\n");
				exit(EXIT_SUCCESS);
				break;
			}
			default: printf("No such operation. Try again.\n"); break;
			}
		}
		else {
			switch (choice) {
			case 'v': view_players_list(); break;
			case 's': return; /*sign out */
			case 'q': {
				printf("Exit\n");
				exit(EXIT_SUCCESS);
				break;
			}
			default: printf("No such operation. Try again.\n"); break;
			}
		}
		
	} while (choice != 'q');
}
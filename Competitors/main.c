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

int g_role = 0;

int main(void) {
	char choice = ' ';

	init_accounts_file();
	init_players_file();

	login();
}

void login(void) {
	const int STR_EQUALS = 0;

	// TODO: add some info about success login
	char login[LOGIN_LENGTH];
	char correct_pass[PASSWORD_LENGTH];
	char entered_pass[PASSWORD_LENGTH];
	
	//printf("Enter login and password: \n");

	// TODO: rewrite with no break-continue-while(true)
	// get existing login
	do {
		printf("%8s: ", "Login");
		scanf_s("%s", login, LOGIN_LENGTH);
		get_password(login, correct_pass);
		if (strlen(correct_pass) != 0) {
			break;
		}
		else {
			if (!ask_confirm("No such account. Try again?"))
				exit(EXIT_SUCCESS);
		}
	} while (true);
	
	// get correct password
	do {
		printf("%8s: ", "Password");
		scanf_s("%s", entered_pass, PASSWORD_LENGTH);
		if (STR_EQUALS == strcmp(correct_pass, entered_pass)) {
			break;
		}
		else {
			clean_stdin();
			if (!ask_confirm("Incorrect password. Try again?")) 
				exit(EXIT_SUCCESS);
		}
	} while (true);

	// if account - admin, change role
	if (STR_EQUALS == strcmp(login, ADM_LOGIN)) {
		g_role = 1;
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
		if (g_role) {
			switch (choice) {
			case 'v': view_players_list(); break;
			case 'a': add_player(); break;
			case 'd': delete_player(); break;
			case 'u': manage_accounts(); break;
			case 'e': edit_player(); break;
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

void manage_accounts(void) {
	char choice = ' ';

	puts("------------------------------------------------------");
	puts("\n          ***USER MANAGEMENT***");

	do {
		print_manage_accounts_menu();
		clean_stdin();
		choice = getchar();
		switch (choice) {
		case 'v': view_accounts_list();  break;
		case 'a': add_new_account();  break;
		case 'd': delete_account();  break;
		case 'c': change_account_pass(); break;
		case 'q': break;
		default: printf("No such operation. Try again.\n"); break;
		}
	} while (choice != 'q');
	puts("------------------------------------------------------");
}
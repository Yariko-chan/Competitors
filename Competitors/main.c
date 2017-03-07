#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "output.h"
#include "input.h"
#include "main.h"
#include "constants.h"
#include "file.h"
#include "users.h"

int g_role = 0;

int main(void) {
	char choice = ' ';

	init_accounts_file();

	printf(WELCOME);
	do {
		print_auth_menu();
		choice = getchar();
		switch (choice) {
		    case 'l': login(); break;
		    case 'q': printf("Exit\n"); break;
		    default: printf("No such operation. Try again.\n"); break;
		}
		clean_scan();
	} while (choice != 'q');
}

void login(void) {
	const int STR_EQUALS = 0;

	// TODO: add some info about success login
	char login[LOGIN_LENGTH];
	char passw[PASSWORD_LENGTH];
	Account user;
	
	printf("Enter login and password: \n");

	// TODO: rewrite with no break-continue-while(true)
	// get existing login
	do {
		printf("%8s:", "Login");
		scanf_s("%s", login, LOGIN_LENGTH);
		user = get_user(login);
		if (strlen(user.passw) != 0) {
			break;
		}
		else {
			if (!ask_confirm("No such user. Try again?"))
				exit(EXIT_SUCCESS);
		}
	} while (true);
	
	// get correct password
	do {
		printf("%8s:", "Password");
		scanf_s("%s", passw, PASSWORD_LENGTH);
		if (STR_EQUALS == strcmp(user.passw, passw)) {
			break;
		}
		else {
			clean_scan();
			if (!ask_confirm("Incorrect password. Try again?")) 
				exit(EXIT_SUCCESS);
		}
	} while (true);

	// if user - admin, change role
	if (STR_EQUALS == strcmp(user.login, ADM_LOGIN)) {
		g_role = 1;
	}

	main_menu();
}

void main_menu(void) {
	char choice = ' ';
	do {
		print_main_menu();
		clean_scan();
		choice = getchar();
		switch (choice) {
		    case 'u': manage_users(); break;
		    case 'q': {
		    	printf("Exit\n");
			    exit(EXIT_SUCCESS);
			    break;
		    }
		default: printf("No such operation. Try again.\n"); break;
		}
	} while (choice != 'q');
}

void manage_users(void) {
	char choice = ' ';
	do {
		print_manage_users_menu();
		clean_scan();
		choice = getchar();
		switch (choice) {
		case 'v': view_users_list();  break;
		case 'a': add_new_user();  break;
		case 'd': delete_user();  break;
		case 'e': edit_user_pass(); break;
		case 'q': break;
		default: printf("No such operation. Try again.\n"); break;
		}
	} while (choice != 'q');
}
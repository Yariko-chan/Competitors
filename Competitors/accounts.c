#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "input.h"
#include "file.h"
#include "output.h"
#include "accounts.h"
#include "search.h"

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
		case 'a': add_account();  break;
		case 'd': delete_account();  break;
		case 'c': change_account_pass(); break;
		case 'q': break;
		default: printf("No such operation. Try again.\n"); break;
		}
	} while (choice != 'q');
	puts("------------------------------------------------------");
}

void view_accounts_list(void) {
	Account* a;
	int count;

	a = get_accounts_list(&count);
	display_accounts_list(a, count);

	//free allocated array
	free(a);
}

/*
input login
if exists, rewrite password
else add new account to list
*/
void add_account(void) {

	Account new_a = input_account();

	// get accounts list
	int a_count = 0;
	Account* a_list = get_accounts_list(&a_count);

	if (0 == a_count) { /* if list void add new */
		add_new_account(new_a);
		free(a_list);
		return;
	}

	// find account in list by login
	// DO NOT free(a_list) until found Account is need
	int i = get_account_index(a_list, a_count, new_a.login);

	if (i > -1) { /* if account found, rewrite pass */
		if (ask_confirm("Account already exists. Rewrite password? ")) {
			strcpy_s(a_list[i].passw, PASSWORD_LENGTH, new_a.passw);
			save_accounts_changes(a_list, a_count);
		}
	}
	else { /* account not found, add_new */
		add_new_account(new_a);
	}
	free(a_list);
}

// writes new account to end of auth file
void add_new_account(Account new_a) {
	FILE* fp;
	open_file(&fp, ACCOUNTS_FILE_NAME, "ab");
	int writed_count = fwrite(&new_a, sizeof(Account), 1, fp);
	if (1 == writed_count) {
		puts("Account successfully added.");
	}
	else {
		printf("Error occured, account [%s] wasn't saved",
			new_a.login);
	}
	close_file(fp);
}

void delete_account(void)
{
	Account * a_list;
	int count;

	// search account in list
	puts("\nEnter login of account to delete.");
	a_list = get_accounts_list(&count);
	if (NULL == a_list) {
		// free(a_list);
		// already free
		return;
	}
	int i = search_account(a_list, count);
	
	//if found
	if (-1 < i) {
		if (ask_confirm("Are you sure you want to delete this account?")) {
			for (i; i < (count - 1); i++) {
				// move all items in list after i to previous position
				a_list[i] = a_list[i + 1];
			}
			count--;
			save_accounts_changes(a_list, count);
		}
	}

	free(a_list);
}

void change_account_pass(void) {

	// search account
	puts("\nEnter login of account to change.");
	int count;
	Account * a_list = get_accounts_list(&count);
	if (NULL == a_list) {
		// free(a_list) - already free
		return;
	} /* input login, search account */
	int i = search_account(a_list, count);

	//if found
	if (-1 < i) {
		// get new password
		printf("New password: ");
		char pass[PASSWORD_LENGTH];
		read_str(&pass, PASSWORD_LENGTH);

		if (ask_confirm("Are you sure you want to save new password?")) { /* replace password */
			strcpy_s(a_list[i].passw, PASSWORD_LENGTH, pass);
			save_accounts_changes(a_list, count);
		}
	}

	free(a_list);
}

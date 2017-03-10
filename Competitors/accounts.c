#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "input.h"
#include "file.h"
#include "output.h"
#include "accounts.h"
#include "search.h"

void view_accounts_list(void) {
	Account* a;
	int count;

	a = get_accounts_list(&count);
	display_accounts_list(a, count);

	//free allocated array
	free(a);
}


void add_new_account(void) {
	FILE* fp;

	Account new_a = input_account();
	open_file(&fp, ACCOUNTS_FILE_NAME, "ab");
	int writed_count = fwrite(&new_a, sizeof(Account), 1, fp);
	if (1 == writed_count) {
		puts("Account successfully added.");
	}
	else {
		printf("Error occured, account [%s] wasn't saved", new_a.login);
	}
	close_file(fp);
}

void delete_account(void)
{
	Account * a_list;
	int count;

	puts("*DELETE ACCOUNT*");
	a_list = get_accounts_list(&count);
	if (NULL == a_list) {
		// free(a_list);
		// already free
		return;
	}
	int i = search_account(a_list, count);
	
	//if found
	if (-1 < i) {
		if (ask_confirm("Do you want to delete this account?")) {
			for (i; i < (count - 1); i++) {
				// move all items in list after i to previous position
				a_list[i] = a_list[i + 1];
			}
			count--;
			save_accounts_changes(a_list, count);
			puts("Account successfully deleted.");
		}
	}

	free(a_list);
}

void edit_account_pass(void) {
	Account * a_list;
	char pass[PASSWORD_LENGTH];
	int count;

	puts("*CHANGE PASSWORD*");
	a_list = get_accounts_list(&count);
	if (NULL == a_list) {
		// free(a_list);
		// already free
		return;
	}
	int i = search_account(a_list, count);

	//if found
	if (-1 < i) {
		// get new password
		printf("New password:");
		do {
			scanf_s("%s", pass, PASSWORD_LENGTH);
		} while ('\n' == (char)pass);

		if (ask_confirm("Do you want to save new password?")) {
			strcpy_s(a_list[i].passw, PASSWORD_LENGTH, pass);
			save_accounts_changes(a_list, count);
			puts("Password successfully saved. ");
		}
	}

	free(a_list);
}

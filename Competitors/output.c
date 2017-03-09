#pragma once
#include <stdio.h>

#include "constants.h"
#include "output.h"

/*
Select operation to continue:
l Login
q Exit program
*/
void print_auth_menu(void) {
	printf("\n\nSelect operation to continue:\n");
	printf("l Login \n");
	printf("q Exit program \n");
}

/*
  ***MENU***
u User management
q Exit program
*/
void print_main_menu(void) {
	printf("\n\n  ***MENU***\n");
	printf("u User management \n");
	printf("q Exit program \n");
}

/*
       ***USER MANAGEMENT***

v View all accounts     a Add new account
e Edit password         d Delete account
q Exit to main menu
*/
void print_manage_accounts_menu(void) {
	printf("\n\n       ***USER MANAGEMENT***\n\n");
	printf("v View all accounts     a Add new account\n");
	printf("e Edit password         d Delete account\n");
	printf("q Exit to main menu\n");
}

// print list of all logins
void display_accounts_list(const Account* a, const int count) {
	int i = 0;
	puts(" *ACCOUNTS*");
	puts("--------");
	for (i = 0; i < count; i++) {
		puts(a[i].login);
	}
	puts("--------");
}
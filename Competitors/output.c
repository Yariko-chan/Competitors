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
Select operation to continue:
u Users management
q Exit program
*/
void print_main_menu(void) {
	printf("\n\nSelect operation to continue:\n");
	printf("u Users management \n");
	printf("q Exit program \n");
}

// TODO: headers

/*
Select operation to continue:
v View all users       a Add new user   
e Edit user password   d Delete user
q Exit to main menu
*/
void print_manage_users_menu(void) {
	printf("\n\nSelect operation to continue:\n");
	printf("v View all users       a Add new user\n");
	printf("e Edit user password   d Delete user\n");
	printf("q Exit to main menu\n");
}

// print list of all logins
void display_users_list(const Account* a, const int count) {
	int i = 0;
	puts(" *USERS*");
	puts("--------");
	for (i = 0; i < count; i++) {
		puts(a[i].login);
	}
	puts("--------");
}
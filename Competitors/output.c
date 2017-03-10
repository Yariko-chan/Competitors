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
v View players list       a Add player to list
u User management         q Exit program
*/
void print_main_menu(void) {
	puts("\n\n               ***MENU***");
	puts("v View players list       a Add player to list");
	puts("u User management         q Exit program\n");
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

// print all players data in table
/*
       ************PLAYERS************

| N |              Surname N. P.| Age| Weight| Height|
------------------------------------------------------
|   |                           |    |       |       |
------------------------------------------------------
*/
void display_players_list(const Player * p_list, const int count) {
	puts("       ************PLAYERS************\n");
	printf("|%3s|%27s|%4s|%7s|%7s|\n",
		"N", "Surname N.P.", "Age", "Weight", "Height");
	puts("------------------------------------------------------");
	for (int i = 0; i < count; i++) {
		Player p = p_list[i];
		printf("|%3hu|%21s %c. %c.|%4hu|%7hu|%7hu|\n",
			p.number, p.name.surname, p.name.name[0], p.name.patronym[0], p.age, p.weight, p.height);
	}
	puts("------------------------------------------------------");
}
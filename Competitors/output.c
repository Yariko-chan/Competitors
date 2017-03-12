#pragma once
#include <stdio.h>

#include "constants.h"
#include "output.h"

extern g_role;

/*
Select operation to continue:
l Login
q Exit program
*/
void print_auth_menu(void) {
	puts("\n\nSelect operation to continue:");
	puts("l Login");
	puts("q Exit program");
}

/*
----------------------------------------------
Select operation to continue:
a Add player to list       e Edit player info
d Delete player            u User management
v View players list        q Exit program
*/
void print_main_menu(void) {
	puts("\n----------------------------------------------");
	puts("Select operation to continue:");
	if (g_role) {
		puts("a Add player to list       e Edit player info");
	    puts("d Delete player            u User management");
	}
	
	puts("v View players list        q Exit program");
}

/*
-----------------------------------------
Select operation to continue:
v View all accounts     a Add new account
e Edit password         d Delete account
q Exit to main menu
*/
void print_manage_accounts_menu(void) {
	puts("\n-----------------------------------------");
	puts("Select operation to continue:");
	puts("v View all accounts     a Add new account");
	puts("c Change password       d Delete account");
	puts("q Exit to main menu");
}

/*
How would you like to search player?
n By number     s By surname
q Exit to main menu
*/
void print_search_player_menu(void) {
	puts("How would you like to search player?");
	puts("n By number     s By surname");
	puts("q Exit to main menu");
}

// print list of all logins
/*                
                 *ACCOUNTS*

          |   Login   | Password  |
          -------------------------
          |           |           |
          -------------------------*/
void display_accounts_list(const Account* a, const int count) {
	int i = 0;
	puts("                 *ACCOUNTS*\n");
	printf("          |%-*s|%-*s|\n", LOGIN_LENGTH, "Login", PASSWORD_LENGTH, "Password");
	printf("          ");
	print_count_hyphen(LOGIN_LENGTH + PASSWORD_LENGTH + 3); /* 3 for 3x'|' */
	for (i = 0; i < count; i++) {
		printf("          |%-*s|%-*s|\n", LOGIN_LENGTH, a[i].login, PASSWORD_LENGTH, a[i].passw);
	}
	printf("          ");
	print_count_hyphen(LOGIN_LENGTH + PASSWORD_LENGTH + 3); /* 3 for 3x'|' */
}

// print all players data in table
/*
                  *PLAYERS*

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

//print line of @count hyphens
void print_count_hyphen(const int count) {
	for (int i = 0; i < count; i++) {
		printf("-");
	}
	puts("");
}
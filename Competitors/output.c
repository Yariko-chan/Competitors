#pragma once
#include <stdio.h>

#include "constants.h"
#include "input.h"
#include "output.h"
#include "filter.h"

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

/*
Select option:
f Filter players   s Sort players list
e Search player    q Exit to main menu
*/
void print_view_menu(void) {
	puts("\nSelect option:");
	puts("f Filter players   s Sort players list");
	puts("e Search player    q Exit to main menu");
}

/*
How would you like to sort players list?

n By number       s By surname
w By Weight       h By height
a By age          g By gender
    q Exit to main menu
*/
void print_sort_mode_menu(void)
{
	puts("\nHow would you like to sort_by_mode players list?\n");
	puts("n By number       s By surname");
	puts("w By Weight       h By height");
	puts("a By age          g By gender");
	puts("    q Exit to main menu");
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
          ************PLAYERS************

| N |              Surname N. P.| Gender| Age| Weight| Height|
------------------------------------------------------
|   |                           |       |    |       |       |
------------------------------------------------------
*/
void display_players_list(const Player * p_list, const int count) {
	puts("\n          ************PLAYERS************\n");
	printf("|%3s|%27s|%7s|%4s|%7s|%7s|\n",
		"N", "Surname N.P.", "Gender", "Age", "Weight", "Height");
	puts("--------------------------------------------------------------");
	for (int i = 0; i < count; i++) {
		Player p = p_list[i];
		printf("|%3hu|%21s %c. %c.|%7c|%5hu|%7hu|%7hu|\n",
			p.number, p.name.surname, p.name.name[0], p.name.patronym[0], p.gender, p.age, p.weight, p.height);
	}
	puts("--------------------------------------------------------------");
}

//print line of @count hyphens
void print_count_hyphen(const int count) {
	for (int i = 0; i < count; i++) {
		printf("-");
	}
	puts("");
}

void display_filter_set(FilterSet set) {
	puts("\n      FILTERS");
	int pad = 10;
	if (!is_void_condition(set.age_c_1)) {
		printf("%*s %c %d\n", pad, "age", get_char_sign(set.age_c_1.sign), set.age_c_1.value);
		if (!is_void_condition(set.age_c_2)) {
			printf("%*s %c %d\n", pad, "age", get_char_sign(set.age_c_2.sign), set.age_c_2.value);
		}
	}
	if (!is_void_condition(set.weight_c_1)) {
		printf("%*s %c %d\n", pad, "weight", get_char_sign(set.weight_c_1.sign), set.weight_c_1.value);
		if (!is_void_condition(set.weight_c_2)) {
			printf("%*s %c %d\n", pad, "weight", get_char_sign(set.weight_c_2.sign), set.weight_c_2.value);
		}
	}
	if (!is_void_condition(set.height_c_1)) {
		printf("%*s %c %d\n", pad, "height", get_char_sign(set.height_c_1.sign), set.height_c_1.value);
		if (!is_void_condition(set.height_c_2)) {
			printf("%*s %c %d\n", pad, "height", get_char_sign(set.height_c_2.sign), set.height_c_2.value);
		}
	}

	char* gender;
	switch (set.gender) {
	case 'm': gender = "male";   break;
	case 'f': gender = "female"; break;
	default:  gender = "both";   break;
	}
	printf("%*s: %s\n", pad, "gender", gender);
}

char get_char_sign(char sign) {
	switch (sign) {
	case -1: return '<';
	case  1: return '>';
	case  0: return '=';
	default: return '?';
	}
}
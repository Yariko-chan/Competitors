#pragma once

#include "constants.h"

void print_auth_menu(void);
void print_main_menu(void);
void print_manage_accounts_menu(void);
void print_search_player_menu(void);
void print_view_menu(void);
void print_sort_mode_menu(void);

void display_accounts_list(const Account* a, const int count);
void display_players_list(const Player* a, const int count);

void print_count_hyphen(const int count);

void display_filter_set(FilterSet set);
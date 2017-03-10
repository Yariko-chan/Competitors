#pragma once

#include "constants.h"

void print_auth_menu(void);
void print_main_menu(void);
void print_manage_accounts_menu(void);
void display_accounts_list(const Account* a, const int count);
void display_players_list(const Player* a, const int count);
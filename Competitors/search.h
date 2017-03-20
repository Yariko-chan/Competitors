#pragma once

#include "constants.h"

int search_account(const Account *a_list, const long count);
int get_account_index(const Account* a_list, const int count, const char* key_login);

int search_one_player(const Player *p_list, const long count);
int search_all_matching_players(const Player * p_list, const long count, int** occ_indices);

char get_search_mode(void);

int get_players_indexes_by_num(const Player * p_list, const int players_count, const unsigned short num, int** occ_indices);
int get_players_indexes_by_surname(const Player * p_list, const int players_count, const char* surname, int** occ_indices);
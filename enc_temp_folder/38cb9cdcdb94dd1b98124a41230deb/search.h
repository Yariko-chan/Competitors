#pragma once

#include "constants.h"

int get_account_index(const Account* a_list, const int count, const char* key_login);
int search_account(const Account *a_list, const long count);

int get_player_index_by_num(const Player* p_list, const int count, const unsigned short num);
int get_player_index_by_surname(const Player* p_list, const int count, const char* surname);
int search_player(const Player *p_list, const long count);

char get_search_mode(void);

int* get_players_indexes_by_num(const Player * p_list, const int players_count, const unsigned short num, int* occ_count);
int* get_players_indexes_by_surname(const Player * p_list, const int players_count, const char* surname, int* occ_count);
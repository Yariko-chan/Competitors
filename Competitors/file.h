#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

 void init_accounts_file(void);
 void init_players_file(void);

 void save_accounts_changes(Account* a_list, const int count);
 void save_players_changes(Player* p_list, const int count);

 int get_accounts_list(Account** a_list);
 int get_players_list(Player** p_list);

 void get_pass_from_account(const char* login, char* pass);

 void open_file(FILE** fp, const char* file_name, const char* mode);
 void close_file(FILE* fp);

 void encrypt(char* sourse, const size_t size);
 void decrypt(char* sourse, const size_t size);

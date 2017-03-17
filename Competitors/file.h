#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

 void init_accounts_file(void);
 void init_players_file(void);

 void save_accounts_changes(Account* a_list, int count);
 void save_players_changes(const Player* p_list, const int count);

 Account* get_accounts_list(int* count);
 Player* get_players_list(int* count);

 void get_pass_from_account(const char* login, char* pass);

 void open_file(FILE** fp, const char* file_name, const char* mode);
 void close_file(FILE* fp);
 void error(const char* message, const _Bool critical);
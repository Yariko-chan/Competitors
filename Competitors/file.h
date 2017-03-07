#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

// TODO: make uniform naming:
// either account or user
 void init_accounts_file(void);
 void add_account(FILE* fp, const Account* acc);
 void save_accounts_changes(Account* a_list, int count);

 Account* get_users_list(int* count);
 Account get_user(const char* login);

 void open_file(FILE** fp, const char* file_name, const char* mode);
 void close_file(FILE* fp);
 void error(const char* message, const _Bool critical);
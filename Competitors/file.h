#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

 void init_accounts_file(void);
 void add_account(FILE* fp, const Account* acc);
 void save_accounts_changes(Account* a_list, int count);

 Account* get_accounts_list(int* count);
 void get_password(const char* login, char* pass);

 void open_file(FILE** fp, const char* file_name, const char* mode);
 void close_file(FILE* fp);
 void error(const char* message, const _Bool critical);
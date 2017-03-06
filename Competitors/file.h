#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

 void init_auth_file(void);

 void add_account(FILE* fp, Account* acc);

 Account* get_acc_list(int* count);
 Account get_user(char* login);

 void open_file(FILE** fp, char* file_name, char* mode);
 void close_file(FILE* fp);
 void error(char* message, _Bool critical);
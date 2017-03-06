#pragma once

#define WELCOME "\n         Welcome to Competitors!\n"

#define LOGIN_LENGTH 10
#define PASSWORD_LENGTH 10

#define AUTH_FILE_NAME "users.co"

#define ERROR_FILE_CREATE "Error occured while creating file. "
#define ERROR_FILE_OPEN "Error occured while opening file. "
#define ERROR_FILE_CLOSE "Error occured while closing file. "
#define ERROR_CODE "Error code is "
#define ERROR_EXIT_CONFIRM "Press Enter to exit. "
#define ERROR_FILE_CORRUPTED "Warning! File corrupted, some data can't be read. "

#define ADM_LOGIN "admin"
#define ADM_PASSW "fO%YEhyE"

typedef struct A {
	char login[LOGIN_LENGTH];
	char passw[PASSWORD_LENGTH];
} Account;
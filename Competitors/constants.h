#pragma once

#define WELCOME "\n         Welcome to Competitors!\n"

#define LOGIN_LENGTH 10
#define PASSWORD_LENGTH 10
#define NAME_LENGTH 20

#define ACCOUNTS_FILE_NAME "accounts.co"
#define PLAYERS_FILE_NAME "players.co"

#define ERR_FILE_CREATE "Error occured while creating file. "
#define ERR_FILE_OPEN "Error occured while opening file. "
#define ERR_FILE_WRITING "Error occured while writing to file. "
#define ERR_FILE_CLOSE "Error occured while closing file. "
#define ERR_CODE "Error code is "
#define ERR_EXIT_CONFIRM "Press Enter to exit. "
#define ERR_FILE_CORRUPTED "Warning! File corrupted, some data can't be read. "

#define MSG_SAVE_SUCCESS "Changes successfully saved."

#define ADM_LOGIN "admin"
#define ADM_PASSW "admin"

typedef struct {
	char login[LOGIN_LENGTH];
	char passw[PASSWORD_LENGTH];
} Account;

typedef struct {
	char name[NAME_LENGTH];
	char surname[NAME_LENGTH];
	char patronym[NAME_LENGTH];
} Name;

typedef struct {
	Name name;

	// or unsigned char 0..255 ?
	unsigned short number;
	unsigned short age;
	unsigned short height;
	unsigned short weight;
} Player;
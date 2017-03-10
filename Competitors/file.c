#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include "constants.h"
#include "input.h"
#include "file.h"
#include "search.h"

const int SUCCESS = 0;

// try to open file for apppend
// creates file with init data if no file
void init_accounts_file(void) {

	FILE* fp;
	errno_t err = 0;

	// open file or create if no such file
	err = fopen_s(&fp, ACCOUNTS_FILE_NAME, "ab");
	if (SUCCESS != err) { /* error opening file*/
		/* recreate file by user confirmation */
		if (ask_confirm("Error opening auth file. "
			"Would you like to recreate file? All accounts will be removed.")) {
			fclose(fp);
		    remove(ACCOUNTS_FILE_NAME);
		    err = fopen_s(&fp, ACCOUNTS_FILE_NAME, "ab");
			/* if can't create file, throw error and exit */
		    if (SUCCESS != err) {
			    error(ERR_FILE_CREATE, true);
		    }
		}
		else {
			error(ERR_FILE_OPEN, true);
		}
	}

	// if file void, add admin account
	fseek(fp, 0L, SEEK_END);
	int length = ftell(fp);
	if (0 == length) {
		Account admin = {ADM_LOGIN, ADM_PASSW};
		int writed_count = fwrite(&admin, sizeof(Account), 1, fp);
		if (1 == writed_count) {
			puts("Account successfully added.");
		}
		else {
			printf("Error occured, account [%s] wasn't saved", admin.login);
		}
	}

	close_file(fp);
};

// rewrite accounts with new data
void save_accounts_changes(Account * a_list, int count) {
	FILE* fp;
	size_t writed_count;

	open_file(&fp, ACCOUNTS_FILE_NAME, "wb");
	writed_count = fwrite(a_list, sizeof(Account), count, fp);
	if (count == writed_count)
		puts(MSG_SAVE_SUCCESS);
	else error(ERR_FILE_WRITING, false);

	close_file(fp);
}

/*
 * search account in file
 * if exists, save correct password to @pass
 * else @pass = ""
 */
void get_password(const char* login, char* pass) {

	// get list of all accounts
	int count = 0;
	Account* a_list = get_accounts_list(&count);
	if (0 == count) { /* if list void throw error and exit */
		errno = EINTR;
		error("Accounts list empty. ", true);
	}

	// find account in list by login
	// DO NOT free(a_list) until found Account is need
	int i = get_account_index(a_list, count, login);

	if (i > -1) { /* if account found, return pass */
		strcpy_s(pass, PASSWORD_LENGTH, (a_list+i)->passw);
	}
	else { /* account not found, return void pass */
		strcpy_s(pass, PASSWORD_LENGTH, "");
	}
	free(a_list);
}

/*
 * returns pointer to list of accounts from file
 * allocates memory, need to free!
 */
Account* get_accounts_list(int* count) {
	FILE* fp;
	Account* a_list;
	size_t readed = 0;

	open_file(&fp, ACCOUNTS_FILE_NAME, "rb");

	// get count of contracts in file
	fseek(fp, 0L, SEEK_END);
	*count = ftell(fp) / sizeof(Account);
	rewind(fp);

	a_list = (Account*)calloc(*count, sizeof(Account));
	/* why. this. works? but not *count*/

	readed = fread_s(a_list,
		(long)(*count) * sizeof(Account), sizeof(Account), *count, fp);
	if (readed != *count) {
		errno = EILSEQ;
		error(ERR_FILE_CORRUPTED, false);
	}

	close_file(fp);
	return a_list;
}

/*
* returns pointer to list of players from file
* allocates memory, need to free!
*/
Player* get_players_list(int* count) {
	FILE* fp;
	Player* p_list;
	size_t readed = 0;

	open_file(&fp, PLAYERS_FILE_NAME, "rb");

	// get count of contracts in file
	fseek(fp, 0L, SEEK_END);
	*count = ftell(fp) / sizeof(Player);
	rewind(fp);

	p_list = (Player*)calloc(count, sizeof(Player));
	/* why. this. works? but not *count*/

	readed = fread_s(p_list,
		(long)count * sizeof(Player), sizeof(Player), count, fp);
	if (readed != *count) {
		errno = EILSEQ;
		error(ERR_FILE_CORRUPTED, false);
	}

	close_file(fp);
	return p_list;
}

void open_file(FILE** fp, const char* file_name, const char* mode) {
	errno_t err = fopen_s(fp, file_name, mode);
	if (SUCCESS != err) { /* if error opening file, exit program */
		error(ERR_FILE_OPEN, true);
	}
}

void close_file(FILE* fp) {
	errno_t err = fclose(fp);
	if (SUCCESS != err) { /* if can't close, exit prigram */
		error(ERR_FILE_CLOSE, true);
	}
}

// handling error
// print error message to stderr
// exit if error critical for program
void error(const char* message, const _Bool critical) {
	perror(message);
	if (critical) {
		fprintf(stderr, ERR_EXIT_CONFIRM);
		clean_scan();
		getchar();
		exit(EXIT_FAILURE);
	}
}
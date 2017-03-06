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
void init_auth_file(void) {

	FILE* fp;
	errno_t err = 0;

	// open file or create if no such file
	err = fopen_s(&fp, AUTH_FILE_NAME, "ab");
	if (SUCCESS != err) { /* error opening file*/
		/* recreate file by user confirmation */
		if (ask_confirm("Error opening auth file. "
			"Would you like to recreate file? All user data will be removed.")) {
			fclose(fp);
		    remove(AUTH_FILE_NAME);
		    err = fopen_s(&fp, AUTH_FILE_NAME, "ab");
			/* if can't create file, throw error and exit */
		    if (SUCCESS != err) {
			    error(ERROR_FILE_CREATE, true);
		    }
		}
		else {
			error(ERROR_FILE_OPEN, true);
		}
	}

	// if file void, add admin account
	fseek(fp, 0L, SEEK_END);
	int length = ftell(fp);
	if (0 == length) {
		rewind(fp);
		Account admin = {ADM_LOGIN, ADM_PASSW};
		Account user1 = { "user1", "user" };
		Account user2 = { "user2", "user" };
		add_account(fp, &admin);
		add_account(fp, &user1);
		add_account(fp, &user2);
	}

	close_file(fp);
};

void open_file(FILE** fp, const char* file_name, const char* mode) {
	errno_t err = fopen_s(fp, file_name, mode);
	if (SUCCESS != err) { /* if error opening file, exit program */
		error(ERROR_FILE_OPEN, true);
	}
}

void close_file(FILE* fp) {
	errno_t err = fclose(fp);
	if (SUCCESS != err) { /* if can't close, exit prigram */
		error(ERROR_FILE_CLOSE, true);
	}
}

// handling error
// print error message to stderr
// exit if error critical for program
void error(const char* message, const _Bool critical) {
	perror(message);
	if (critical) {
		fprintf(stderr, ERROR_EXIT_CONFIRM);
		clean_scan();
		getchar();
		exit(EXIT_FAILURE);
	}
}

// TODO: is this function good?
// rewrite for other uses may be
void add_account(FILE* fp, const Account* acc) {
	int writed_count = fwrite(acc, sizeof(Account), 1, fp);
	if (1 == writed_count) {
		puts("Account successfully added.");
	}
	else {
		printf("Error occured, account [%s] wasn't saved", acc->login);
	}
}

/*
 * search user in file
 * if exists, return login
 * else return account with void passw
 */
Account get_user(const char login[LOGIN_LENGTH]) {

	// get list of all accounts
	int count = 0;
	Account* acc_list = get_acc_list(&count);
	if (0 == count) { /* if list void throw error and exit */
		errno = EINTR;
		error("User list empty. ", true);
	}

	// find account in list by login
	// DO NOT free(acc_list) until found Account is need
	int i = search(acc_list, count, login);

	Account res;
	strcpy_s(res.login, LOGIN_LENGTH, login);
	if (i > -1) { /* if account found, copy passw */
		strcpy_s(res.passw, PASSWORD_LENGTH, (acc_list+i)->passw);
	}
	else { /* account not found, return void passw */
		strcpy_s(res.passw, PASSWORD_LENGTH, "");
	}
	free(acc_list);

	return res;
}

/*
 * returns pointer to list of accounts from file
 * allocates memory, need to free!
 */
Account* get_acc_list(int* count) {
	FILE* fp;
	Account* a_list;
	size_t readed = 0;

	open_file(&fp, AUTH_FILE_NAME, "rb");

	// get count of contracts in file
	fseek(fp, 0L, SEEK_END);
	*count = ftell(fp) / sizeof(Account);
	rewind(fp);

	// TODO: is allocated memory size true? check @param count
	// allocate memory for array
	a_list = (Account*)calloc(count, sizeof(Account));

	// TODO: check int param instead of size_t
	// read array from file
	readed = fread_s(a_list, 
		(long)count * sizeof(Account), sizeof(Account), count, fp);
	if (readed != *count) {
		errno = EILSEQ;
		error(ERROR_FILE_CORRUPTED, false);
	}

	close_file(fp);
	return a_list;
}
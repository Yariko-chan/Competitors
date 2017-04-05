#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "input.h"
#include "file.h"
#include "search.h"
#include "utils.h"

const int SUCCESS = 0;

/*
creates file with init data if no file
*/
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

/*
creates void file if no file
*/
void init_players_file(void) {

	FILE* fp;
	errno_t err = 0;

	// open file or create if no such file
	err = fopen_s(&fp, PLAYERS_FILE_NAME, "ab");
	if (SUCCESS != err) { /* error opening file*/
						  /* recreate file by user confirmation */
		if (ask_confirm("Error opening main file. "
			"Would you like to recreate file? All players will be removed.")) {
			fclose(fp);
			remove(PLAYERS_FILE_NAME);
			err = fopen_s(&fp, PLAYERS_FILE_NAME, "ab");
			/* if can't create file, throw error and exit */
			if (SUCCESS != err) {
				error(ERR_FILE_CREATE, true);
			}
		}
		else {
			error(ERR_FILE_OPEN, true);
		}
	}

	close_file(fp);
};

/*
rewrite auth file with new data
*/
void save_accounts_changes(Account * a_list, const int count) {
	FILE* fp;
	size_t writed_count;

	encrypt((char*) a_list, count*sizeof(Account));

	open_file(&fp, ACCOUNTS_FILE_NAME, "wb");
	writed_count = fwrite(a_list, sizeof(Account), count, fp);
	if (count == writed_count)
		puts(MSG_SAVE_SUCCESS);
	else error(ERR_FILE_WRITING, false);

	close_file(fp);
}

/*
rewrite players file with new data
*/
void save_players_changes(Player * p_list, const int count) {
	FILE* fp;
	size_t writed_count;

	encrypt(p_list, count * sizeof(Player));
	open_file(&fp, PLAYERS_FILE_NAME, "wb");

	writed_count = fwrite(p_list, sizeof(Player), count, fp);
	if (count == writed_count)
		puts(MSG_SAVE_SUCCESS);
	else error(ERR_FILE_WRITING, false);

	close_file(fp);
}

/*
allocate memory and save accounts to @a_list
@a_list need to be free after use
if void, @a_list = NULL, return 0
 */
int get_accounts_list(Account** a_list) {
	FILE* fp;
	int count = 0;
	size_t readed = 0;
	*a_list = NULL; /* initiaize anyway */

	open_file(&fp, ACCOUNTS_FILE_NAME, "rb");

	// get count of accounts in file
	fseek(fp, 0L, SEEK_END);
	count = ftell(fp) / sizeof(Account);

	if (0 != count) {
		rewind(fp);
		*a_list = (Account*)calloc(count, sizeof(Account));

		// copy accounts to @a_list
		readed = fread_s(*a_list,
			count * sizeof(Account), sizeof(Account), count, fp);
		if (readed != count) {
			errno = EILSEQ;
			error(ERR_FILE_CORRUPTED, false);
		}

		decrypt(*a_list, count * sizeof(Account));
	}

	close_file(fp);
	return count;
}

/*
return pointer to list of players from file
return NULL if file void
allocates memory, need to free!
*/
int get_players_list(Player** p_list) {
	FILE* fp;
	size_t readed = 0;
	int count = 0;
	*p_list = NULL;

	open_file(&fp, PLAYERS_FILE_NAME, "rb");

	// get count of players in file
	fseek(fp, 0L, SEEK_END);
	count = ftell(fp) / sizeof(Player);
	if (0 != count) {
		rewind(fp);

		*p_list = (Player*)calloc(count, sizeof(Player));

		// write players to @p_list
		readed = fread_s(*p_list,
			count * sizeof(Player), sizeof(Player), count, fp);
		if (readed != count) {
			errno = EILSEQ;
			error(ERR_FILE_CORRUPTED, false);
		}

	}
	
	close_file(fp);
	decrypt(*p_list, count * sizeof(Player));
	return count;
}

/*
* search account in file
* if exists, save correct password to @pass
* else @pass = ""
*/
void get_pass_from_account(const char* login, char* pass) {

	// get list of all accounts
	Account* a_list = NULL; /* to have no errors with junk in the memory*/
	int count = get_accounts_list(&a_list);
	if (0 == count || NULL == a_list) { /* if list void, throw error and exit */
		errno = EINTR;
		error("Accounts list empty. ", true);
	}

	// find account in list by login
	// DO NOT free(a_list) until found Account is need
	int i = get_account_index(a_list, count, login);

	int res;
	if (i > -1) { /* if account found, return pass */
		res = strcpy_s(pass, PASSWORD_LENGTH, (a_list + i)->passw);
	}
	else { /* account not found, return void pass */
		res = strcpy_s(pass, PASSWORD_LENGTH, "");
	}
	if (res != 0) {
		// if continue, strlen(pass) -> strlen(NULL) -> throw exception
		errno = EINTR;
		error("Error occured while copy, password can't be checked.", true);
	}
	free(a_list);
}

/*
open file
exit if error occured
*/
void open_file(FILE** fp, const char* file_name, const char* mode) {
	errno_t err = fopen_s(fp, file_name, mode);
	if (SUCCESS != err) { /* if error opening file, exit program */
		error(ERR_FILE_OPEN, true);
	}
}

/*
close file
exit if error occured
*/
void close_file(FILE* fp) {
	errno_t err = fclose(fp);
	if (SUCCESS != err) { /* if can't close, exit prigram */
		error(ERR_FILE_CLOSE, true);
	}
}

/*
encrypts @sourse with xor-encryption
key is string used in get_key_char()
@size - size of @sourse in bytes
*/
void encrypt(char* sourse, const size_t size) {

	// set to zero
	//sourse[0] = sourse[0] ^ get_key_char(true);
	//for (int i = 1; i < (int) size; i++) {
	//	sourse[i] = sourse[i] ^ get_key_char(false);
	//}
	for (int i = 0; i < (int)size; i++) {
		sourse[i] = sourse[i] ^ ADM_PASSW[i % strlen(ADM_PASSW)];
	}
}

/*
decrypts @sourse with xor-encryption
key is string used in get_key_char()
@size - size of @sourse in bytes
*/
void decrypt(char* sourse, const size_t size) {

	// same as encrypt, but to functions to make it clear
	// and also for have opportunity to use other encryption later
	encrypt(sourse, size);
}
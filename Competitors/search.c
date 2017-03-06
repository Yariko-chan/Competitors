#include <stdlib.h>
#include <string.h>

#include "search.h"

// linear search
int search(const Account* a_list, const int count, const char* key_login) {
	int i = 0;
	int res = 0;

	for (i = 0; i < count; i++) {
		res = strcmp(a_list[i].login, key_login);
		if (0 == res) return i;
	}
	return -1;
}
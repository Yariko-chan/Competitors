#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "filter.h"
#include "file.h"

Player* filter(const Player* p_list, const int p_count, const FilterSet f_set,
	int* f_p_count) {
	bool* accepted = (bool*)calloc(p_count, sizeof(bool));
	*f_p_count = 0;
	for (int i = 0; i < p_count; i++) {
		if (fit_filters(p_list[i], f_set)) {
			accepted[i] = true;
			(*f_p_count)++;
		}
		else {
			accepted[i] = false;
		}

	}

	Player* f_p_list = (Player*)calloc(*f_p_count, sizeof(Player));
	for (int i = 0, j = 0; i < p_count, j < *f_p_count; i++) {
		if (accepted[i]) {
			f_p_list[j] = p_list[i];
			j++;
		}
	}

	free(accepted);
	return f_p_list;
}

bool fit_filters(const Player p, const FilterSet f_set) {

	// check all numeric fields
	if (!fit_condition(p.age, f_set.age_c_1)
		&& !fit_condition(p.age, f_set.age_c_2)) return false;
	if (!fit_condition(p.weight, f_set.weight_c_1)
		&& !fit_condition(p.weight, f_set.weight_c_2)) return false;
	if (!fit_condition(p.height, f_set.height_c_1)
		&& !fit_condition(p.height, f_set.height_c_2)) return false;

	// check gender
	if (f_set.gender != 'b' && f_set.gender != p.gender) return false;

	return true;
}

// true by default
// false if doesn't fit condition
bool fit_condition(const short n, const Condition c) {
	if (n < 0) {
		errno = EINVAL;
		error("Value for comparing must be non-negative.", false);
		return true; // as if condition is void
	}
	if (is_void_condition(c)) return true;
	return sign(n - c.value) == c.sign;
}

// 0 if 0
// -1 if negative
// +1 if positive
int sign(const int x) {
	return (x > 0) - (x < 0);
}

bool is_void_condition(const Condition c) {
	if (c.sign == SIGN_DFLT || c.value < 0) {
		return true;
	}
	return false;
}
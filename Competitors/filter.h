#pragma once

#include <stdbool.h>

#include "constants.h"

Player* filter_players_list(const Player* p_list, const int p_count, const FilterSet f_set, int* f_p_count);

bool fit_filters(const Player p, const FilterSet f_set);
bool fit_condition(const short n, const Condition c);

bool is_void_condition(const Condition c);
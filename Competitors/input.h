#pragma once

#include <stdbool.h>

#include "constants.h"

void clean_scan(void);
bool ask_confirm(const char* str);

Account input_account(void);
Player input_player(void);
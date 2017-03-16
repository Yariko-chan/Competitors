#pragma once

#include <stdbool.h>

#include "constants.h"

void clean_stdin(void);
bool ask_confirm(const char* str);

Account input_account(void);
Player input_player(void);

void edit_str(char* editable, const char* tag, const size_t length);
void edit_short(unsigned short* editable, const char* tag);

void read_str_or_skip(char * str, const int length);
void read_hu_or_skip(unsigned short* hu);

FilterSet get_filter_set(void);
Condition get_condition(void);
char get_gender(void);

bool is_char_sign(const char c);

char get_sort_mode(void);
#pragma once

#include <stdlib.h>
#include <stdbool.h>

char get_key_char(bool reset);

void encrypt(char* sourse, const size_t size);
void decrypt(char* sourse, const size_t size);
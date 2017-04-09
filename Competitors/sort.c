#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "constants.h"
#include "sort.h"

/*
sort @p_list by @mode
*/
void sort_by_mode(Player* p_list, const int count, const char mode) {
	switch (mode) {
	case 'n':
		puts("Sort by number");
		qsort(p_list, count, sizeof(Player), compare_num); 
		break;
	case 's':
		puts("Sort by surname");
		qsort(p_list, count, sizeof(Player), compare_surname);
		break;
	case 'w':
		puts("Sort by weight");
		qsort(p_list, count, sizeof(Player), compare_weight);
		break;
	case 'h':
		puts("Sort by height");
		qsort(p_list, count, sizeof(Player), compare_height);
		break;
	case 'a':
		puts("Sort by age");
		qsort(p_list, count, sizeof(Player), compare_age);
		break;
	case 'g':
		puts("Sort by number");
		qsort(p_list, count, sizeof(Player), compare_gender);
		break;
	default:
		puts("No such sort mode"); 
		break;
	}
	
}

/*
comparing by one of the field
*/

int compare_num(const void * p1, const void * p2)
{
	int result;
	result = ((Player *)p1)->number - ((Player *)p2)->number;
	return result;
}

int compare_surname(const void * p1, const void * p2)
{
	int result;
	result = strcmp(((Player*)p1)->name.surname, ((Player*)p2)->name.surname);
	return result;
}

int compare_weight(const void * p1, const void * p2)
{
	int result;
	result = ((Player *)p1)->weight - ((Player *)p2)->weight;
	return result;
}

int compare_height(const void * p1, const void * p2)
{
	int result;
	result = ((Player *)p1)->height - ((Player *)p2)->height;
	return result;
}

int compare_age(const void * p1, const void * p2)
{
	int result;
	result = ((Player *)p1)->age - ((Player *)p2)->age;
	return result;
}

int compare_gender(const void * p1, const void * p2)
{
	int result;
	result = ((Player *)p1)->gender - ((Player *)p2)->gender;
	return result;
}

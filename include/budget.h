#ifndef _budget_h_
#define _budget_h_
#include "../include/paper.h"

typedef struct budget_t
{
	Paper* start;
	char* name;
	int size;
	struct budget_t* next;
} Budget;

typedef struct
{
	Budget* start;
	int size;
} List;

List* initList();

Budget* searchBudget(Budget* current, char* name);

void insertBudget(List* list, Budget* budget);

void deleteBudget(List* list, char* name);

void initBudget(char* name);

void readList();

void saveList(List* list);

#endif

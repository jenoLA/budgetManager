#ifndef BUDGET_H
#define BUDGET_H
#include "../include/paper.h"


typedef struct budget_t
{
	Paper* start;
	char name[20];
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

void addBudget(List* list, Budget* budget);

void deleteBudget(List* list, char* name);

Budget* initBudget(char* name);

void printBudgets(Budget* current);

void readList();

void saveList(List* list);

#endif

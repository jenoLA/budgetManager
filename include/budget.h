#ifndef _budget_h_
#define _budget_h_

#include "../include/paper.h"


typedef struct budget_t
{
	Paper* start;
	char* name;
	int size;
} Budget;

typedef struct node_t
{
	struct node* next;
	Budget budget;
} Node;

typedef struct list_t
{
	Node* start;
	int size;
} List;

List* initList();

Budget* searchBudget(List* list, char* name);

void appendBudget(List* list, Budget budget);

void deleteBudget(List* list, char* name);

void initBudget(char* name);

void readList(); //still thinking about how/where to read

void saveList(List* list);

#endif

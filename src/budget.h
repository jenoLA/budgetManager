#include <stdlib.h>
#include <stdio.h>
#include "paper.h"

typedef struct
{
	Paper* start;
	char* name;
	int size;
} Budget;

typedef struct node
{
	struct node* next;
	Budget budget;
} Node;

typedef struct
{
	Node* start;
	int size;
} List;

List* initList()
{
	List* tempList = malloc(sizeof(List));
	tempList->size = 0;
	return tempList;
}

void initBudget(char* name);

void appendBudget(List* list, Budget budget);

Budget* searchBudget(List* list, char* name);

Paper* createPaper(Budget* budget, char* code, float initialValue);

void appendPaper(Budget budget, Paper paper);

void deleteBudget(List* list, char* name);

void deletePaper(Budget budget, char* code);

void saveList(List* list);

void readList(); //still thinking about how/where to read

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

initList();

initBudget(char* name);

appendBudget(List* list, Budget budget);

searchBudget(List* list, char* name);

appendPaper(Budget budget, Paper paper);

deleteBudget(List* list, char* name);

deletePaper(Budget budget, char* code);

saveList(List* list);

readList(); //still thinking about how/where to read




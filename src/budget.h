#include <stdlib.h>


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

Budget* searchBudget(List* list, char* name);

void appendBudget(List* list, Budget budget);

void deleteBudget(List* list, char* name);

void initBudget(char* name);

void readList(); //still thinking about how/where to read

void saveList(List* list);

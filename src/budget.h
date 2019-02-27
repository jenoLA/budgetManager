#include <stdlib.h>
#include <string.h>

typedef struct paper
{
	char* code;
	float initalValue;
	float finalValue;
	int totalTime;
	struct paper* next;
} Paper_t;

typedef struct budget
{
	Paper_t* start;
	char* name;
	int size;
	struct budget* next;
} Budget_t;

typedef struct
{
	Budget_t* start;
	int size;
} List;

List* initList()
{
	List* tempList = malloc(sizeof(List));
	tempList->size = 0;
	return tempList;
}

void newBudget(List* list, char name[20]);

Budget_t* searchBudget(List* list, char* name);

void appendBudget(List* list, Budget_t* budget);

void deleteBudget(List* list, char* name);

void initBudget(char* name);

void readList(); //still thinking about how/where to read

void saveList(List* list);

void printBudgets(Budget_t* current)
{
	while(current != NULL)
	{
		printf("budget name: %s\n", current->name);
		current = current->next;
	}
}
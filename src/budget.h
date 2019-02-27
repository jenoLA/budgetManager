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
	char name[20];
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

void newBudget(List* list, char name[20])
{
	Budget_t* temp = malloc(sizeof(Budget_t));
	// temp->name = name;
	strcpy(temp->name, name);
	temp->size = 0;
	temp->next = NULL;
	if(list->size == 0)
	{
		list->start = temp;
		list->size++;
		return;
	}
	Budget_t* budget = list->start;
	while(budget->next != NULL)
	{
		budget = budget->next;
	}
	budget->next = temp;
	list->size++;
}
Budget_t* searchBudget(List* list, char* name);

void appendBudget(List* list, Budget_t* budget);

void deleteBudget(List* list, char* name);

void initBudget(char* name);

void readList();

void saveList(List* list);

void printBudgets(Budget_t* current)
{
	while(current != NULL)
	{
		printf("budget name: %s\n", current->name);
		current = current->next;
	}
}
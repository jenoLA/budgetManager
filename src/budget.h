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

void appendBudget(List* list, Budget_t* budget)
{
	Budget_t* lBudget = list->start;
	while(lBudget->next != NULL)
	{
		lBudget = lBudget->next;
	}
	lBudget->next = budget;
	list->size++;	
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
	appendBudget(list, temp);
}

Budget_t* searchBudget(Budget_t* current, char* name)
{
	while(current != NULL) //seria nulo mesmo o current?
	{
		if (strcmp(current->name, name) == 0)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void deleteBudget(List* list, char* name)
{
	Budget_t* erase = searchBudget(list->start, name);
	if (erase == NULL)
	{
		printf("nao localizado nenhum budget com este nome[%s]\n", name);
		return;
	}
	if (list->start == erase)
	{
		Budget_t* oldHead = list->start;
		list->start = erase->next;
		free(oldHead);
		list->size--;
		return;
	}

	if (erase->next != NULL)
	{
		Budget_t* before = list->start;
		while(before->next != erase)
		{
			before = before->next;
		}
		Budget_t* budget = erase;
		budget = budget->next;
		before->next = budget;
		free(erase);
		list->size--;
		return;
	}
	free(erase);
	list->size--;
}

void readList(char* path);

void saveList(List* list, char* path);

void printBudgets(Budget_t* current)
{
	while(current != NULL)
	{
		printf("budget name: %s\n", current->name);
		current = current->next;
	}
}
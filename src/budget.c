#include <stdlib.h>
#include <string.h>

List* initList()
{
	List* tempList = malloc(sizeof(List));
	return tempList;
}

void appendBudget(List* list, Budget_t* budget)
{
	Budget_t* lBudget = list->start;
	while (lBudget->next != NULL)
	{
		lBudget = lBudget->next;
	}
	lBudget->next = budget;
	list->size++;
}

void newBudget(List* list, char name[20])
{
	Budget_t* temp = malloc(sizeof(Budget_t));
	strcpy(temp->name, name);

	if (list->size == 0)
	{
		list->start = temp;
		list->size++;
		return;
	}
	appendBudget(list, temp);
}

Budget_t* searchBudget(Budget_t* current, char* name)
{
	while (current != NULL)
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
		printf("Não foi localizado nenhum budget com o nome \"%s\"\n", name);
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
		while (before->next != erase)
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

void printBudgets(Budget_t* current)
{
	while (current != NULL)
	{
		printf("budget name: %s\n", current->name);
		current = current->next;
	}
}

// void readList(char* path)
// {

// }

// void saveList(List* list, char* path)
// {

// }

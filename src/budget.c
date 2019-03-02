#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/budget.h"



List* initList()
{
	List* newList = malloc(sizeof(List));
	return newList;
}


Budget* initBudget(char name[20])
{
	Budget* newBudget = malloc(sizeof(Budget));
	strcpy(newBudget->name, name);
	printf(" namezin: %s\n", newBudget->name);
	return newBudget;
}


void addBudget(List* list, char* name)
{
	Budget* budget = initBudget(name);
	if (list->start > 0)
	{
		Budget* lBudget = list->start;
		while (lBudget->next != NULL)
		{
			lBudget = lBudget->next;
		}

		lBudget->next = budget;
		list->size++;
		return;
	}
	list->start = budget;
	list->size++;

	printf("Budget \"%s\" created!\n", name);
}


Budget* searchBudget(Budget* current, char* name)
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
	Budget* erase = searchBudget(list->start, name);

	if (erase == NULL)
	{
		printf("Não foi localizado nenhum budget com o nome \"%s\"\n", name);
		return;
	}

	if (list->start == erase)
	{
		Budget* oldHead = list->start;
		list->start = erase->next;

		free(oldHead);

		list->size--;
		return;
	}

	if (erase->next != NULL)
	{
		Budget* before = list->start;
		while (before->next != erase)
		{
			before = before->next;
		}
		Budget* budget = erase->next;
		before->next = budget;

		free(erase);
		list->size--;
		return;
	}
	free(erase);
	list->size--;

	printf("Budget \"%s\" deleted!\n", name);
}


void printBudgets(List* list)
{
	Budget* current = list->start;
	for (int i = 1 ; current != NULL ; i++)
	{
		printf("budget %d: %s\n", i, current->name);
		current = current->next;
	}
}


// void readList(char* path)
// {

// }


// void saveList(List* list, char* path)
// {

// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/budget.h"



List* initList()
{
	List* newList = malloc(sizeof(List));
	return newList;
}


Budget* initBudget(char* name)
{
	Budget* newBudget = malloc(sizeof(Budget));
	strcpy(newBudget->name, name);
	printf("Initialized budget \"%s\".\n", newBudget->name);
	return newBudget;
}


void addBudget(List* list, char* name)
{
	Budget* newBudget = initBudget(name);
	if (list->start > 0)
	{
		newBudget* lastBudget = list->start;
		while (lastBudget->next != NULL)
		{
			lastBudget = lastBudget->next;
		}

		lastBudget->next = newBudget;
		list->size++;
		return;
	}
	list->start = newBudget;
	list->size++;

	printf("Budget \"%s\" created.\n", name);
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
	Budget* eraseBudget = searchBudget(list->start, name);

	if (eraseBudget == NULL)
	{
		printf("Budget \"%s\" not found.\n", name);
		return;
	}

	if (list->start == eraseBudget)
	{
		Budget* oldHead = list->start;
		list->start = eraseBudget->next;

		free(oldHead);

		list->size--;
		return;
	}

	if (eraseBudget->next != NULL)
	{
		Budget* before = list->start;
		while (before->next != eraseBudget)
		{
			before = before->next;
		}
		Budget* budget = eraseBudget->next;
		before->next = budget;

		free(eraseBudget);
		list->size--;
		return;
	}
	free(eraseBudget);
	list->size--;

	printf("Budget \"%s\" deleted.\n", name);
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

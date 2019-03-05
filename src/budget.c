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
		Budget* lastBudget = list->start;
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

	// If it was not found
	if (eraseBudget == NULL)
	{
		printf("Budget \"%s\" not found.\n", name);
		return; // Don't erase, quit
	}

	// If it is the first budget
	else if (eraseBudget == list->start)
		list->start = eraseBudget->next;

	// If it is between first and last budgets
	else if (eraseBudget->next != NULL)
	{
		Budget* before = list->start;

		// Iterate to get the before budget
		while (before->next != eraseBudget)
			before = before->next;

		// Skip eraseBudget
		before->next = before->next->next;
		// before->next = eraseBudget->next;
	}


	free(eraseBudget);
	list->size--;
	printf("Budget \"%s\" deleted.\n", name);
}


void printBudgets(Budget* current)
{
	for (int i = 1 ; current != NULL ; i++)
	{
		printf("budget %d: %s\n", i, current->name);
		current = current->next;
	}
}

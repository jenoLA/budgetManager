#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/budget.h"



List* initList(int argc, char** argv)
{

	if (argc == 1)
	{
		return malloc(sizeof(List));
	}
	else if (argc == 2)
	{
		return readList(argv[1]);
	}
	else
	{
		printf("This program accepts only a data file (one argument)\n");
		exit(1);
	}
}


Budget* initBudget(char* name)
{
	Budget* newBudget = malloc(sizeof(Budget));
	strcpy(newBudget->name, name);
	newBudget->next = NULL;
	newBudget->size = 0;
	newBudget->start = NULL;
	newBudget->totalValue = 0;
	newBudget->earned = 0;
	return newBudget;
}


void addBudget(List* list, Budget* budget)
{
	if (list->start > 0)
	{
		Budget* lastBudget = list->start;
		while (lastBudget->next != NULL)
		{
			lastBudget = lastBudget->next;
		}

		lastBudget->next = budget;
		list->size++;
		return;
	}
	list->start = budget;
	list->size++;
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
		printf("Budget: %s\n", current->name);
		printf("   Items: %i\n", current->size);
		if (current->size > 0)
		{
			printf("   Total value of items: %0.2f R$\n", current->totalValue);
		}
		if (current->earned != 0)
		{
			printf("   Earned with till now: %0.2f R$\n", current->earned);
		}
		printf("\n");
		current = current->next;
	}
	printf("\n");
}
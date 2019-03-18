#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "budget.h"


List* initList(char* path, char const* file)
{
	if (file)
	{
		int len = strlen(path) + strlen(file) + 1;
		char filePath[len];
		strncpy(filePath, path, strlen(path) + 1);
		return readList(strncat(filePath, file, len));
	}

	else
		return malloc(sizeof(List));

}


Budget* initBudget(char const* name)
{
	Budget* newBudget = malloc(sizeof(Budget));
	strncpy(newBudget->name, name, strlen(name) + 1);
	newBudget->next = NULL;
	newBudget->size = 0;
	newBudget->start = NULL;
	newBudget->totalValue = 0;
	newBudget->earned = 0;
	return newBudget;
}


int addBudget(List* list, Budget* budget)
{
	if (list->size == 0)
	{
		list->start = budget;
		list->size++;
		return 1;
	}
	
	Budget* lastBudget = list->start;

	while (lastBudget->next != NULL)
		lastBudget = lastBudget->next;

	lastBudget->next = budget;
	list->size++;
	return 1;
}


Budget* searchBudget(Budget* current, char const* name)
{
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return current;

		current = current->next;
	}
	return NULL;
}


int deleteBudget(List* list, char const* name)
{
	Budget* eraseBudget = searchBudget(list->start, name);

	// If it was not found
	if (eraseBudget == NULL)
		return 0; // Don't erase, quit

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
	else
	{
		Budget* before = list->start;

		// Iterate to get the before budget
		while (before->next != eraseBudget)
			before = before->next;

		//removing eraseBudget os the list
		before->next = NULL;
	}


	free(eraseBudget);
	list->size--;
	printf("\nBudget \"%s\" deleted.\n", name);
	return 1;
}

void printBudgets(Budget* current)
{
	while (current != NULL)
	{
		printf("\nBudget: %s\t\t\t\t%s\n", current->name, current->lastModified);
		printf("   Items: %i\n", current->size);

		if (current->size > 0)
			printf("   Total value of items: %0.2f R$\n", current->totalValue);

		if (current->earned != 0)
			printf("   Selled with till now: %0.2f R$\n", current->earned);

		printf("\n");
		current = current->next;
	}
}

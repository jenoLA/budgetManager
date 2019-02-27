#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/budget.h"

List* initList()
{
	List* newList = malloc(sizeof(List));
	return newList;
}

void insertBudget(List* list, Budget* budget)
{
	if (list->start != NULL)
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
}

Budget* newBudget(char name[20])
{
	Budget* temp = malloc(sizeof(Budget));
	strcpy(temp->name, name);
	return temp;
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
}

void printBudgets(Budget* current)
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

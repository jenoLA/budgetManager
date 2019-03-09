#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/paper.h"

Paper* createPaper()
{
	Paper* temp = malloc(sizeof(Paper));
	char code[6];
	printf("Name of your new stock: \n");
	scanf(" %s", &code);
	strcpy(temp->code, code);

	float initialValue;
	printf("His value by unit: \n");
	scanf(" %f", &initialValue);
	temp->initialValue = initialValue;

	int quantity;
	printf("How much units: \n");
	scanf(" %i", &quantity);
	temp->quantity = quantity;

	temp->next = NULL;
	temp->isSelled = 0;
	return temp;
}

// requesting char code[6] for better integration with the system
Paper* searchPaper(Paper* current, char* string)
{
	while (current != NULL)
	{
		if (strcmp(current->code, string) == 0)
			return current;

		current = current->next;
	}
	return NULL;
}

// puts on the last position
void addPaper(Budget* budget, Paper* paper)
{
	if (budget->size > 0)
	{
		Paper* current = budget->start;

		while(current->next != NULL)
			current = current->next;

		current->next = paper;
		budget->totalValue += paper->initialValue * paper->quantity;
		budget->size++;
		printf("Budget value: %f\n", budget->totalValue);
		return;
	}

	budget->start = paper;
	budget->size++;
	budget->totalValue += paper->initialValue * paper->quantity;
}

void deletePaper(Budget* budget)
{
	char code[6];
	printf("Name of the paper to delete: \n");
	scanf(" %s", code);

	Paper* erase = searchPaper(budget->start, code);

	if (erase == NULL)
	{
		printf("Not found any paper with this[%s] code\n", code);
		return;
	}

	if (budget->start == erase)
	{
		Paper* oldHead = budget->start;
		budget->start = erase->next;

		free(oldHead);

		budget->size--;
		return;
	}

	if (erase->next != NULL)
	{
		Paper* before = budget->start;

		while (before->next != erase)
			before = before->next;

		Paper* nextPaper = erase->next;
		before->next = nextPaper;

		free(erase);
		budget->size--;
		return;
	}
	free(erase);
	budget->size--;
}

// print all the info about the papers
void listPapers(Paper* current)
{
	while(current != NULL)
	{
		printf("Paper Code: %s\n", current->code);
		printf("    Initial value: %0.2f R$\n", current->initialValue);
		printf("    Quantity: %i\n", current->quantity);
		if (current->isSelled == 1)
		{
			printf("    Final value: %0.2f R$\n", current->finalValue);
			printf("    You have earned: %0.2f R$\n", current->finalValue - current->initialValue);
		}
		printf("\n");
		current = current->next;
	}
}

// data required within
void updatePaper(Budget* budget, Paper* paper)
{
	float finalValue;
	printf("\nFinal value of the paper: \n");
	scanf("%f", &finalValue);
	paper->finalValue = finalValue;
	paper->isSelled = 1;
	budget->earned += finalValue * paper->quantity;
}

static void paperMenuMessage(Budget* budget)
{
	printf("\n====================");
	printf(" You are on");
	printf("\e[96m");
	printf(" %s ", budget->name);
	printf("\e[97m");
	printf("Budget");
	printf("======================\n");
	printf("\nQ)uit  L)ist papers  A)dd paper   U)pdate paper   S)ave paper and quit  D)elete paper\n");
}

void paperMenu(Budget* budget)
{
	char option;
	while(budget)
	{
		paperMenuMessage(budget);
		scanf(" %c", &option);
		if (option >= 65 && option <=90)
		{
			option += 32;
		}

		if(option == 'q')
		{
			break;
		}

		else if(option == 'l')
		{
			listPapers(budget->start);
		}

		else if(option == 'a')
		{
			addPaper(budget, createPaper());
		}

		else if(option == 'u')
		{
			char code[6];
			printf("Name of the paper: \n");
			scanf(" %s", &code);
			Paper* paper = searchPaper(budget->start, code);
			if (paper != NULL)
			{
				updatePaper(budget, paper);
			}
			else
				printf("\nError, paper not registered\n");
		}

		else if(option == 'd')
			deletePaper(budget);

		else if(option == 's')
			break;

		else
		{
			printf("\e[91m");
			printf("Invalid command\n");
			printf("\e[97m");
		}
	}
}

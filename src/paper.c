#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "paper.h"


Paper* createPaper(char* code, float value, int quantity)
{
	Paper* temp = malloc(sizeof(Paper));
	setWeek(temp->dayOf);

	strncpy(temp->code, code, 7); //maximun size
	temp->bValue = value;
	temp->quantity = quantity;
	temp->actualQuantity = quantity;
	temp->next = NULL;
	temp->earned = 0;
	return temp;
}

// requesting char string for better integration with the system
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
int addPaper(Budget* budget, Paper* paper)
{
    strncpy(budget->lastModified, paper->dayOf, 15);
    
    if (budget->size == 0)
	{
		budget->start = paper;
		budget->size++;
		budget->totalValue += paper->bValue * paper->quantity;
        setWeek(budget->lastModified);
		return 1;
	}
	
	Paper* current = budget->start;
	
    while(current->next != NULL)
		current = current->next;

	current->next = paper;
	budget->totalValue += paper->bValue * paper->quantity;
	budget->size++;
	return 1;
}

int deletePaper(Budget* budget, char* code)
{
	Paper* erasePaper = searchPaper(budget->start, code);

	if (erasePaper == NULL)
	{
		return 0;
	}

	else if (budget->start == erasePaper)
		budget->start = erasePaper->next;

	else if (erasePaper->next != NULL)
	{
		Paper* before = budget->start;

		while (before->next != erasePaper)
			before = before->next;

		before->next = before->next->next;
	}

	else
	{
		Paper* before = budget->start;

		// Iterate to get the before budget
		while (before->next != erasePaper)
			before = before->next;

		//removing erasePaper of the budget
		before->next = NULL;
	}

	printf("\npaper %s deleted\n", code);
	free(erasePaper);
	budget->size--;
	return 1;
}

// print all the info about the papers
int listPapers(Paper* current)
{
	while(current != NULL)
	{
		printf("\n  Paper code: %s\t\t\t\t%s\n", current->code, current->dayOf);
		printf("\tPondered value: %0.2f R$\n", current->bValue);
		printf("\tCurrent quantity: %i\n", current->actualQuantity);

        if (current->actualQuantity == 0)
			printf("\tfinal pondered value: %0.2f R$\n", current->bValue * current->quantity);

		if (current->earned != 0)
			printf("\tSelled: %0.2f R$\t\t\t%s\n", current->earned, current->selled);

		printf("\n");
		current = current->next;
	}
	return 1;
}

// data required within
int updatePaperSell(Budget* budget, Paper* paper, float value, int quantityMinus)
{
	if (quantityMinus > paper->actualQuantity)
		return 0; //because of the invalid entry

	setWeek(paper->selled);
	paper->actualQuantity -= quantityMinus;
	paper->earned += (value * quantityMinus);
	budget->earned += (value * quantityMinus);
	return 1;
}

int updatePaperBuy(Budget* budget, Paper* paper, float value, int quantityPlus)
{
	setWeek(paper->dayOf);
	setWeek(budget->lastModified);
	paper->bValue = (paper->bValue + value) / 2;
	budget->totalValue += value * quantityPlus;
	paper->quantity += quantityPlus;
	paper->actualQuantity += quantityPlus;
	return 1;
}

void simulateSell(Paper* paper, float value, int quantityMinus)
{	
	if (quantityMinus > paper->actualQuantity)
	{
		printf("\e[91m");
		printf("\ninvalid number, you cannot sell more than you have\n");
		printf("\e[m");
		return; //if invalid enter
	}
	
	char today[15];
	setWeek(today);

	if ((strcmp(paper->dayOf, today)) == 0)
	{
		printf("\e[33m");
		printf("\nif you sell this paper today, be ware of the tax\n");
		printf("\e[m");
	}

	float byUnit = value - paper->bValue;
	printf("\nearned by unit: %0.2f\n", byUnit);
	printf("\ntotal: %0.2f\n", byUnit * quantityMinus);
}

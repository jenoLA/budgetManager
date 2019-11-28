#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "paper.h"

List* initList(char* path, char const* file)
{
	if (file)
	{
		int len = strlen(path) + strlen(file) + 1;
		char filePath[len];
		strncpy(filePath, path, strlen(path) + 1);
		return readList(strncat(filePath, file, len));
	}

	return malloc(sizeof(List));
}

Paper* createPaper(char* code, float value, int quantity)
{
	Paper* temp = malloc(sizeof(Paper));
	setWeek(temp->dayOfBuy);

	for (int i = 0; i < sizeof(code); ++i)
		code[i] = toupper(code[i]);

	strncpy(temp->code, code, 7); //maximun size
	temp->buyValue = value;
	temp->quantity = quantity;
	temp->actualQuantity = quantity;
	temp->next = NULL;
	temp->earned = 0;
	return temp;
}

Paper* searchPaper(Paper* paper, char *code)
{
	for (int i = 0; i < strlen(code); ++i)
		code[i] = toupper(code[i]);

	while (paper)
	{
		if (!strcmp(paper->code, code))
			return paper;

		paper = paper->next;
	}
	
	return NULL;
}

// puts on the last position
int addPaper(List* list, Paper* paper)
{
    strncpy(list->lastModified, paper->dayOfBuy, 13);
    
    if (!list->size)
	{
		list->start = paper;
		list->size++;
		list->totalValue += paper->buyValue * paper->quantity;
		return 0;
	}
	
	Paper* current = list->start;
	
    while(current->next)
		current = current->next;

	current->next = paper;
	list->totalValue += paper->buyValue * paper->quantity;
	list->size++;
	return 0;
}

int deletePaper(List* list, char *code)
{
	Paper* paperToDelete = searchPaper(list->start, code);

	if (!paperToDelete)
		return 1;

	else if (list->start == paperToDelete)
		list->start = paperToDelete->next;

	else if (paperToDelete->next)
	{
		Paper* before = list->start;

		while (before->next != paperToDelete)
			before = before->next;

		before->next = before->next->next;
	}
/*
	else
	{
		Paper* before = list->start;

		// Iterate to get the before list
		while (before->next != paperToDelete)
			before = before->next;

		//removing paperToDelete of the list
		before->next = NULL;
	}
*/
	printf("\npaper %s deleted\n", code);
	free(paperToDelete);
	list->size--;
	return 0;
}

void listPapers(Paper* current)
{
	while(current)
	{
		printf("\n  Paper code: %s\t\t\t\t%s\n", current->code, current->dayOfBuy);
		printf("\tPondered value: %0.2f R$\n", current->buyValue);
		printf("\tCurrent quantity: %i\n", current->actualQuantity);

        if (current->actualQuantity == 0)
			printf("\tfinal pondered value: %0.2f R$\n", current->buyValue * current->quantity);

		if (current->earned)
			printf("\tearned: %0.2f R$\t\t%s\n", current->earned, current->dayOfSell);

		printf("\n");
		current = current->next;
	}
}

int updatePaperSell(List* list, Paper* paper, float value, int quantityMinus)
{
	if (quantityMinus > paper->actualQuantity)
		return 1; //invalid entry

	setWeek(paper->dayOfSell);
	paper->actualQuantity -= quantityMinus;
	paper->earned += (value * quantityMinus);
	list->earned += (value * quantityMinus);
	return 0;
}

int updatePaperBuy(List* list, Paper* paper, float value, int quantityPlus)
{
	setWeek(paper->dayOfBuy);
	setWeek(list->lastModified);
	list->totalValue += value * quantityPlus;
	paper->quantity += quantityPlus;
	paper->buyValue = (paper->buyValue * paper->actualQuantity + value * quantityPlus) / paper->quantity; //pondered new paper->bvalue
	paper->actualQuantity += quantityPlus;
	return 0;
}

void simulateSell(Paper* paper, float value, int quantityMinus)
{	
	if (quantityMinus > paper->actualQuantity)
    {
        printf("\ninvalid number, you cannot sell more than you have\n");
		return; //if invalid enter
	}
	
	char today[15];
	setWeek(today);

	if (!strcmp(paper->dayOfBuy, today))
		printf("\nif you sell this paper today, be ware of the tax\n");

	float byUnit = value - paper->buyValue;
	printf("\nearned by unit: %0.2f\n", byUnit);
	printf("\ntotal: %0.2f\n", byUnit * quantityMinus);
}

void simulateBuy(Paper* paper, float value, int quantityMinus)
{	
	if (quantityMinus > paper->actualQuantity)
    {
        printf("\ninvalid number, you cannot sell more than you have\n");
		return; //if invalid enter
	}
	
	char today[15];
	setWeek(today);

	if (!strcmp(paper->dayOfBuy, today))
		printf("\nif you sell this paper today, be ware of the tax\n");

	float byUnit = value - paper->buyValue;
	printf("\nearned by unit: %0.2f\n", byUnit);
	printf("\ntotal: %0.2f\n", byUnit * quantityMinus);
}

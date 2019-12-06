#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "paper.h"

List* initList(char* path, char const* file)
{
	if (file)
	{
		char filePath[PATH_SIZE];
		memccpy(memccpy(filePath, path, '\0', PATH_SIZE) -1, file, '\0', PATH_SIZE);
		return readList(filePath);
	}

	return malloc(sizeof(List));
}

Paper* createPaper(char* code, float value, int quantity)
{
	Paper* temp = malloc(sizeof(Paper));
	setWeek(temp->dayOfBuy);

	register int codeSize = strlen(code);
	for (register int i = 0; i < codeSize; i++)
		code[i] = toupper(code[i]);

	memccpy(temp->code, code, '\0', CODE_SIZE);
	temp->averageValue = value;
	temp->quantity = quantity;
	temp->actualQuantity = quantity;
	temp->next = NULL;
	temp->earned = 0;
	return temp;
}

Paper* searchPaper(Paper* paper, char *code)
{
	register int codeSize = strlen(code);
	for (register int i = 0; i < codeSize; i++)
		code[i] = toupper(code[i]);

	while (paper)
	{
		if (!strcmp(paper->code, code)) return paper;

		paper = paper->next;
	}
	
	return NULL;
}

// puts on the last position
int addPaper(List* list, Paper* paper)
{
    memccpy(list->lastModified, paper->dayOfBuy, '\0', DATE_SIZE);
	list->lastModified[DATE_SIZE - 1] = '\0';
    
    if (list->size == 0)
	{
		list->start = paper;
		list->size++;
		list->totalValue += paper->averageValue * paper->quantity;
		return 0;
	}
	
	Paper* current = list->start;
	
	for(register int i = 1; i < list->size; i++)
		current = current->next;

	current->next = paper;
	list->totalValue += paper->averageValue * paper->quantity;
	list->size++;
	return 0;
}

int deletePaper(List* list, char *code)
{
	Paper* paperToDelete = searchPaper(list->start, code);

	if (!paperToDelete)
		return 1;

	if (list->start == paperToDelete)
		list->start = paperToDelete->next;

	else
	{
		Paper *before = list->start;
		while(before->next != paperToDelete)
		{
			before = before->next;
		}
		before->next = paperToDelete->next;
	}
	
	printf("paper %s deleted\n", paperToDelete->code);
	free(paperToDelete);
	list->size--;
	return 0;
}

void listPapers(Paper* current)
{
	while(current)
	{
		printf("\nPaper code: %s\t\t\t%s\n", current->code, current->dayOfBuy);
		printf(" Average value by unit: %0.2f R$\n", current->averageValue);
		printf(" Current quantity: %i\n", current->actualQuantity);

        if (current->actualQuantity == 0)
			printf(" Total value: %0.2f R$\n", current->averageValue * current->quantity);

		if (current->earned)
			printf(" Earned: %0.2f R$\t\t\t%s\n", current->earned, current->dayOfSell);

		current = current->next;
	}
	printf("\n");
}

int sellPaper(List* list, Paper* paper, float value, int quantityMinus)
{
	if (quantityMinus > paper->actualQuantity)
		return 1; //invalid entry

	setWeek(paper->dayOfSell);
	paper->actualQuantity -= quantityMinus;
	paper->earned += (value * quantityMinus);
	list->earned += (value * quantityMinus);
	return 0;
}

int buyPaper(List* list, Paper* paper, float value, int quantityPlus)
{
	setWeek(paper->dayOfBuy);
	setWeek(list->lastModified);
	list->totalValue += value * quantityPlus;
	paper->quantity += quantityPlus;
	paper->averageValue = (paper->averageValue * paper->actualQuantity + value * quantityPlus) / paper->quantity;
	paper->actualQuantity += quantityPlus;
	return 0;
}

void simulateSell(Paper* paper, float value, int quantityMinus)
{	
	if (quantityMinus > paper->actualQuantity)
    {
        printf("\ninvalid number, you cannot sell more than you have\n");
		return;
	}
	
	float byUnit = value - paper->averageValue;
	printf("\nearned by unit: %0.2f\n", byUnit);
	printf("\ntotal: %0.2f\n", byUnit * quantityMinus);
}

void simulateBuy(Paper* paper, float value, int quantityPlus)
{	
	if (quantityPlus > 0)
    {
        printf("\ninvalid number, you can't buy zero or a non-positive number\n");
		return;
	}
	
	float byUnit = (value * quantityPlus + paper->averageValue * paper->quantity) / paper->quantity + quantityPlus;
	printf("\naverage value by unit: %0.2f\n", byUnit);
	printf("\ntotal: %0.2f\n", byUnit * quantityPlus);
}

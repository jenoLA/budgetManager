#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/paper.h"

Paper* createPaper()
{
	Paper* temp = malloc(sizeof(Paper));
	temp->isSelled = 0;
	char* code;
	printf("name of your new stock: \n");
	scanf(" %s", &code);
	if (strlen(code) > 5)
	{
		printf("invalid stock code, it is allowed just 6 or less characters\n");
		return;
	}
	strcpy(temp->name, code);

	float initialValue;
	printf("his value by unit: \n");
	scanf(" %f", &initialValue);
	temp->initialValue = initialValue;
	
	int quantity;
	printf("how much units: \n");
	scanf(" %i", &quantity);
	temp->quantity = quantity;
	
	return temp;
}

// requesting char code[6] for better integration with the system
Paper* searchPaper(Paper* current, char code[6]);

// puts on the last position
void addPaper(Budget* budget, Paper* paper)
{
	Paper* current = budget->start;
	if (budget->size > 0)
	{
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = temp;
		budget->size++;
		return;
	}
	budget->start = temp;
	budget->size++;
}

void deletePaper(Budget* budget, char code[6]);

// print all the info about the papers
void listPapers(Paper* current);

// data required within
void updatePaper();
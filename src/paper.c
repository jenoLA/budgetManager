#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/paper.h"



Paper* createPaper()
{
	Paper* temp = malloc(sizeof(Paper));
	char code[6];
	printf("\nName of your new stock: ");
	scanf(" %s", code);
	printf("\n");
	// change in the future to if the quantity isn't multiply of 100 add F in the end
	for (int i = 0; i < sizeof(code); ++i)
		code[i] = toupper(code[i]);

	strcpy(temp->code, code);

	float initialValue;
	printf("\nHis value by unit: ");
	scanf(" %f", &initialValue);
	printf("\n");
	temp->bValue = initialValue;

	int quantity;
	printf("\nHow much units: ");
	scanf(" %i", &quantity);
	temp->quantity = quantity;
	temp->actualQuantity = quantity;

	setWeek(temp->dayOf);

	temp->next = NULL;
	temp->earned = 0;
	return temp;
}

// requesting char code[6] for better integration with the system
Paper* searchPaper(Paper* current, char* string)
{
	for (int i = 0; i < strlen(string); ++i)
		string[i] = toupper(string[i]); // putting here to simplify

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
	if (budget->size == 0)
	{
		budget->start = paper;
		budget->size++;
		budget->totalValue += paper->bValue * paper->quantity;
		strcpy(budget->lastModified, paper->dayOf);
		return;
	}
	
	Paper* current = budget->start;
	while(current->next != NULL)
		current = current->next;

	current->next = paper;
	budget->totalValue += paper->bValue * paper->quantity;
	budget->size++;
	strcpy(budget->lastModified, paper->dayOf);

}

void deletePaper(Budget* budget)
{
	char code[6];
	printf("\nName of the paper to delete: ");
	scanf(" %s", code);

	Paper* erasePaper = searchPaper(budget->start, code);

	if (erasePaper == NULL)
	{
		printf("\e[91m");	
		printf("Not found any paper with this code\n");
		printf("\e[m");
		return;
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
	setWeek(budget->lastModified);
}

// print all the info about the papers
void listPapers(Paper* current)
{
	while(current != NULL)
	{
		printf("\nPaper Code: %s\t\t\t\t%s\n", current->code, current->dayOf);
		printf("    Pondered value: %0.2f R$\n", current->bValue);
		printf("    Current quantity: %i\n", current->actualQuantity);
		if (current->actualQuantity == 0)
			printf("    final pondered value: %0.2f R$\n", current->bValue * current->quantity);
		
		if (current->earned != 0)
			printf("    Selled: %0.2f R$\t\t\t\t%s\n", current->earned, current->selled);

		printf("\n");
		current = current->next;
	}
}

// data required within
void updatePaper(Budget* budget, Paper* paper)
{
	float quantityMinus;
	printf("\nQuantity selled: ");
	scanf(" %f", &quantityMinus);

	if (quantityMinus > paper->actualQuantity)
	{
		printf("\e[91m");
		printf("\ninvalid number, you cannot sell more than you have\n");
		printf("\e[m");
		return; //because of the invalid entry
	}
	
	float price; //for both situations
	setWeek(budget->lastModified);

	// sell part
	if (quantityMinus > 0)
	{
		setWeek(paper->selled);
		printf("\nValue of the paper selled: ");
		scanf(" %f", &price); //sell price

		paper->actualQuantity -= quantityMinus;
		paper->earned += (price * quantityMinus);
		budget->earned += (price * quantityMinus);
		return; //not going to buy part
	}

	// buy part
	float quantityPlus;
	printf("\nQuantity brought: ");
	scanf(" %f", &quantityPlus);
	
	if (quantityPlus > 0)
	{
		setWeek(paper->dayOf);
		printf("\nvalue by unit: \n");
		scanf(" %f", &price);
		paper->bValue = (paper->bValue + price) / 2;
		budget->totalValue += price * quantityPlus;
		paper->quantity += quantityPlus;
		paper->actualQuantity += quantityPlus;
		return; //to end here
	}
	//nothing happens because there isn't any thing to change
}

void simulateSell(Paper* paper)
{
	float quantityPlus, quantityMinus, value;
	if ((strcmp(paper->dayOf, paper->selled)) == 0)
	{
		printf("\e[36m");
		printf("\nif you sell this paper today, be ware of the tax\n");
		printf("\e[m");
	}
	printf("\nQuantity selled: ");
	scanf(" %f", &quantityMinus);

	if (quantityMinus > paper->actualQuantity)
	{
		printf("\e[91m");
		printf("\ninvalid number, you cannot sell more than you have\n");
		printf("\e[m");
		return; //if invalid enter
	}

	if (quantityMinus > 0)
	{
		printf("\nValue of the paper selled: ");
		scanf(" %f", &value);
		float byUnit = value - paper->bValue;
		printf("\nearned by unit: %0.2f\n", byUnit);
		printf("\ntotal: %0.2f\n", byUnit * quantityMinus);
		return;
	}
	//goes here if isn't going to sell any paper
	printf("\nQuantity brought: ");
	scanf(" %f", &quantityPlus);
	float bprice; //buy price
	printf("\nvalue by unit: \n");
	scanf(" %f", &bprice);
	float ponderedValue = (paper->bValue + bprice) / 2;
	printf("\npondered value: %0.2f\n", ponderedValue);
	printf("\ntotal: %0.2f\n", ponderedValue * quantityPlus);

}

void paperMenuMessage(Budget* budget)
{
	printf("\n====================");
	printf(" You are on");
	printf("\e[96m");
	printf(" %s ", budget->name);
	printf("\e[m");
	printf("Budget");
	printf("======================\n");
	printf("\nA)dd paper  L)ist papers  U)pdate paper  S)imulate  D)elete paper  B)ack to the main menu\n");
}

void paperMenu(Budget* budget)
{
	char option;
	while(budget)
	{
		paperMenuMessage(budget);
		scanf(" %c", &option);
		
		option = tolower(option);

		if(option == 'l')
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
			printf("\nName of the paper: ");
			scanf(" %s", code);
			
			Paper* paper = searchPaper(budget->start, code);
			
			if (paper != NULL)
				updatePaper(budget, paper);
			
			else
				printf("\nError, paper not registered\n");
		}

		else if (option == 's')
		{
			char code[6];
			printf("\nName of the paper: ");
			scanf(" %s", code);
			Paper* paper = searchPaper(budget->start, code);
			simulateSell(paper);
		}

		else if(option == 'd')
			deletePaper(budget);

		else if(option == 'b')
			break;

		else
		{
			printf("\e[91m");
			printf("\nInvalid command\n");
			printf("\e[m");
		}
	}
}

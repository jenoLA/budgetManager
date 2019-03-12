#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/paper.h"

Paper* createPaper()
{
	Paper* temp = malloc(sizeof(Paper));
	char code[6];
	printf("Name of your new stock: ");
	scanf(" %s", code);
	printf("\n");
	// change in the future to if the quantity isn't multiply of 100 add F in the end
	for (int i = 0; i < sizeof(code); ++i)
		code[i] = toupper(code[i]);
	
	strcpy(temp->code, code);

	float initialValue;
	printf("His value by unit: ");
	scanf(" %f", &initialValue);
	printf("\n");
	temp->bValue = initialValue;

	int quantity;
	printf("How much units: ");
	scanf(" %i", &quantity);
	printf("\n");
	temp->quantity = quantity;
	temp->actualQuantity = quantity;

	temp->next = NULL;
	temp->earned = 0;
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
	if (budget->size == 0)
	{
		budget->start = paper;
		budget->size++;
		budget->totalValue += paper->bValue * paper->quantity;
		return;
	}
	
	Paper* current = budget->start;
	while(current->next != NULL)
		current = current->next;

	current->next = paper;
	budget->totalValue += paper->bValue * paper->quantity;
	budget->size++;

}

void deletePaper(Budget* budget)
{
	char code[6];
	printf("Name of the paper to delete: \n");
	scanf(" %s", code);

	Paper* erase = searchPaper(budget->start, code);

	if (erase == NULL)
	{
		printf("\e[91m");	
		printf("Not found any paper with this code\n");
		printf("\e[m");
		return;
	}

	else if (budget->start == erase)
		budget->start = erase->next;

	else if (erase->next != NULL)
	{
		Paper* before = budget->start;

		while (before->next != erase)
			before = before->next;

		before->next = before->next->next;
	}

	printf("paper %s deleted\n", code);
	free(erase);
	budget->size--;
}

// print all the info about the papers
void listPapers(Paper* current)
{
	while(current != NULL)
	{
		printf("\nPaper Code: %s\n", current->code);
		printf("    Pondered value: %0.2f R$\n", current->bValue);
		printf("    Current quantity: %i\n", current->actualQuantity);
		if (current->actualQuantity == 0)
			printf("    final pondered value: %0.2f R$\n", current->bValue * current->quantity);
		
		if (current->earned != 0)
			printf("    Selled: %0.2f R$\n", current->earned);

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
	// sell part
	if (quantityMinus > 0)
	{
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
		printf("\nearned by unit: %0.2f\n", value - paper->bValue);
		return;
	}
	//goes here if isn't going to sell any paper
	printf("\nQuantity brought: ");
	scanf(" %f", &quantityPlus);
	float bprice; //buy price
	printf("\nvalue by unit: \n");
	scanf(" %f", &bprice);
	printf("\npondered value: %0.2f\n", (paper->bValue + bprice) / 2);

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
			
			for (int i = 0; i < sizeof(code); ++i)
				code[i] = toupper(code[i]);

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
			
			for (int i = 0; i < sizeof(code); ++i)
				code[i] = toupper(code[i]);

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

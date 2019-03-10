#include "../include/paper.h"

Paper* createPaper()
{
	Paper* temp = malloc(sizeof(Paper));
	char code[6];
	printf("Name of your new stock: ");
	scanf(" %s", code);
	printf("\n");
	
	for (int i = 0; i < sizeof(code); ++i)
		code[i] = toupper(code[i]);
	
	strcpy(temp->code, code);

	float initialValue;
	printf("His value by unit: ");
	scanf(" %f", &initialValue);
	printf("\n");
	temp->initialValue = initialValue;

	int quantity;
	printf("How much units: ");
	scanf(" %i", &quantity);
	printf("\n");
	temp->quantity = quantity;

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
	if (budget->size > 0)
	{
		Paper* current = budget->start;

		while(current->next != NULL)
			current = current->next;

		current->next = paper;
		budget->totalValue += paper->initialValue * paper->quantity;
		budget->size++;

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
		printf("Paper Code: %s\n", current->code);
		printf("    Initial value: %0.2f R$\n", current->initialValue);
		printf("    Current quantity: %i\n", current->quantity);
		if (current->quantity == 0)
			printf("    final earned (brute) value: %0.2f R$\n", current->earned);
		
		else if (current->earned != 0)
			printf("    You have earned till now: %0.2f R$\n", current->earned);

		printf("\n");
		current = current->next;
	}
}

// data required within
void updatePaper(Budget* budget, Paper* paper)
{
	float quantityPlus, quantityMinus, value;

	printf("\nQuantity brought: ");
	scanf(" %f", &quantityPlus);

	printf("\nQuantity selled: ");
	scanf(" %f", &quantityMinus);

	if (paper->quantity <= quantityMinus)
	{
		printf("\e[91m");
		printf("invalid number, you cannot sell more than you have\n");
		printf("\e[m");
		return;
	}

	printf("\nValue of the paper selled: ");
	scanf(" %f", &value);

	paper->quantity += quantityPlus - quantityMinus;
	paper->earned += (value * quantityMinus);
	budget->earned += (value * quantityMinus);
	return;
}

static void paperMenuMessage(Budget* budget)
{
	printf("\n====================");
	printf(" You are on");
	printf("\e[96m");
	printf(" %s ", budget->name);
	printf("\e[m");
	printf("Budget");
	printf("======================\n");
	printf("\nA)dd paper  L)ist papers  U)pdate paper  D)elete paper  S)ave paper and quit  Q)uit\n");
}

void paperMenu(Budget* budget)
{
	char option;
	while(budget)
	{
		paperMenuMessage(budget);
		scanf(" %c", &option); //this to prevent more than one a character
		
		if (option >= 65 && option <= 90)
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

		else if(option == 'd')
			deletePaper(budget);

		else if(option == 's')
			break;

		else
		{
			printf("\e[91m");
			printf("Invalid command\n");
			printf("\e[m");
		}
	}
}

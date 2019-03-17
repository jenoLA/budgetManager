#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include "../include/budget.h"
#include "../include/paper.h"
#include "../include/commands.h"

void welcomeMessage()
{
	printf("\e[0;m");
	printf("\n=========================");
	printf("\e[36m");
	printf(" Budget Manager ");
	printf("\e[m");
	printf("==========================\n\n");
	printf("N)ew budget  E)nter budget  L)ist budgets  D)elete budget  S)ave and quit  Q)uit\n");
}

void printFilesInFolder(char* path)
{
	DIR* dir;
	struct dirent* entry;
	printf("--------------------------[dir: %s ]-------------------------\n\n", path);
	
	if ((dir = opendir(path)))
	{	
		while ((entry = readdir(dir)))
		{
 			if (entry->d_name[0] != '.')
  				printf(">> %s\n", entry->d_name);
		}

		closedir(dir);
		printf("\n");
		return;
	}

	printf("invalid directory\n");
}

void mainMenu(char* path, char const* file)
{
	List* list = initList(path, file);

	char name[20];
	char option;
	int save;
	int success;

	while (list)
	{
		welcomeMessage();

		printf("\n");
		scanf(" %c", &option);
		option = tolower(option);

		if (option == 'n')
		{
			printf("Type the name to the new budget (max 20 characters): ");
			scanf(" %s", name);
			printf("\n");
			Budget* newBudget = initBudget(name);
			success = addBudget(list, newBudget);
			save = paperMenu(newBudget);
		}
		
		else if (option == 'd')
		{
			printf("Type the name of the budget to delete: ");
			scanf(" %s", name);
			printf("\n");
			success = deleteBudget(list, name);
		}

		else if (option == 's')
			save = 1;
		
		else if (option == 'e')
		{
			printf("Name of the budget to enter: ");
			scanf(" %s", name);
			printf("\n");

			Budget* budget = searchBudget(list->start, name);
			
			if (budget == NULL)
				printf("Not found any budget with this name\n");

			save = paperMenu(budget);
		}
		
		else if (option == 'l')
		{
			printBudgets(list->start);
			success = 1;
		}

		else if (option == 'q')
			exit(0);

		else
		{
			printf("\e[91m");
			printf("\nInvalid command\n");
			printf("\e[m");
		}

		if (save)
		{
			printFilesInFolder(path);
			printf("Name to the new data file: ");
			scanf(" %s", name);
			printf("\n");
			
			saveList(list, strcat(path, name)); //sending directly
			exit(0);
		}

		else if (!success)
		{
			printf("\e[33m");
			printf("\nInvalid entry\n");
			printf("\e[m");
		}
	}	
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
	printf("\nA)dd paper  L)ist papers  U)pdate paper  S)imulate  D)elete paper  B)ack  Q)uit and save\n\n");
}

int paperMenu(Budget* budget)
{
	char option;
	int success;
	while(budget)
	{
		paperMenuMessage(budget);

		scanf(" %c", &option);
		
		option = tolower(option);

		if(option == 'l')
			success = listPapers(budget->start);

		else if(option == 'a')
		{
			char code[6];
			printf("\nName of your new stock: ");
			scanf(" %s", code);
			printf("\n");

			for (int i = 0; i < sizeof(code); ++i)
				code[i] = toupper(code[i]);

			float value;
			printf("\nHis value by unit: ");
			scanf(" %f", &value);
			printf("\n");

			int quantity;
			printf("\nHow much units: ");
			scanf(" %i", &quantity);
			success = addPaper(budget, createPaper(code, value, quantity));
		}

		else if(option == 'u')
		{
			char code[6];
			printf("\nName of the paper: ");
			scanf(" %s", code);
			
			for (int i = 0; i < strlen(code); ++i)
				code[i] = toupper(code[i]);

			Paper* paper = searchPaper(budget->start, code);
			
			float price; //for both situations
			
			float quantityMinus;
			if (paper)
			{
				char today[13];
				setWeek(today);
				
				if ((strcmp(paper->dayOf, today)) == 0)
				{
					printf("\e[33m");
					printf("\nif you sell this paper today, be ware of the tax\n");
					printf("\e[m");
				}

				printf("\nQuantity selled: ");
				scanf(" %f", &quantityMinus);
				
				if (quantityMinus > 0)
				{
					printf("\nValue of the paper selled: ");
					scanf(" %f", &price); //sell price
					success = updatePaperSell(budget, paper, price, quantityMinus);
				}
			}
			
			//buy part
			else if (quantityMinus == 0)
			{
				float quantityPlus;
				printf("\nQuantity brought: ");
				scanf(" %f", &quantityPlus);
			
				if (quantityPlus > 0)
				{
					printf("\nvalue by unit: \n");
					scanf(" %f", &price);
					success = updatePaperBuy(budget, paper, price, quantityPlus);
				}
			}

			else
				printf("\nInvalid entry\n");

		}

		else if (option == 's')
		{
			char code[6];
			printf("\nName of the paper: ");
			scanf(" %s", code);
			
			for (int i = 0; i < strlen(code); ++i)
				code[i] = toupper(code[i]);
			
			Paper* paper = searchPaper(budget->start, code);
			if (paper)
			{
				float quantityMinus, value;
				printf("\nQuantity selled: ");
				scanf(" %f", &quantityMinus);
				
				printf("\nValue of the paper selled: ");
				scanf(" %f", &value);
				
				simulateSell(paper, value, quantityMinus);
			}
		}

		else if(option == 'd')
		{
			char code[6];
			printf("\nName of the paper to delete: ");
			scanf(" %s", code);
			success = deletePaper(budget, code);
		}

		else if(option == 'b')
			return 0;

		else if (option == 'q')
			return 1;

		else
		{
			printf("\e[91m");
			printf("\nInvalid action\n");
			printf("\e[m");
		}
		
		if (!success)
		{
			printf("\e[91m");	
			printf("Not found any paper with this code\n");
			printf("\e[m");
		}
	}
	return 0;
}
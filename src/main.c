#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/struct.h"
#include "../include/budget.h"
#include "../include/paper.h"

static void welcomeMessage()
{
	printf("\n=========================");
	printf("\033[0;96m");
	printf(" Budget Manager "); 
	printf("\033[0;97m");
	printf("==========================\n\n");
	printf("Q)uit, L)ist budgets, N)ew budget,  E)nter budget,  D)elete budget,  S)ave and quit\n");
}

int main(int argc, char** argv)
{
	List* list = initList(argc, argv);
	while (list)
	{
		char name[20];
		char option;
		welcomeMessage();
		scanf(" %s", &option);
		
		if (option >= 65 && option <= 95)
		{// if uppercase is modified to be lowercase
			option += 32;
		}

		if (option == 'n')
		{
			printf("Type the name to the new budget (max 20 characters):\n");
			scanf(" %s", &name);
			Budget* newBudget = initBudget(name);
			addBudget(list, newBudget);
			paperMenu(newBudget);
		}
		else if (option == 'd')
		{
			printf("Type the name of the budget to delete:\n");
			scanf(" %s", &name);
			deleteBudget(list, name);
		}
		else if (option == 'l')
			printBudgets(list->start);

		else if (option == 'q')
		{
			free(list);
			exit(0);
		}

		else if (option == 's')
		{// thought: print folder arquive
			printf("name to the newly data file: \n");
			char name[20];
			scanf(" %s", &name);
			char* path = "arquive/";
			strcat(path, name);
			saveList(list, path);
			break;
		}

		else if (option == 'e')
		{
			printf("name of the budget to enter: \n");
			scanf(" %s", &name);
			Budget* budget = searchBudget(list->start, name);
			if (budget == NULL)
			{
				printf("not found any budget with this name[%s]\n", name);
			}
			paperMenu(budget);
		}
		else
		{
			printf("\033[0;91m");
			printf("invalid command\n");
			printf("\033[0;97m");
		}
	}
	return 0;
}

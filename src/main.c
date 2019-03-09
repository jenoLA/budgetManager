#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/struct.h"
#include "../include/budget.h"
#include "../include/paper.h"


static void welcomeMessage()
{
	printf("\e[0;m");
	printf("\n=========================");
	printf("\e[36m");
	printf(" Budget Manager ");
	printf("\e[m");
	printf("==========================\n\n");
	printf("Q)uit, L)ist budgets, N)ew budget,  E)nter budget,  D)elete budget,  S)ave and quit\n");
}


int main(int argc, char** argv)
{
	List* list = initList(argc, argv);
	char name[20];
	char option;

	while (list)
	{
		welcomeMessage();

		scanf(" %c", &option);
		option = tolower(option);

		if (option == 'n')
		{
			printf("Type the name to the new budget (max 20 characters):\n");
			scanf(" %s", name);
			Budget* newBudget = initBudget(name);
			addBudget(list, newBudget);
			paperMenu(newBudget);
		}
		else if (option == 'd')
		{
			printf("Type the name of the budget to delete:\n");
			scanf(" %s", name);
			deleteBudget(list, name);
		}
		// thought: print folder arquive
		else if (option == 's')
		{
			printf("Name to the newly data file: \n");
			scanf(" %s", name);

			char* path = "arquive/";
			strcat(path, name);
			saveList(list, path);
			break;
		}
		else if (option == 'e')
		{
			printf("Name of the budget to enter: \n");
			scanf(" %s", name);

			Budget* budget = searchBudget(list->start, name);
			if (budget == NULL)
				printf("Not found any budget with this name[%s]\n", name);

			paperMenu(budget);
		}
		else if (option == 'l')
			printBudgets(list->start);

		else if (option == 'q')
			exit(0);

		else
		{
			printf("\e[m");
			printf("Invalid command\n");
			printf("\e[37m");
		}
	}
	return 0;
}

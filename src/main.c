#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/struct.h"
#include "../include/budget.h"
#include "../include/paper.h"



int main(int argc, char** argv)
{
	List* list;
	char name[20];
	char option;
	if (argc == 1)
	{
		list = initList();
	}
	else if (argc == 2)
	{
		list = readList(argv[1]);
	}
	else
	{
		printf("this program just accept one data file only\n");
		exit(1);
	}
	while (true) {

		printf("\n====================== Budget Manager ======================\n\n");
		if (list->size > 0)
		{
			printBudgets(list->start);
		}
		printf("Q)uit, L)ist budgets, N)ew budget,  E)nter budget,  D)elete budget,  S)ave and quit\n");

		scanf(" %c", &option);

		option = tolower(option);

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
		{
			saveList(list, "arquive/temp.txt");
			break;
		}

		else if (option == 'e')
		{
			printf("name of the budget to enter: \n");
			scanf(" %s", &name);
			Budget* budget = searchBudget(list->start, name);
			paperMenu(budget);
		}
	}
	return 0;
}

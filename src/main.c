#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/struct.h"
#include "../include/budget.h"
#include "../include/paper.h"



int main()
{
	List* list = initList();

	char name[20];
	char option;

	while (true) {

		printf("\n====================== Budget Manager ======================\n\n");
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
			break;
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

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/budget.h"


int main()
{
	List* list = initList();

	char name[20];
	char option;

	while (true) {

		printf("By now we have the following functionalities\n");
		printf("Q)uit, L)ist budgets, N)ew budget*,  E)nter budget,  D)elete budget\n");

		scanf(" %c", &option);

		option = tolower(option);

		if (option == 'l')
		{
			printBudgets(list->start);
		}
		else if (option == 'n')
		{
			printf("Type the name to the new budget (max 20 characters):\n");
			scanf(" %s", &name);
			insertBudget(list, initBudget(name));
			printf("Done!\n\n");
		}
		else if (option == 'd')
		{
			printf("Type the name of the budget to delete:\n");
			scanf(" %s", &name);
			deleteBudget(list, name);
			printf("Done!\n\n");
		}
		else if (option == 'e')
		{
			// paperLoop();
		}
		if (option == 'q')
		{
			break;
		}
	}
	return 0;
}

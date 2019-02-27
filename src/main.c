#include <stdio.h>
#include <ctype.h>
#include "budget.h"

int main()
{
	List* list = initList();

	char name[20];
	char option;

	while (1) {

		printf("by now we have the following functionalities\n");
		printf("Q)uit, L)ist budgets, N)ew budget*,  E)nter budget,  D)elete budget\n");

		scanf(" %c", &option);

		option = tolower(option);

		if (option == 'l')
		{
			printBudgets(list->start);
		}
		else if (option == 'n')
		{
			printf("name to the new budget of twenty caracters or least:\n");
			scanf(" %s", &name);
			newBudget(list, name);
			printf("done!\n\n");
			printf("%s start\n", list->start);
		}
		else if (option == 'd')
		{
			// printf("name of the budget to delete:\n");
			// scanf(" %s", &name);
			// deleteBudget(list, name);
			// printf("done!\n\n");
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

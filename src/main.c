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

		printf("By now we have the following functionalities:\n");
		printf("Q)uit, L)ist budgets, N)ew budget,  E)nter budget,  D)elete budget\n");

		scanf(" %c", &option);

		option = tolower(option);

		if (option == 'n')
		{
			printf("Type the name to the new budget (max 20 characters):\n");
			scanf(" %s", &name);
			addBudget(list, name);
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
			break;

		else if (option == 'e')
		{
			printf("name of the budget to enter: \n");
			scanf(" %s", &name);
			Budget* budget = searchBudget(list->start, name);
			while(budget)
			{
				printf("\n===================== You are on %s budget =====================\nMenu:\nQ)uit  L)ist papers  A)dd paper   U)pdate paper   S)ave paper and quit  D)elete paper\n", budget->name);
				scanf(" %c", &option);
				option = tolower(option);
				if(option == 'q')
				{
					//we will be using free in the future
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
					// change the search to be idiot-proof
					char name[6];
					printf("code of the paper to update: \n");
					scanf(" %s", &name);
					Paper* paper = searchPaper(budget->start, name);
					updatePaper(paper);
				}
				
				else if(option == 's')
				{
					//save and quit here
				}
				
				else if(option == 'd')
				{
					//delete here
				}
			}
		}
	}
	return 0;
}

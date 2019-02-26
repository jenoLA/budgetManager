#include <stdio.h>
#include "budget.h"
#include "paper.h"


int main()
{
	List* list = initList();

	char name[20];
	char option;

	while (1) {

	    printf("by now we have the following functionalities\n");
		printf("Q)uit  L)ist budgets  N)ew budget*   E)nter budget   D)elete budget\n");

	    scanf(" %c", &option);

	    if (option >= 65 && option <= 90)
	    {
	        option += 32;
	    }
	    if (option == 'q')
	    {
	        break;
	    }
	    else if (option == 'l')
	    {
	     //   printBudgets(list);
	    }
	    else if (option == 'n')
	    {
	        // printf("name to the new budget of twenty caracters or least:\n");
	        // scanf(" %s", &name);
	        // newBudget(list, name);
	        // printf("done!\n\n");
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
		//	paperLoop();
	    }
	}

	return 0;
}

#include <stdio.h>
#include "budget.h"

void paperLoop(Budget budget);

void budgetLoop(List* list)
{
	char name[20];
	char option;
	while(1){
	    printf("by now we have the following functionalities\nQ)uit  L)ist budgets  N)ew budget*   E)nter budget   D)elete budget\n");
	    scanf(" %c", &option);
	    if (option >= 65 && option <= 90)
	    {
	        option += 32;
	    }
	    if(option == 'q')
	    {
	        break; 
	    }
	    else if(option == 'l' )
	    {
	     //   printBudgets(list);
	    }
	    else if(option == 'n')
	    {
	        // printf("name to the new budget of twenty caracters or least:\n");
	        // scanf(" %s", &name);	   
	        // newBudget(list, name);
	        // printf("done!\n\n");
	    }
	    else if(option == 'd')
	    {
	        // printf("name of the budget to delete:\n");
	        // scanf(" %s", &name);
	        // deleteBudget(list, name);
	        // printf("done!\n\n");
	    }
	    else if(option == 'e')
	    {
		//	paperLoop();    	
	    }
	}
}

int main(int argc, char const *argv[])
{
	List* list = initList();
	if(list->size == 0)
	{
		printf("sucess!!\n");
	}
	budgetLoop(list);
	return 0;
}
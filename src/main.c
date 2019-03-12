#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include "../include/struct.h"
#include "../include/budget.h"
#include "../include/paper.h"


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

int main(int argc, char const *argv[])
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

		else if (option == 's')
		{
			char filePath[60] = "arquive/";
			printFilesInFolder(filePath);
			printf("Name to the new data file: \n");
			scanf(" %s", name);
			strcat(filePath, name);
			saveList(list, filePath);
			exit(0);
		}
		
		else if (option == 'e')
		{
			printf("Name of the budget to enter: \n");
			scanf(" %s", name);

			Budget* budget = searchBudget(list->start, name);
			
			if (budget == NULL)
				printf("Not found any budget with this name\n");

			paperMenu(budget);
		}
		
		else if (option == 'l')
			printBudgets(list->start);

		else if (option == 'q')
			exit(0);

		else
		{
			printf("\e[91m");
			printf("\nInvalid command\n");
			printf("\e[m");
		}
	}
	return 0;
}

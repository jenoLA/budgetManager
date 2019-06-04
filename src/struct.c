#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

void setWeek(char* date)
{
	time_t now = time(NULL);;
	struct tm* ts;
	ts = localtime(&now);

	strftime(date, 15, "%d:%m:%y %a", ts);
}

// make a verification
List* readList(char const* path)
{
	FILE* pf;
	List* list = malloc(sizeof(List));
	pf = fopen(path, "r");
	
	if (pf == NULL)
    {    
		printf("\nfile data not found\n");
		exit(1);
	}
	int isList;

	if (!fscanf(pf, "\"list\": %i\n", &isList))
	{
		printf("\nfile data invalid\n");
		exit(1);
	}

	fscanf(pf, "\"size\": %i\n", &(list->size));
	fscanf(pf, "\n");
	Budget* currentBudget = malloc(sizeof(Budget));
	Paper* currentPaper;
	for (int i = 0; i < list->size; ++i)
	{
		currentBudget->next = malloc(sizeof(Budget));
		fscanf(pf, "\t\"budget\": %s\n", currentBudget->next->name);
		fscanf(pf, "\t\t\"size\": %i\n", &currentBudget->next->size);
		fscanf(pf, "\t\t\"totalValue\": %f\n", &currentBudget->next->totalValue);
		fscanf(pf, "\t\t\"earned\": %f\n", &currentBudget->next->earned);
		fscanf(pf, "\t\t\"lastModified\": %[^\n]\n", currentBudget->next->lastModified);

		currentPaper = malloc(sizeof(Paper));
		for (int j = 0; j < currentBudget->next->size; ++j)
		{
			currentPaper->next = malloc(sizeof(Paper));
			fscanf(pf, "\t\t\"paper\": %s\n", currentPaper->next->code);
			fscanf(pf, "\t\t\t\"bValue\": %f\n", &currentPaper->next->bValue);
			fscanf(pf, "\t\t\t\"earned\": %f\n", &currentPaper->next->earned);
			fscanf(pf, "\t\t\t\"quantity\": %i\n", &currentPaper->next->quantity);
			fscanf(pf, "\t\t\t\"actualQuantity\": %i\n", &currentPaper->next->actualQuantity);
			fscanf(pf, "\t\t\t\"dayOf\": %[^\n]\n", currentPaper->next->dayOf);
			
			if (currentPaper->next->quantity != currentPaper->next->actualQuantity)
				fscanf(pf, "\t\t\t\"selled\": %[^\n]\n", currentPaper->next->selled);

			// for the first paper in the budget
			if (j == 0)
			{
				currentBudget->next->start = currentPaper->next;
				currentPaper = currentBudget->next->start;
			}
			else
				currentPaper = currentPaper->next;
		}
		currentPaper->next = NULL;

		fscanf(pf, "\n");
		// for the first budget in the list
		if (i == 0)
		{
			list->start = currentBudget->next;
			currentBudget = list->start;
		}
		else
			currentBudget = currentBudget->next;
	}

	currentBudget->next = NULL;
	fclose(pf);
	return list;
}

void saveList(List* list, char const* path)
{
	FILE* pf;
	pf = fopen(path, "w+");
	
	if (pf == NULL)
	{
		printf("\ninvalid directory\n");
		exit(1);
	}

	fprintf(pf, "\"list\": 1\n");
	fprintf(pf, "\"size\": %i\n", list->size);
	fprintf(pf, "\n");

	Budget* currentBudget = list->start;
	while(currentBudget != NULL)
	{
		fprintf(pf, "\t\"budget\": %s\n", currentBudget->name);
		fprintf(pf, "\t\t\"size\": %i\n", currentBudget->size);
		fprintf(pf, "\t\t\"totalValue\": %0.2f\n", currentBudget->totalValue);
		fprintf(pf, "\t\t\"earned\": %0.2f\n", currentBudget->earned);
		fprintf(pf, "\t\t\"lastModified\": %s\n", currentBudget->lastModified);

		Paper* currentPaper = currentBudget->start;
		while(currentPaper != NULL)
		{
			fprintf(pf, "\t\t\"paper\": %s\n", currentPaper->code);
			fprintf(pf, "\t\t\t\"bValue\": %0.2f\n", currentPaper->bValue);
			fprintf(pf, "\t\t\t\"earned\": %0.2f\n", currentPaper->earned);	
			fprintf(pf, "\t\t\t\"quantity\": %i\n", currentPaper->quantity);
			fprintf(pf, "\t\t\t\"actualQuantity\": %i\n", currentPaper->actualQuantity);
			fprintf(pf, "\t\t\t\"dayOf\": %s\n", currentPaper->dayOf);

			if (currentPaper->quantity != currentPaper->actualQuantity)
				fprintf(pf, "\t\t\t\"selled\": %s\n", currentPaper->selled);

			currentPaper = currentPaper->next;
		}

		fprintf(pf, "\n");
		currentBudget = currentBudget->next;
	}

	fclose(pf);
}
